#include <iostream>
#include <vector>

#include "matrix.hpp"

int main()
{
    long long matrixSize = 0;
    std::cin >> matrixSize;
    if(std::cin.fail() || (matrixSize < 0) )
    {
        std::cout << "Incorrect input of matrix size" << std::endl;
        if(matrixSize < 0)
            std::cerr << "The matrix size must not be less than 0" << std::endl;
        return 1;
    }
    size_t vecSize = static_cast<size_t>(matrixSize * matrixSize);
    
    std::vector<int> matrixVec;
    matrixVec.reserve(vecSize);
    for(auto i = 0; i < vecSize; ++i)
    {
        int elem = 0;
        std::cin >> elem;
        if(std::cin.fail())
        {
            std::cout << "Incorrect input of matrix element" << std::endl;
            return 1;
        }
        matrixVec.push_back(elem);
    }
    
    matrices::SquareMatrix<int> matrix{static_cast<size_t>(matrixSize), matrixVec.begin(), matrixVec.end()};
    std::cout << matrix.determinant() << std::endl;
    
    return 0;    
}