# matrix
Here is an algorithm for calculating the [determinant](https://en.wikipedia.org/wiki/Determinant) of a [square matrix](https://en.wikipedia.org/wiki/Square_matrix)

## Short description 

### Input
On stdin : matrix size, all matrix elements line by line

### Output
On stdout : the matrix determinant

### Example 
Input : 3, 1, 2, 3, 3, 2, 1, 2, 1, 3

Output : -12


## How to install
use 
```bush
git clone git@github.com:kxkxkxq/matrix.git
``` 
and then 
```bush
cd ./matrix/
```

## How to build
use 
```bush
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
``` 
and then 
```bush
cmake --build build
```

## How to run
to calculate determinant use 
```bush
./build/src/determinant
```
to run unit tests use 
```bush
./build/tests/unit-tests/unit-tests 
```
to run end to end tests use 
```bush
ctest --test-dir ./build
```
