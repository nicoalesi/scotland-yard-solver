#include "initialize.h"

constexpr uint8_t NUM_OF_TICKETS = 5;

void initialize_game(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board, Player &mr_x,
    std::vector<Player> &detectives) {

    initialize_board(board);
    initialize_mr_x(mr_x, to_uint8(board.size()));
    initialize_detectives(detectives, to_uint8(board.size()));
}

void initialize_game(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board,
    std::vector<Player> &detectives, Estimate &estimate) {

    initialize_board(board);
    initialize_detectives(detectives, to_uint8(board.size()));
    initialize_mr_x_estimate(estimate, to_uint8(board.size()));
}

void initialize_game(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board, Player &mr_x,
    std::vector<Player> &detectives, Estimate &estimate) {
    initialize_board(board);
    initialize_mr_x(mr_x, to_uint8(board.size()));
    initialize_detectives(detectives, to_uint8(board.size()));
    initialize_mr_x_estimate(estimate, to_uint8(board.size()));
}

void initialize_board(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board) {
    if (!board.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    std::string dir;
    std::string file;

    dir = "./../board-data/";

    file = "num_of_positions.txt";
    uint8_t positions_count = to_uint8(read_int(dir + file) + 1);

    file = "num_of_taxi_connections.txt";
    uint16_t taxi_routes_count = to_uint16(read_int(dir + file));

    file = "num_of_bus_connections.txt";
    uint16_t bus_routes_count = to_uint16(read_int(dir + file));

    file = "num_of_underground_connections.txt";
    uint16_t underground_routes_count = to_uint16(read_int(dir + file));

    file = "num_of_ferry_connections.txt";
    uint16_t ferry_routes_count = to_uint16(read_int(dir + file));

    board.resize(positions_count);

    file = "taxi_map.txt";
    populate_board(board, dir + file, taxi_routes_count, TAXI);

    file = "bus_map.txt";
    populate_board(board, dir + file, bus_routes_count, BUS);

    file = "underground_map.txt";
    populate_board(board, dir + file, underground_routes_count, UNDERGROUND);

    file = "ferry_map.txt";
    populate_board(board, dir + file, ferry_routes_count, BLACK);
}

void initialize_mr_x(Player &mr_x, uint8_t positions_count) {
    if (!mr_x.tickets.empty()) {
        throw std::invalid_argument("Expected struct vector to be empty.");
    }

    std::string dir;
    std::string file;
    dir = "./../game-data/";

    std::vector<int32_t> tickets;

    file = "mr_x_starting_position.txt";
    uint8_t position = to_uint8(read_int(dir + file));

    if (positions_count <= position) {
        throw std::runtime_error("Mr. X position out of valid range.");
    }

    file = "mr_x_tickets.txt";
    read_ints(tickets, dir + file, NUM_OF_TICKETS);

    mr_x.position = position;
    for (const auto &ticket_count : tickets) {
        mr_x.tickets.emplace_back(to_uint8(ticket_count));
    }
}

void initialize_detectives(std::vector<Player> &detectives,
                           uint8_t positions_count) {
    if (!detectives.empty()) {
        throw std::invalid_argument("Expected detectives vector to be empty.");
    }

    std::string dir;
    std::string file;
    dir = "./../game-data/";

    file = "num_of_players.txt";
    uint8_t num_of_detectives = to_uint8(read_int(dir + file) - 1);

    std::vector<int32_t> tickets;

    file = "detective_tickets.txt";
    read_ints(tickets, dir + file, NUM_OF_TICKETS);

    std::vector<int32_t> starting_positions;

    file = "detectives_starting_positions.txt";
    read_ints(starting_positions, dir + file, num_of_detectives);

    for (uint8_t i = 0; i < num_of_detectives; i++) {
        uint8_t spawn = to_uint8(starting_positions[i]);

        if (positions_count <= spawn) {
            throw std::runtime_error("Detective position out of valid range.");
        }

        Player detective;
        detective.position = spawn;

        for (const auto &ticket_count : tickets) {
            detective.tickets.emplace_back(to_uint8(ticket_count));
        }

        detectives.emplace_back(detective);
    }
}

void initialize_mr_x_estimate(Estimate &estimate, uint8_t positions_count) {
    if (!estimate.positions.empty() || !estimate.tickets.empty()) {
        throw std::invalid_argument("Expected estimate vectors to be empty.");
    }

    std::string dir;
    std::string file;
    dir = "./../game-data/";

    std::vector<int32_t> tickets;

    file = "mr_x_tickets.txt";
    read_ints(tickets, dir + file, NUM_OF_TICKETS);

    for (const auto &ticket_count : tickets) {
        estimate.tickets.emplace_back(to_uint8(ticket_count));
    }

    dir = "./../board-data/";
    file = "num_of_general_starting_positions.txt";
    uint8_t count = to_uint8(read_int(dir + file));

    std::vector<int32_t> all_starting_positions;
    std::vector<int32_t> detectives_starting_positions;

    file = "general_starting_positions";
    read_ints(all_starting_positions, dir + file, count);

    dir = "./../game-data/";

    file = "num_of_players.txt";
    uint8_t used_count = to_uint8(read_int(dir + file) - 1);

    file = "detectives_starting_positions.txt";
    read_ints(detectives_starting_positions, dir + file, used_count);

    std::vector<uint8_t> all_spawns;
    std::vector<uint8_t> used_spawns;

    for (const auto &position : all_starting_positions) {
        uint8_t spawn = to_uint8(position);

        if (positions_count <= spawn) {
            throw std::runtime_error("Position out of valid range.");
        }

        all_spawns.push_back(spawn);
    }

    for (const auto &position : detectives_starting_positions) {
        uint8_t spawn = to_uint8(position);

        if (positions_count <= spawn) {
            throw std::runtime_error("Position out of valid range.");
        }

        used_spawns.push_back(spawn);
    }

    vector_diff(estimate.positions, all_spawns, used_spawns);
}

void populate_board(std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board,
                    const std::string &filepath, uint16_t count,
                    Ticket ticket) {

    std::vector<std::pair<int32_t, int32_t>> connections;

    read_int_pairs(connections, filepath, count);
    for (const auto &[start, end] : connections) {
        // NOLINTBEGIN(readability-identifier-length)

        uint8_t u = to_uint8(start);
        uint8_t v = to_uint8(end);

        // NOLINTEND(readability-identifier-length)

        if (board.size() <= u || board.size() <= v) {
            throw std::runtime_error("Position value out of valid range.");
        }

        board[u].emplace_back(v, ticket);
    }
}

void vector_diff(std::vector<uint8_t> &result, std::vector<uint8_t> &minuend,
                 std::vector<uint8_t> &subtrahend) {
    if (!result.empty()) {
        throw std::invalid_argument(
            "Expected empty vector as output parameter.");
    }

    sort(minuend.begin(), minuend.end());
    sort(subtrahend.begin(), subtrahend.end());

    // NOLINTBEGIN(readability-identifier-length)

    uint8_t i = 0;
    uint8_t j = 0;

    // NOLINTEND(readability-identifier-length)

    while (i < minuend.size() && j < subtrahend.size()) {
        if (minuend[i] == subtrahend[j]) {
            i++;
        } else if (minuend[i] < subtrahend[j]) {
            result.emplace_back(minuend[i]);
            i++;
        } else {
            j++;
        }
    }

    while (i < minuend.size()) {
        result.emplace_back(minuend[i]);
        i++;
    }
}
