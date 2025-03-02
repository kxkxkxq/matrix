cmake_minimum_required(VERSION 3.11)
project(src)

set(INCLUDE_DIR  "${CMAKE_SOURCE_DIR}/include")

add_executable(determinant determinant.cpp)
target_include_directories(determinant PRIVATE ${INCLUDE_DIR})