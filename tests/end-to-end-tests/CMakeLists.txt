cmake_minimum_required(VERSION 3.11)
project(end_to_end_tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(PYTHON_SCRIPT_RUN "${CMAKE_SOURCE_DIR}/tests/end-to-end-tests/run_e2e_tests.py")

add_test( NAME end_to_end_tests
          COMMAND python3 ${PYTHON_SCRIPT_RUN} )

set_tests_properties( end_to_end_tests 
                      PROPERTIES 
                      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tests/end-to-end-tests" )

add_executable(generator generator.cpp)
target_include_directories(generator PRIVATE ${INCLUDE_DIR})

target_link_libraries(generator ${GTEST_LIBRARIES} gtest_main pthread)