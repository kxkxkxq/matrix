//  this programme generates matrices of a given size and
//  determinant value, which will later be used in e2e tests
//  and outputs the size of the obtained matrix and its elements
//  line by line to stdout 

#include <iostream>

#include "generator.hpp"

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

    double determinant = 0;
    std::cin >> determinant;
    if(std::cin.fail())
    {
        std::cout << "Incorrect input of matrix determinant" << std::endl;
        return 1;
    }  

    e2etests::MatrixGenerator<int> mg{static_cast<size_t>(matrixSize), determinant};
    mg.generate_matrix();
    std::vector<int> resultMatrixVec(mg.get_matrix_vec());
    
    std::cout << matrixSize << std::endl;
    for(auto&& i : resultMatrixVec)
        std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}