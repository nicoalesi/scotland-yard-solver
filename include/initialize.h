#pragma once

#include <stdexcept>
#include <vector>

#include "input.h"
#include "types.h"

/**
 * @brief Initializes the game board and sets up Mr. X's starting state.
 *
 * This function prepares the internal game state by initializing the game board
 * with connection data and setting the starting position and ticket inventory
 * for Mr. X.
 *
 * @param[out] board A reference to an empty 2D vector that will be resized and
 * populated with connection data between positions.
 * @param[out] mr_x A reference to the Player object representing Mr. X.
 *
 * @throws std::invalid_argument If the `board` is not empty at the start.
 * @throws std::runtime_error If any required file cannot be opened or read.
 * @throws std::runtime_error If the number of positions is not positive.
 * @throws std::runtime_error If Mr. X's starting position is out of bounds.
 * @throws std::runtime_error If any ticket count is negative.
 *
 * @note This function reads from the following files:
 * - `board-data/num_of_positions.txt`
 * - `board-data/num_of_taxi_connections.txt`
 * - `board-data/num_of_bus_connections.txt`
 * - `board-data/num_of_underground_connections.txt`
 * - `board-data/num_of_ferry_connections.txt`
 * - `board-data/taxi_map.txt`
 * - `board-data/bus_map.txt`
 * - `board-data/underground_map.txt`
 * - `board-data/ferry_map.txt`
 * - `game-data/mr_x_starting_position.txt`
 * - `game-data/mr_x_tickets.txt`
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<int, Ticket>>> board;
 * Player mr_x;
 * initialize_game(board, mr_x);
 * // board is now populated, and mr_x is ready for the game
 * @endcode
 */
void initialize_game(std::vector<std::vector<std::pair<int, Ticket>>> &board,
                     Player &mr_x);

/**
 * @brief Populates the game board with connections of a specific ticket type.
 *
 * This function reads a specified number of connections from a file and adds
 * them to the game board.
 *
 * @param[out] board A reference to the adjancency list representing the board.
 * @param[in] filepath Path to the input file containing the list of
 * connections.
 * @param[in] count The number of connections to read from the file. It must be
 * non-negative.
 * @param[in] ticket The ticket type associated with all connections being
 * added.
 *
 * @throws std::invalid_argument If `count` is negative.
 * @throws std::runtime_error If the file does not exist or cannot be opened.
 * @throws std::runtime_error If any connection references a node that is
 * out of the valid range.
 *
 * @note Connections are treated as one-way (directed) edges from `start` to
 * `end`.
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<int, Ticket>>> board(200);
 * populate_board(board, "taxi_map.txt", 300, TAXI);
 * // The board now contains 300 taxi connections.
 * @endcode
 */
void populate_board(std::vector<std::vector<std::pair<int, Ticket>>> &board,
                    const std::string &filepath, int count, Ticket ticket);
