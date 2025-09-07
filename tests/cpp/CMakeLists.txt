find_package(GTest REQUIRED)

set( TEST_RESOURCES
    input_tests.cpp
)

add_executable(unit_tests ${TEST_RESOURCES})

target_link_libraries(unit_tests PRIVATE input_lib GTest::gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(unit_tests)