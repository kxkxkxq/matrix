#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "matrix.hpp"

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
 

