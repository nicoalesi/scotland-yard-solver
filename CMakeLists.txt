cmake_minimum_required(VERSION 3.14)
project(ScotlandYardSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SANITIZE_FLAGS
    -fsanitize=address,undefined,leak
    -fno-omit-frame-pointer
)
set(WARNING_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Werror
)

add_compile_options(
    ${SANITIZE_FLAGS}
    ${WARNING_FLAGS}
)

add_link_options(
    ${SANITIZE_FLAGS}
)

add_library(input_lib
    src/input.cpp
)
target_include_directories(input_lib
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

option(BUILD_TESTING
    "Enable tests builds"
    OFF
)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests/cpp)
endif()