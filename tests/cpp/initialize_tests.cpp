// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

#include <filesystem>
#include <gtest/gtest.h>

#include "initialize.h"
#include "types.h"

// Helper: create a temporary file at the specified filepath with given content
void create_file(const std::string &filepath, const std::string &content) {
    std::ofstream ofs(filepath);
    ofs << content;
}

// Helper: create a temporary file with given content, returns filename
std::string create_file(const std::string &content) {
    std::string filename = "temp_test_file.txt";
    std::ofstream ofs(filename);
    ofs << content;
    return filename;
}

// Helper: delete a file
void delete_file(const std::string &filename) {
    if (std::remove(filename.c_str()) != 0) {
        throw std::runtime_error("Failed to delete file '" + filename + "'.");
    }
}

// No error
TEST(initialize_board, InitCorrectly) {
    std::string dir;
    std::string file;
    dir = "./../board-data/";

    std::filesystem::create_directory(dir);

    file = "num_of_positions.txt";
    create_file(dir + file, "200\n");

    file = "num_of_taxi_connections.txt";
    create_file(dir + file, "3\n");

    file = "num_of_bus_connections.txt";
    create_file(dir + file, "0\n");

    file = "num_of_underground_connections.txt";
    create_file(dir + file, "0\n");

    file = "num_of_ferry_connections.txt";
    create_file(dir + file, "0\n");

    file = "taxi_map.txt";
    create_file(dir + file, "12 34\n99 199\n23 32\n");

    file = "bus_map.txt";
    create_file(dir + file, "");

    file = "underground_map.txt";
    create_file(dir + file, "");

    file = "ferry_map.txt";
    create_file(dir + file, "");

    std::vector<std::vector<std::pair<uint8_t, Ticket>>> board;

    EXPECT_NO_THROW(initialize_board(board));

    EXPECT_EQ(board.size(), 201);
    EXPECT_EQ(board[12][0], std::make_pair(to_uint8(34), TAXI));
    EXPECT_TRUE(board[0].empty());

    std::filesystem::remove_all(dir);
}

// Throw if board not empty
TEST(initialize_board, ThrowIfBoardNotEmpty) {
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> board(1);

    EXPECT_THROW(initialize_board(board), std::invalid_argument);

    try {
        initialize_board(board);
    } catch (const std::invalid_argument &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Expected empty vector") != std::string::npos);
    }
}

// Throw if file missing
TEST(initialize_board, ThrowIfFileMissing) {
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> board;

    EXPECT_THROW(initialize_board(board), std::runtime_error);

    try {
        initialize_board(board);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Could not open file") != std::string::npos);
    }
}

// No error
TEST(initialize_mr_x, InitCorrectly) {
    std::string dir;
    std::string file;
    dir = "./../game-data/";

    std::filesystem::create_directory(dir);

    file = "mr_x_starting_position.txt";
    create_file(dir + file, "2");

    file = "mr_x_tickets.txt";
    create_file(dir + file, "4\n3\n3\n2\n2\n");

    Player mr_x;
    uint8_t positions_count = 3;

    EXPECT_NO_THROW(initialize_mr_x(mr_x, positions_count));

    std::filesystem::remove_all(dir);
}

// Throw if file missing
TEST(initialize_mr_x, ThrowIfFileMissing) {
    Player mr_x;
    uint8_t positions_count = 3;

    EXPECT_THROW(initialize_mr_x(mr_x, positions_count), std::runtime_error);

    try {
        initialize_mr_x(mr_x, positions_count);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Could not open file") != std::string::npos);
    }
}

// Throw if position out of range
TEST(initialize_mr_x, ThrowIfPositionOutOfRange) {
    std::string dir;
    std::string file;
    dir = "./../game-data/";

    std::filesystem::create_directory(dir);

    file = "mr_x_starting_position.txt";
    create_file(dir + file, "2");

    file = "mr_x_tickets.txt";
    create_file(dir + file, "4\n3\n3\n2\n2\n");

    Player mr_x;
    uint8_t positions_count = 1;

    EXPECT_THROW(initialize_mr_x(mr_x, positions_count), std::runtime_error);

    try {
        initialize_mr_x(mr_x, positions_count);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Mr. X position out of valid range") !=
                    std::string::npos);
    }

    std::filesystem::remove_all(dir);
}

