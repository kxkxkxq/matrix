#pragma once

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
        MatrixGenerator(const size_t s, const T d) : matrixSize_(m), 
                                                     matrixDeterminant_(d),
                                                     matrixVector_(m, std::vector<T>(m, 0)) 
        {
            for(size_t i = 0; i < matrixSize_; ++i)
                matrixVector_[i][i] = 1;
            size_t indx = get_pseudorandom_number(0, matrixSize_ - 1);
            matrixVector_[indx][indx] = matrixDeterminant_;
        };  //  created a diagonal matrix with a given determinant
        
        void generate_matrix(); //  transforms the matrix without changing its determinant
        const std::vector<T> get_matrix_vec() const   //  returns generated matrix represented as a vector
        {
            std::vector<T> tmp(matrixSize_ * matrixSize_);
            for(auto i : matrixVector_)
                for(auto j : i)
                    tmp.push_back(j);

            return tmp;
        }

    private :
        template <typename U>
        const U get_pseudorandom_number(const U lb, const U ub);
        {
            std::random_device r;
            std::mt19937 gen(r());    
            std::uniform_int_distribution<> req_dist{lb, ub};
            return gen();
        }

        void transpose_matrix()
        {
            for(size_t i = 0; i < matrixSize_; ++i)
                for(size_t j = 0; j < i; ++j)
                {
                    if(i == j) 
                        break;
                    matrixVector_[i][j] = matrixVector_[j][i];
                }
        }

        void swap_rows(const size_t rowNum1, const size_t rowNum2)
        {
            std::vector<T>& row1Ref = matrixVector_[rowNum1];
            std::vector<T>& row2Ref = matrixVector_[rowNum2];
            assert(row1Ref.size() == row2Ref.size()); 
            
            for(size_t i = 0; i < row1Ref.size(); ++i)
            {
                T tmp = -row1Ref[i];      //  when the matrix rows swap, the sign of determinant changes, 
                row1Ref[i] = row2Ref[i];  //  so one of the rows must be multiplied by -1
                row2Ref[i] = tmp;
            }
        }

        void rows_elementary_operations(const size_t rowNum1, const size_t rowNum2);
            //  this func multiplies the rows by random coefs and sums them up
    }

    void generate_matrix()
    {
        size_t lb = 0;
        size_t ub = matrixSize_ - 1;
        
        for(size_t i = 0; i < matrixSize_; ++i) //  N times swap rows and columns
        {
            swap_rows(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
            transpose_matrix();
            swap_rows(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
        }

        for(size_t i = 0; i < matrixSize_; ++i) //  N times do rows and columns elementary operations
        {
            rows_elementary_operations(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
            transpose_matrix();
            rows_elementary_operations(get_pseudorandom_number(lb, ub), get_pseudorandom_number(lb, ub));
        }
    }

    template <typename T>
    void 
    rows_elementary_operations(const size_t rowNum1, const size_t rowNum2)
    {
        std::vector<T>& row1Ref = matrixVector_[rowNum1];
        std::vector<T>& row2Ref = matrixVector_[rowNum2];
        assert(row1Ref.size() == row2Ref.size()); 

        const int coef1 = get_pseudorandom_number(0, matrixSize_ - 1);  //  the range from 0 to the matrix size   
        const int coef2 = get_pseudorandom_number(0, matrixSize_ - 1);  //  is chosen as the range of random numbers
        for(size_t i = 0; i < row1Ref.size(); ++i)
        {
            row1Ref[i] *= coef1;
            row2Ref[i] *= coef2;
            row2Ref[i] += row1Ref;
            row1Ref[i] /= coef1;    // problems if T == int 
            row2Ref[i] /= coef2;
        }
    }
}   //  namespace e2etests