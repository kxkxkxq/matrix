#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.hpp"

namespace determinanttests
{
//      struct for tests
    template <typename T> struct DetParam
    {
        const std::vector<T> matrixVec;
        double result;
    };

//      DETERMINANT TEST DATA
    static std::vector<int> v1(1,1);    //  det == 0
    static std::vector<int> v2(4,1);    //  det == 0
    static std::vector<int> v3(100);    //  det == 0
    
    static std::vector<int> v4{ 1, 0, 0,    
                                0, 1, 0,
                                0, 0, 1 };  //  det == 1
    
    static std::vector<int> v5{ 0, 0, 0, 
                                0, 1, 0, 
                                0, 0, 0 };  //  det == 0

    static std::vector<int> v6{ 1, 2, 3,
                                3, 2, 1, 
                                2, 1, 3 };  //  det == -12

    static std::vector<int> v7{ 1, 4, 1,
                                4, 0, 1, 
                                4, 1, 4 };  //  det == -45

    static std::vector<int> v8{ 0, 1, 2,
                                2, 0, 1, 
                                1, 2, 0 };  //  det == 9

    static std::vector<int> l9{ 1, 0, 1, 2,
                                0, 1, 0, 1,
                                1, 0, 1, 0
                                2, 1, 0, 1 };  //  det == -4
                            
    static std::vector<int> l10{ 0, 1, 1, 1,
                                 1, 0, 1, 1,
                                 1, 1, 0, 1,
                                 1, 1, 1, 0 };  //  det == -3

    static std::vector<int> l11{ 1, 2, 2, 1,
                                 3, 0, 3, 1,
                                 1, 3, 0, 3,
                                 2, 1, 1, 2 };  //  det == 0
    
    static std::vector<int> l12{ 1, 2, 0, 3,
                                 2, 1, 3, 0,
                                 0, 3, 1, 2,
                                 3, 0, 2, 1 };  //  det == 0
                                
    static std::vector<int> l13{ 4, 1, 6, 3,
                                 1, 5, 1, 2,
                                 2, 1, 5, 1,
                                 3, 6, 1, 4 };  //  det == -21

    static std::vector<int> l14{ 9, 9, 1, 0,
                                 1, 6, 5, 9,
                                 0, 0, 1, 9,
                                 9, 9, 5, 6 };  //  det == -1350

    static std::vector<int> l15{ 0, 1, 2, 3, 4,
                                 4, 0, 1, 2, 3,
                                 3, 4, 0, 1, 2,
                                 2, 3, 4, 0, 1,
                                 1, 2, 3, 4, 0 };  //  det == 1250

    static std::vector<int> l16{ 1, 2, 3, 4, 5,
                                 3, 3, 4, 5, 1,
                                 2, 1, 5, 1, 2,
                                 1, 5, 4, 3, 3,
                                 5, 4, 3, 2, 1 };  //  det == 1152

    static std::vector<int> l17{ 2, 1, 1, 0, 0,
                                 1, 2, 1, 1, 0,
                                 1, 1, 2, 1, 1,
                                 0, 1, 1, 2, 1,
                                 0, 0, 1, 1, 2 };  //  det == 4

    static std::vector<int> l18{ 0, 4, 6, 8, 2,
                                 4, 0, 3, 7, 9,
                                 6, 3, 0, 5, 7,
                                 8, 7, 5, 0, 6,
                                 2, 9, 7, 6, 0 };  //  det == -392

    static std::vector<int> l19{ 1, 1, 0, 1, 5,
                                 1, 2, 2, 0, 1,
                                 0, 2, 3, 3, 0,
                                 1, 0, 3, 4, 4,
                                 5, 1, 0, 4, 5 };  //  det == 469
                            
    static std::vector<int> l20{ 0, 1, 2, 3, 4, 5,
                                 1, 0, 1, 2, 3, 4,
                                 2, 1, 0, 1, 2, 3,
                                 3, 2, 1, 0, 1, 2,
                                 4, 3, 2, 1, 0, 1,
                                 5, 4, 3, 2, 1, 0 };  //  det == -80

    static std::vector<int> l21{ 1, 2, 3, 4, 5, 6,
                                 2, 3, 4, 5, 6, 7,
                                 3, 4, 5, 6, 7, 8,
                                 4, 5, 6, 7, 8, 9,
                                 5, 6, 7, 8, 9, 1,
                                 6, 7, 8, 9, 1, 2 };  //  det == 0






}   //  namespace determinanttests

TEST(MatrixTests, Test1)
{
    std::vector<int> data(9, 1);

    matrices::SquareMatrix<int> matrix{3, data.begin(), data.end()};

    for(size_t rowIndx = 0; rowIndx < matrix.size(); ++rowIndx)
    {
        for(size_t colIndx = 0; colIndx < matrix.size(); ++colIndx)
            std::cout << matrix[rowIndx][colIndx] << '\t';
        std::cout << std::endl;   
    }
    EXPECT_EQ(matrix.size(), 3);
}

TEST(MatrixTests, Test2)
{
    const size_t size = 10;
    matrices::SquareMatrix<int> matrix{size};

    for(size_t rowIndx = 0; rowIndx < matrix.size(); ++rowIndx)
    {
        for(size_t colIndx = 0; colIndx < matrix.size(); ++colIndx)
            std::cout << matrix[rowIndx][colIndx] << '\t';
        std::cout << std::endl;   
    }
    EXPECT_EQ(matrix.size(), size);
}


 

