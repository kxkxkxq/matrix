#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <numeric>
#include <cmath>

#include "matrix.hpp"

namespace determinanttests
{
//      struct for tests
    template <typename T> struct DetParam
    {
        size_t matrixSize;
        const std::vector<T> matrixVec;
        double result;
    };

//      DETERMINANT TEST DATA
    static std::vector<int> v1(1,1);    //  det == 1
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

    static std::vector<int> v9{ 1, 0, 1, 2,
                                0, 1, 0, 1,
                                1, 0, 1, 0,
                                2, 1, 0, 1 };  //  det == -4
                            
    static std::vector<int> v10{ 0, 1, 1, 1,
                                 1, 0, 1, 1,
                                 1, 1, 0, 1,
                                 1, 1, 1, 0 };  //  det == -3

    static std::vector<int> v11{ 1, 2, 2, 1,
                                 3, 0, 3, 1,
                                 1, 3, 0, 3,
                                 2, 1, 1, 2 };  //  det == 0
    
    static std::vector<int> v12{ 1, 2, 0, 3,
                                 2, 1, 3, 0,
                                 0, 3, 1, 2,
                                 3, 0, 2, 1 };  //  det == 0
                                
    static std::vector<int> v13{ 4, 1, 6, 3,
                                 1, 5, 1, 2,
                                 2, 1, 5, 1,
                                 3, 6, 1, 4 };  //  det == -21

    static std::vector<int> v14{ 9, 9, 1, 0,
                                 1, 6, 5, 9,
                                 0, 0, 1, 9,
                                 9, 9, 5, 6 };  //  det == -1350

    static std::vector<int> v15{ 0, 1, 2, 3, 4,
                                 4, 0, 1, 2, 3,
                                 3, 4, 0, 1, 2,
                                 2, 3, 4, 0, 1,
                                 1, 2, 3, 4, 0 };  //  det == 1250

    static std::vector<int> v16{ 1, 2, 3, 4, 5,
                                 3, 3, 4, 5, 1,
                                 2, 1, 5, 1, 2,
                                 1, 5, 4, 3, 3,
                                 5, 4, 3, 2, 1 };  //  det == 1152

    static std::vector<int> v17{ 2, 1, 1, 0, 0,
                                 1, 2, 1, 1, 0,
                                 1, 1, 2, 1, 1,
                                 0, 1, 1, 2, 1,
                                 0, 0, 1, 1, 2 };  //  det == 4

    static std::vector<int> v18{ 0, 4, 6, 8, 2,
                                 4, 0, 3, 7, 9,
                                 6, 3, 0, 5, 7,
                                 8, 7, 5, 0, 6,
                                 2, 9, 7, 6, 0 };  //  det == -392

    static std::vector<int> v19{ 1, 1, 0, 1, 5,
                                 1, 2, 2, 0, 1,
                                 0, 2, 3, 3, 0,
                                 1, 0, 3, 4, 4,
                                 5, 1, 0, 4, 5 };  //  det == 469
                            
    static std::vector<int> v20{ 0, 1, 2, 3, 4, 5,
                                 1, 0, 1, 2, 3, 4,
                                 2, 1, 0, 1, 2, 3,
                                 3, 2, 1, 0, 1, 2,
                                 4, 3, 2, 1, 0, 1,
                                 5, 4, 3, 2, 1, 0 };  //  det == -80

    static std::vector<int> v21{ 1, 2, 3, 4, 5, 6,
                                 2, 3, 4, 5, 6, 7,
                                 3, 4, 5, 6, 7, 8,
                                 4, 5, 6, 7, 8, 9,
                                 5, 6, 7, 8, 9, 1,
                                 6, 7, 8, 9, 1, 2 };  //  det == 0

    static std::vector<int> v22{ 1, 0, 2, 0, 3, 0,
                                 0, 1, 0, 2, 0, 3,
                                 2, 0, 1, 0, 2, 0,
                                 0, 2, 0, 1, 0, 2,
                                 3, 0, 2, 0, 1, 0,
                                 0, 3, 0, 2, 0, 1 };  //  det == 64

