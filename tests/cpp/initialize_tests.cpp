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
TEST(initialize_game, InitCorrectly) {
    std::filesystem::create_directories("./../board-data");
    std::filesystem::create_directories("./../game-data");

    create_file("./../board-data/num_of_positions.txt", "2\n");
    create_file("./../board-data/num_of_taxi_connections.txt", "1\n");
    create_file("./../board-data/num_of_bus_connections.txt", "0\n");
    create_file("./../board-data/num_of_underground_connections.txt", "0\n");
    create_file("./../board-data/num_of_ferry_connections.txt", "0\n");

    create_file("./../board-data/taxi_map.txt", "0 1\n");
    create_file("./../board-data/bus_map.txt", "");
    create_file("./../board-data/underground_map.txt", "");
    create_file("./../board-data/ferry_map.txt", "");

    create_file("./../game-data/mr_x_starting_position.txt", "1\n");
    create_file("./../game-data/mr_x_tickets.txt", "4\n3\n2\n1\n0\n");

    std::vector<std::vector<std::pair<int, Ticket>>> board;
    Player mr_x;

    ASSERT_NO_THROW(initialize_game(board, mr_x));
    EXPECT_EQ(board.size(), 2);
    EXPECT_EQ(mr_x.position, 1);
    EXPECT_EQ(mr_x.tickets.size(), 5);
    EXPECT_EQ(mr_x.tickets[0], 4);
    EXPECT_EQ(mr_x.tickets[4], 0);

    std::filesystem::remove_all("./../board-data");
    std::filesystem::remove_all("./../game-data");
}

// Error if board not empty
TEST(initialize_game, ThrowIfBoardNotEmpty) {
    std::vector<std::vector<std::pair<int, Ticket>>> board(1);
    Player mr_x;

    EXPECT_THROW(initialize_game(board, mr_x), std::invalid_argument);
}

// Error if value of positions negative
TEST(initialize_game, ThrowIfPositionsNegative) {
    std::filesystem::create_directories("./../board-data");
    std::filesystem::create_directories("./../game-data");

    create_file("./../board-data/num_of_positions.txt", "-1\n");
    create_file("./../board-data/num_of_taxi_connections.txt", "1\n");
    create_file("./../board-data/num_of_bus_connections.txt", "0\n");
    create_file("./../board-data/num_of_underground_connections.txt", "0\n");
    create_file("./../board-data/num_of_ferry_connections.txt", "0\n");

    create_file("./../board-data/taxi_map.txt", "0 1\n");
    create_file("./../board-data/bus_map.txt", "");
    create_file("./../board-data/underground_map.txt", "");
    create_file("./../board-data/ferry_map.txt", "");

    create_file("./../game-data/mr_x_starting_position.txt", "1\n");
    create_file("./../game-data/mr_x_tickets.txt", "4\n3\n2\n1\n0\n");

    std::vector<std::vector<std::pair<int, Ticket>>> board;
    Player mr_x;

    EXPECT_THROW(initialize_game(board, mr_x), std::runtime_error);

    std::filesystem::remove_all("./../board-data");
    std::filesystem::remove_all("./../game-data");
}

// Error if Mr. X position out of range
TEST(initialize_game, ThrowIfMrXPositionOutOfRange) {
    std::filesystem::create_directories("./../board-data");
    std::filesystem::create_directories("./../game-data");

    create_file("./board-data/num_of_positions.txt", "3\n");
    create_file("./board-data/num_of_taxi_connections.txt", "0\n");
    create_file("./board-data/num_of_bus_connections.txt", "0\n");
    create_file("./board-data/num_of_underground_connections.txt", "0\n");
    create_file("./board-data/num_of_ferry_connections.txt", "0\n");

    create_file("./board-data/taxi_map.txt", "");
    create_file("./board-data/bus_map.txt", "");
    create_file("./board-data/underground_map.txt", "");
    create_file("./board-data/ferry_map.txt", "");

    create_file("./game-data/mr_x_starting_position.txt", "10\n");
    create_file("./game-data/mr_x_tickets.txt", "1\n1\n1\n1\n1\n");

    std::vector<std::vector<std::pair<int, Ticket>>> board;
    Player mr_x;

    EXPECT_THROW(initialize_game(board, mr_x), std::runtime_error);

    std::filesystem::remove_all("./../board-data");
    std::filesystem::remove_all("./../game-data");
}

// Error if negative ticket count
TEST(initialize_game, ThrowIfNegativeTicketCount) {
    std::filesystem::create_directories("./../board-data");
    std::filesystem::create_directories("./../game-data");

    create_file("./board-data/num_of_positions.txt", "3\n");
    create_file("./board-data/num_of_taxi_connections.txt", "0\n");
    create_file("./board-data/num_of_bus_connections.txt", "0\n");
    create_file("./board-data/num_of_underground_connections.txt", "0\n");
    create_file("./board-data/num_of_ferry_connections.txt", "0\n");

    create_file("./board-data/taxi_map.txt", "");
    create_file("./board-data/bus_map.txt", "");
    create_file("./board-data/underground_map.txt", "");
    create_file("./board-data/ferry_map.txt", "");

    create_file("./game-data/mr_x_starting_position.txt", "1\n");
    create_file("./game-data/mr_x_tickets.txt", "1\n1\n-1\n1\n1\n"); // Invalid

    std::vector<std::vector<std::pair<int, Ticket>>> board;
    Player mr_x;

    EXPECT_THROW(initialize_game(board, mr_x), std::runtime_error);

    std::filesystem::remove_all("./../board-data");
    std::filesystem::remove_all("./../game-data");
}

// No error
TEST(populate_board, PopulateCorrectly) {
    std::string file = create_file("0 1\n1 2\n2 3\n");
    std::vector<std::vector<std::pair<int, Ticket>>> board(4);

    ASSERT_NO_THROW(populate_board(board, file, 3, TAXI));

    ASSERT_EQ(board[0].size(), 1);
    EXPECT_EQ(board[0][0].first, 1);
    EXPECT_EQ(board[0][0].second, TAXI);

    ASSERT_EQ(board[1].size(), 1);
    EXPECT_EQ(board[1][0].first, 2);
    EXPECT_EQ(board[1][0].second, TAXI);

    ASSERT_EQ(board[2].size(), 1);
    EXPECT_EQ(board[2][0].first, 3);
    EXPECT_EQ(board[2][0].second, TAXI);

    delete_file(file);
}

// Error if negative count
TEST(populate_board, ThrowIfNegativeCount) {
    std::vector<std::vector<std::pair<int, Ticket>>> board;
    EXPECT_THROW(populate_board(board, "anyfile.txt", -1, BUS),
                 std::invalid_argument);
}

// Error if node out of range
TEST(populate_board, ThrowIfNodeOutOfRange) {
    std::vector<std::vector<std::pair<int, Ticket>>> board(3);

    std::string file = create_file("0 5\n");
    EXPECT_THROW(populate_board(board, file, 1, UNDERGROUND),
                 std::runtime_error);
    delete_file(file);

    file = create_file("0 -1\n");
    EXPECT_THROW(populate_board(board, file, 1, UNDERGROUND),
                 std::runtime_error);
    delete_file(file);

    file = create_file("-10 1\n");
    EXPECT_THROW(populate_board(board, file, 1, UNDERGROUND),
                 std::runtime_error);
    delete_file(file);

    file = create_file("4 2\n");
    EXPECT_THROW(populate_board(board, file, 1, UNDERGROUND),
                 std::runtime_error);
    delete_file(file);
}
