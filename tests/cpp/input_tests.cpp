#include <gtest/gtest.h>

#include "input.h"


// Helper: create a temporary file with given content, returns filename
std::string create_file(const std::string& content) {
    std::string filename = "temp_test_file.txt";
    std::ofstream ofs(filename);
    ofs << content;
    return filename;
}


// Helper: delete a file
void delete_file(const std::string& filename) {
    if (std::remove(filename.c_str()) != 0) {
        throw std::runtime_error("Failed to delete file '" + filename + "'.");
    }
}


// No error
TEST(read_ints, ReadCorrectly) {
    std::string file = create_file("10\n20\n30\n");

    std::vector<int> result;
    ASSERT_NO_THROW(read_ints(result, file, 3));
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);

    delete_file(file);
}


// Error if vector not empty
TEST(read_ints, ThrowIfVectorNotEmpty) {
    std::vector<int> result = {1, 2};
    EXPECT_THROW(read_ints(result, "anyfile.txt", 1), std::invalid_argument);
}


// Error if file does not exist
TEST(read_ints, ThrowIfFileMissing) {
    std::vector<int> result;
    EXPECT_THROW(read_ints(result, "nonexistent_file.txt", 1), std::runtime_error);
}


// Error if invalid integer in file
TEST(read_ints, ThrowIfInvalidInteger) {
    std::string file = create_file("10\nabc\n30\n");

    std::vector<int> result;
    EXPECT_THROW(read_ints(result, file, 3), std::runtime_error);
    result.clear();

    try {   
        read_ints(result, file, 3);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Invalid integer on line 2") != std::string::npos);
    }

    delete_file(file);
}


// Error if file has fewer lines than requested
TEST(read_ints, ThrowIfNotEnoughLines) {
    std::string file = create_file("10\n20\n");

    std::vector<int> result;
    EXPECT_THROW(read_ints(result, file, 3), std::runtime_error);
    result.clear();

    try {
        read_ints(result, file, 3);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Expected 3 lines but got 2") != std::string::npos);
    }

    delete_file(file);
}


// No error
TEST(read_int_pairs, ReadCorrectly) {
    std::string file = create_file(
        "1 2\n"
        "3 4\n"
        "5 6\n"
    );

    std::vector<std::pair<int, int>> result;
    ASSERT_NO_THROW(read_int_pairs(result, file, 3));
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], std::make_pair(1, 2));
    EXPECT_EQ(result[1], std::make_pair(3, 4));
    EXPECT_EQ(result[2], std::make_pair(5, 6));

    delete_file(file);
}


// Error if vector not empty
TEST(read_int_pairs, ThrowIfVectorNotEmpty) {
    std::vector<std::pair<int, int>> result = {{1, 2}, {3, 4}};
    EXPECT_THROW(read_int_pairs(result, "anyfile.txt", 1), std::invalid_argument);
}


// Error if file does not exist
TEST(read_int_pairs, ThrowIfFileMissing) {
    std::vector<std::pair<int, int>> result;
    EXPECT_THROW(read_int_pairs(result, "nonexistent_file.txt", 1), std::runtime_error);
}


// Error if invalid integer pair in file
TEST(read_int_pairs, ThrowIfInvalidIntegerPair) {
    std::string file = create_file(
        "10 11\n"
        "abc\n"
        "30 21\n"
    );

    std::vector<std::pair<int, int>> result;
    EXPECT_THROW(read_int_pairs(result, file, 3), std::runtime_error);
    result.clear();

    try {   
        read_int_pairs(result, file, 3);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Invalid integer pair on line 2") != std::string::npos);
    }

    delete_file(file);
    file = create_file(
        "10 11\n"
        "12 9\n"
        "30\n"
    );

    result.clear();
    EXPECT_THROW(read_int_pairs(result, file, 3), std::runtime_error);
    result.clear();

    try {   
        read_int_pairs(result, file, 3);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Invalid integer pair on line 3") != std::string::npos);
    }

    delete_file(file);
    file = create_file(
        "10 \n"
        "11 12\n"
        "30\n"
    );

    result.clear();
    EXPECT_THROW(read_int_pairs(result, file, 3), std::runtime_error);
    result.clear();
    
    try {   
        read_int_pairs(result, file, 3);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Invalid integer pair on line 1") != std::string::npos);
    }

    delete_file(file);
}


// Error if file has fewer lines than requested
TEST(read_int_pairs, ThrowIfNotEnoughLines) {
    std::string file = create_file("10 9\n");

    std::vector<std::pair<int, int>> result;
    EXPECT_THROW(read_int_pairs(result, file, 3), std::runtime_error);
    result.clear();

    try {
        read_int_pairs(result, file, 3);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Expected 3 lines but got 1") != std::string::npos);
    }

    delete_file(file);
}