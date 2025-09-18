find_package(GTest REQUIRED)

add_executable(input_tests
    input_tests.cpp
)

add_executable(initialize_tests
    initialize_tests.cpp
)

target_link_libraries(input_tests
    PRIVATE
    input_lib
    GTest::gtest_main
    pthread
)

target_link_libraries(initialize_tests
    PRIVATE
    initialize_lib
    GTest::gtest_main
    pthread
)

include(GoogleTest)
gtest_discover_tests(input_tests)
gtest_discover_tests(initialize_tests)