    static std::vector<int> v23{ 1, 2, 1, 3, 4, 5,
                                 2, 1, 2, 4, 3, 4,
                                 1, 2, 1, 5, 4, 3,
                                 1, 2, 3, 1, 3, 5,
                                 2, 3, 4, 5, 1, 3,
                                 3, 4, 5, 3, 5, 1 };  //  det == 552

    static std::vector<int> v24{ 0, 1, 1, 1, 1, 1,
                                 1, 0, 1, 1, 1, 1,
                                 1, 1, 0, 1, 1, 1,
                                 1, 1, 1, 0, 1, 1,
                                 1, 1, 1, 1, 0, 1,
                                 1, 1, 1, 1, 1, 0 };  //  det == -5

    static std::vector<int> v25{ 0, 1, 1, 1, 1, 1, 1,
                                 1, 0, 1, 1, 1, 1, 1,
                                 1, 1, 0, 1, 1, 1, 1,
                                 1, 1, 1, 0, 1, 1, 1,
                                 1, 1, 1, 1, 0, 1, 1,
                                 1, 1, 1, 1, 1, 0, 1,
                                 1, 1, 1, 1, 1, 1, 0 };  //  det == 6

    std::vector<DetParam<int>> matrixDetTestData = { {1, v1, 1},
                                                     {2, v2, 0},
                                                     {10, v3, 0},
                                                     {3, v4, 1},
                                                     {3, v5, 0},
                                                     {3, v6, -12},
                                                     {3, v7, -45},
                                                     {3, v8, 9},
                                                     {4, v9, -4},
                                                     {4, v10, -3},
                                                     {4, v11, 0},
                                                     {4, v12, 0},
                                                     {4, v13, -21},
                                                     {4, v14, -1350},
                                                     {5, v15, 1250},
                                                     {5, v16, 1152},
                                                     {5, v17, 4},
                                                     {5, v18, -392},
                                                     {5, v19, 469},
                                                     {6, v20, -80},
                                                     {6, v21, 0},
                                                     {6, v22, 64},
                                                     {6, v23, 552},
                                                     {6, v24, -5},
                                                     {7, v25, 6} };
}   //  namespace determinanttests

TEST(MatrixTests, Test1)
{
    std::vector<int> data(9, 1);
    matrices::SquareMatrix<int> matrix{3, data.begin(), data.end()};
    EXPECT_EQ(matrix.size(), 3);
}

TEST(MatrixTests, Test2)
{
    const size_t size = 10;
    matrices::SquareMatrix<int> matrix{size};
    EXPECT_EQ(matrix.size(), size);
}

TEST(MatrixTests, Test3)
{
    std::vector<int> data(4);
    std::iota(data.begin(), data.end(), 1);
    matrices::SquareMatrix<int> matrix{2, data.begin(), data.end()};

    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[1][0], 3);
    EXPECT_EQ(matrix[1][1], 4);
}

//      DETERMINANT TESTS
class SquareMatrixTests : public ::testing::TestWithParam<determinanttests::DetParam<int>> {};

TEST_P(SquareMatrixTests, DetTest)
{
    determinanttests::DetParam testParams = GetParam();
    matrices::SquareMatrix<int> matrix{ testParams.matrixSize,
                                        testParams.matrixVec.begin(),
                                        testParams.matrixVec.end() };
    double det1, det2;
    const double epsilon = 1e-6;
    det1 = matrix.determinant();
    det2 = matrix.determinant();

    EXPECT_NEAR(det1, testParams.result, epsilon);
    EXPECT_NEAR(det2, testParams.result, epsilon);
}

INSTANTIATE_TEST_SUITE_P( matrices,
                          SquareMatrixTests,
                          ::testing::ValuesIn(determinanttests::matrixDetTestData) );
