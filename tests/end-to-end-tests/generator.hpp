#pragma once

#include <vector>

namespace e2etests
{
    template<typename T> class MatrixGenerator final
    {
        const size_t matrixSize_;
        const T matrixDeterminant_;
        std::vector<std::vector<T>> matrixVector_;

    public :
        MatrixGenerator(const size_t s, const T d) : matrixSize_(m), 
                                                     matrixDeterminant_(d),
                                                     matrixVector_(m, std::vector<T>(m, 0)) 
        {
            size_t indx = 0;
            matrixVector_[indx][indx] = matrixDeterminant_; 
            for(size_t i = 1; i < matrixSize_; ++i)
                matrixVector_[i][i] = 1;
        };  //  created a diagonal matrix with a given determinant
        
        void generate_matrix(); //  transforms the matrix without changing its determinant
        const std::vector<T> get_matrix() const;  //  return generated matrix 

    private :
        template <typename U>
        const U get_pseudorandom_number(const U lb, const U ub);
        {
            std::random_device r;
            std::mt19937 gen(r());    
            std::uniform_int_distribution<> req_dist{lb, ub};
            return gen();
        }
    }

    void
    generate_matrix()
    {
        size_t lb = 0;
        size_t ub = matrixSize_ - 1;
        
        for(size_t i = 0; i < matrixSize_; ++i)
        {
            swap_rows(get_pseudorandom_number, get_pseudorandom_number);
            transpose_matrix();
            swap_rows(get_pseudorandom_number, get_pseudorandom_number);
        }

        for(size_t i = 0; i < matrixSize_; ++i)
        {
            rows_elementary_operations(get_pseudorandom_number, get_pseudorandom_number);
            transpose_matrix();
            rows_elementary_operations(get_pseudorandom_number, get_pseudorandom_number);
        }
    } 
    


}   //  namespace e2etests