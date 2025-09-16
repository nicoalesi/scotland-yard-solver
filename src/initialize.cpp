#include "initialize.h"
#include "input.h"
#include "types.h"

void initialize_game(std::vector<std::vector<std::pair<int, Ticket>>>& board,
                     Player& mr_x) {

    if (!board.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    int positions_count = read_int("./board-data/num_of_positions.txt");
    int taxi_connections_count = read_int("./board-data/num_of_taxi_connections.txt");
    int bus_connections_count = read_int("./board-data/num_of_bus_connections.txt");
    int underground_connections_count = read_int("./board-data/num_of_underground_connections.txt");
    int ferry_connections_count = read_int("./board-data/num_of_ferry_connections.txt");

    board.resize(positions_count);

    populate_board(board, "./board-data/taxi_map.txt", taxi_connections_count, TAXI);
    populate_board(board, "./board-data/bus_map.txt", bus_connections_count, BUS);
    populate_board(board, "./board-data/underground_map.txt", underground_connections_count, UNDERGROUND);
    populate_board(board, "./board-data/ferry_map.txt", ferry_connections_count, BLACK);

    mr_x.position = read_int("./game-data/mr_x_starting_position.txt");
    read_ints(mr_x.tickets, "./game-data/mr_x_tickets.txt", 5);

    if (mr_x.position < 0 || mr_x.position >= positions_count) {
        throw std::runtime_error("Mr. X position out of valid range.");
    }

    for (const auto& ticket_count : mr_x.tickets) {
        if (ticket_count < 0) {
            throw std::runtime_error("Number of tickets cannot be negative.");
        }
    }

    return;
}

void initialize_game(std::vector<std::vector<std::pair<int, Ticket>>> board,
                     std::vector<Player> detectives) {

    return;
}

void initialize_game(std::vector<std::vector<std::pair<int, Ticket>>> board,
                     Player mr_x, std::vector<Player> detectives) {

    return;
}

void populate_board(std::vector<std::vector<std::pair<int, Ticket>>>& board, const std::string& filepath, int count, Ticket ticket) {
    if (count < 0) {
        throw std::invalid_argument("Expected non-negative value as count.");
    }

    std::vector<std::pair<int, int>> connections;

    read_int_pairs(connections, filepath, count);
    for (const auto& [start, end] : connections) {
        if (start < 0 || end < 0 || (size_t)(start) >= board.size() || (size_t)(end) >= board.size()) {
            throw std::runtime_error("Node value out of valid range.");
        }

        board[start].emplace_back(end, ticket);
    }
}