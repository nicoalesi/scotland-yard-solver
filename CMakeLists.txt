cmake_minimum_required(VERSION 3.14)
project(ScotlandYardSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_library(input_lib src/input.cpp)
target_include_directories(input_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(tests/cpp)