// No error
TEST(initialize_detectives, InitCorrectly) {
    std::string dir;
    std::string file;
    dir = "./../game-data/";

    std::filesystem::create_directory(dir);

    file = "num_of_players.txt";
    create_file(dir + file, "4\n");

    file = "detective_tickets.txt";
    create_file(dir + file, "10\n8\n4\n0\n0\n");

    file = "detectives_starting_positions.txt";
    create_file(dir + file, "1\n2\n3\n");

    std::vector<Player> detectives;
    uint8_t positions_count = 4;

    EXPECT_NO_THROW(initialize_detectives(detectives, positions_count));

    EXPECT_EQ(detectives[0].position, 1);
    EXPECT_EQ(detectives[2].position, 3);
    EXPECT_EQ(detectives[0].tickets[0], 10);
    EXPECT_EQ(detectives[1].tickets[2], 4);

    std::filesystem::remove_all(dir);
}

// Throw if file missing
TEST(initialize_detectives, ThrowIfFileMissing) {
    std::vector<Player> detectives;
    uint8_t positions_count = 3;

    EXPECT_THROW(initialize_detectives(detectives, positions_count),
                 std::runtime_error);

    try {
        initialize_detectives(detectives, positions_count);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Could not open file") != std::string::npos);
    }
}

// Throw if position out of range
TEST(initialize_detectives, ThrowIfPositionOutOfRange) {
    std::string dir;
    std::string file;
    dir = "./../game-data/";

    std::filesystem::create_directory(dir);

    file = "num_of_players.txt";
    create_file(dir + file, "4\n");

    file = "detective_tickets.txt";
    create_file(dir + file, "10\n8\n4\n0\n0\n");

    file = "detectives_starting_positions.txt";
    create_file(dir + file, "1\n8\n3\n");

    std::vector<Player> detectives;
    uint8_t positions_count = 4;

    EXPECT_THROW(initialize_detectives(detectives, positions_count),
                 std::runtime_error);

    detectives.clear();

    try {
        initialize_detectives(detectives, positions_count);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Detective position out of valid range") !=
                    std::string::npos);
    }

    std::filesystem::remove_all(dir);
}

// No error
TEST(initialize_mr_x_estimate, InitCorrectly) {
    std::string data_dir;
    std::string game_dir;
    std::string file;

    data_dir = "./../game-data/";
    std::filesystem::create_directory(data_dir);

    file = "mr_x_tickets.txt";
    create_file(data_dir + file, "5\n4\n3\n2\n1\n");

    file = "num_of_players.txt";
    create_file(data_dir + file, "4\n");

    file = "detectives_starting_positions.txt";
    create_file(data_dir + file, "3\n5\n11\n");

    game_dir = "./../board-data/";
    std::filesystem::create_directory(game_dir);

    file = "num_of_general_starting_positions.txt";
    create_file(game_dir + file, "7\n");

    file = "general_starting_positions";
    create_file(game_dir + file, "1\n2\n3\n4\n5\n6\n7\n");

    Estimate estimate;
    uint8_t positions_count = 15;

    EXPECT_NO_THROW(initialize_mr_x_estimate(estimate, positions_count));

    std::filesystem::remove_all(data_dir);
    std::filesystem::remove_all(game_dir);
}

// Throw if file missing
TEST(initialize_mr_x_estimate, ThrowIfFileMissing) {
    Estimate estimate;
    uint8_t positions_count = 10;

    EXPECT_THROW(initialize_mr_x_estimate(estimate, positions_count),
                 std::runtime_error);

    try {
        initialize_mr_x_estimate(estimate, positions_count);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Could not open file") != std::string::npos);
    }
}

