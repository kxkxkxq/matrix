#pragma once

#include <cassert>
#include <random>
#include <vector>

namespace e2etests
{
    template<typename T> class MatrixGenerator final
    {
        const size_t matrixSize_;
        double matrixDeterminant_;
        std::vector<std::vector<T>> matrixVector_;

    public :
        MatrixGenerator(const size_t s, const double d) : matrixSize_(s), 
                                                          matrixDeterminant_(d),
                                                          matrixVector_(s, std::vector<T>(s, 0)) 
        {
            for(size_t i = 0; i < matrixSize_; ++i)
                matrixVector_[i][i] = 1;
            const int indx = get_pseudorandom_number(0, matrixSize_ - 1);
            matrixVector_[indx][indx] = matrixDeterminant_;
        };  //  created a diagonal matrix with a given determinant
        
        void generate_matrix(); //  transforms the matrix without changing its determinant
        
        std::vector<T> get_matrix_vec() const   //  returns generated matrix represented as a vector
        {
            std::vector<T> tmp;
            tmp.reserve(matrixSize_ * matrixSize_);
            for(auto&& i : matrixVector_)
                for(auto&& j : i)
                    tmp.push_back(j);
            return tmp;
        }

    private :
        const int get_pseudorandom_number(const int lb, const int  ub)
        {
            if(lb == ub)
                return lb;
            std::random_device r;
            std::mt19937 gen(r());    
            std::uniform_int_distribution<> req_dist{lb, ub};
            return req_dist(gen);
        }

        void transpose_matrix()
        {
            for(size_t i = 0; i < matrixSize_; ++i)
                for(size_t j = 0; j < i; ++j)
                    std::swap(matrixVector_[i][j], matrixVector_[j][i]);   
        }

        void swap_rows(const size_t rowNum1, const size_t rowNum2)
        {
            if(rowNum1 == rowNum2) return;
            std::swap(matrixVector_[rowNum1], matrixVector_[rowNum2]);   
            for(auto&& elem : matrixVector_[rowNum1])
                elem *= -1;
            //  when the matrix rows swap, the sign of determinant changes, 
            //  so one of the rows must be multiplied by -1
       }                                           
        
        void rows_elementary_operations(const size_t rowNum1, const size_t rowNum2);
            //  this func multiplies the rows by random coefs and sums them up
    };

    template <typename T>
    void 
    MatrixGenerator<T>::generate_matrix()
    {
        if(matrixSize_ == 1) return;
        size_t lb = 0;
        size_t ub = matrixSize_ - 1;

        for(auto&& i : matrixVector_) //  N times swap rows and columns
        {
            swap_rows(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
            transpose_matrix();
            swap_rows(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
        }
#if 0        
        for(auto&& j : matrixVector_) //  N times do rows and columns elementary operations
        {
            rows_elementary_operations(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
            transpose_matrix();
            rows_elementary_operations(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
        }
#endif       
    }

    template <typename T>
    void 
    MatrixGenerator<T>::rows_elementary_operations(const size_t rowNum1, const size_t rowNum2)
    {
        if(rowNum1 == rowNum2) return;
        std::vector<T>& row1Ref = matrixVector_[rowNum1];
        std::vector<T>& row2Ref = matrixVector_[rowNum2];
        assert(row1Ref.size() == row2Ref.size()); 

        const int limit = 100;
        const int coef1 = get_pseudorandom_number(-limit, limit);  //  the range from -100 to 100
        const int coef2 = get_pseudorandom_number(-limit, limit);  //  is chosen as the range of random numbers
        if(coef1 == 0 || coef2 == 0) return;

        for(size_t i = 0; i < row1Ref.size(); ++i)
        {
            row1Ref[i] *= coef1;
            row2Ref[i] *= coef2;
            row2Ref[i] -= row1Ref[i];
            //  div
        }
    }
}   //  namespace e2etests