// Throw if position out of range
TEST(initialize_mr_x_estimate, ThrowIfPositionOutOfRange) {
    std::string data_dir;
    std::string game_dir;
    std::string file;

    data_dir = "./../game-data/";
    std::filesystem::create_directory(data_dir);

    file = "mr_x_tickets.txt";
    create_file(data_dir + file, "5\n4\n3\n2\n1\n");

    file = "num_of_players.txt";
    create_file(data_dir + file, "4\n");

    file = "detectives_starting_positions.txt";
    create_file(data_dir + file, "3\n5\n11\n");

    game_dir = "./../board-data/";
    std::filesystem::create_directory(game_dir);

    file = "num_of_general_starting_positions.txt";
    create_file(game_dir + file, "7\n");

    file = "general_starting_positions";
    create_file(game_dir + file, "1\n2\n3\n4\n5\n6\n7\n");

    Estimate estimate;
    uint8_t positions_count = 10;

    EXPECT_THROW(initialize_mr_x_estimate(estimate, positions_count),
                 std::runtime_error);

    estimate.positions.clear();
    estimate.tickets.clear();

    try {
        initialize_mr_x_estimate(estimate, positions_count);
    } catch (const std::runtime_error &e) {
        std::string msg = e.what();
        EXPECT_TRUE(msg.find("Position out of valid range") !=
                    std::string::npos);
    }

    std::filesystem::remove_all(data_dir);
    std::filesystem::remove_all(game_dir);
}

// No error
TEST(populate_board, PopulateCorrectly) {
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> board(3);
    std::string file = create_file("2 1\n");

    EXPECT_NO_THROW(populate_board(board, file, 1, TAXI));

    EXPECT_EQ(board[2][0], std::make_pair(to_uint8(1), TAXI));

    delete_file(file);
}

// Throw if position out of range
TEST(populate_board, ThrowIfPositionOutOfRange) {
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> board(3);

    std::string file = create_file("13 1\n");
    EXPECT_THROW(populate_board(board, file, 1, TAXI), std::runtime_error);
    delete_file(file);

    file = create_file("0 14\n");
    EXPECT_THROW(populate_board(board, file, 1, TAXI), std::runtime_error);
    delete_file(file);

    file = create_file("-2 1\n");
    EXPECT_THROW(populate_board(board, file, 1, TAXI), std::invalid_argument);
    delete_file(file);

    file = create_file("1 -4\n");
    EXPECT_THROW(populate_board(board, file, 1, TAXI), std::invalid_argument);
    delete_file(file);
}

// Nothing removed
TEST(vector_diff, NoElementsRemoved) {
    std::vector<uint8_t> minuend = {1, 2, 3};
    std::vector<uint8_t> subtrahend = {4, 5};
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_EQ(result, (std::vector<uint8_t>{1, 2, 3}));
}

// All elements removed
TEST(vector_diff, AllElementsRemoved) {
    std::vector<uint8_t> minuend = {1, 2, 3};
    std::vector<uint8_t> subtrahend = {1, 2, 3};
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_TRUE(result.empty());
}

// Some elements removed
TEST(vector_diff, SomeElementsRemoved) {
    std::vector<uint8_t> minuend = {1, 2, 3, 4, 5};
    std::vector<uint8_t> subtrahend = {2, 4};
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_EQ(result, (std::vector<uint8_t>{1, 3, 5}));
}

// Empty minuend
TEST(vector_diff, EmptyMinuend) {
    std::vector<uint8_t> minuend;
    std::vector<uint8_t> subtrahend = {1, 2};
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_TRUE(result.empty());
}

// Empty subtrahend
TEST(vector_diff, EmptySubtrahend) {
    std::vector<uint8_t> minuend = {1, 2, 3};
    std::vector<uint8_t> subtrahend;
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_EQ(result, (std::vector<uint8_t>{1, 2, 3}));
}

// Both empty
TEST(vector_diff, BothEmpty) {
    std::vector<uint8_t> minuend;
    std::vector<uint8_t> subtrahend;
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_TRUE(result.empty());
}

// Duplicates in minuend
TEST(vector_diff, DuplicatesInMinuend) {
    std::vector<uint8_t> minuend = {1, 2, 2, 3, 4};
    std::vector<uint8_t> subtrahend = {2};
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_EQ(result, (std::vector<uint8_t>{1, 3, 4}));
}

// Unsorted input
TEST(vector_diff, UnsortedInputs) {
    std::vector<uint8_t> minuend = {5, 3, 1, 4, 2};
    std::vector<uint8_t> subtrahend = {4, 2};
    std::vector<uint8_t> result;

    vector_diff(result, minuend, subtrahend);

    EXPECT_EQ(result, (std::vector<uint8_t>{1, 3, 5}));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
