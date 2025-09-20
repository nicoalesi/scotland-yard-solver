#pragma once

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "input.h"
#include "types.h"

/**
 * @brief Initializes the game in Mr. X mode.
 *
 * This function sets up the game board, initializes Mr. X player, and
 * initializes the detective players.
 *
 * @param[out] board The game board adjacency list to initialize. Must be empty.
 * @param[out] mr_x The Mr. X player instance to initialize.
 * @param[out] detectives Vector of detective players to initialize.
 *
 * @throws std::invalid_argument If any output vector is not empty.
 * @throws std::runtime_error If any file cannot be opened or contains invalid
 * data.
 *
 * @note The board size is used to validate player positions.
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<uint8_t, Ticket>>> board;
 * Player mr_x;
 * std::vector<Player> detectives;
 * initialize_game(board, mr_x, detectives);
 * @endcode
 */
void initialize_game(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board, Player &mr_x,
    std::vector<Player> &detectives);

/**
 * @brief Initializes the game in Detectives mode.
 *
 * This function sets up the game board, initializes detective players,
 * and initializes the estimate instance for Mr. X's state.
 *
 * @param[out] board The game board adjacency list to initialize. Must be empty.
 * @param[out] detectives Vector of detective players to initialize.
 * @param[out] estimate The estimate object to initialize.
 *
 * @throws std::invalid_argument If any output vector is not empty.
 * @throws std::runtime_error If any file cannot be opened or contains invalid
 * data.
 *
 * @note The board size is used to validate player positions.
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<uint8_t, Ticket>>> board;
 * std::vector<Player> detectives;
 * Estimate estimate;
 * initialize_game(board, detectives, estimate);
 * @endcode
 */
void initialize_game(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board,
    std::vector<Player> &detectives, Estimate &estimate);

/**
 * @brief Initializes the game in full mode with both Mr. X and Detectives.
 *
 * This function sets up the game board, initializes Mr. X player, detective
 * players, and the estimate of Mr. X's state.
 *
 * @param[out] board The game board adjacency list to initialize. Must be empty.
 * @param[out] mr_x The Mr. X player instance to initialize.
 * @param[out] detectives Vector of detective players to initialize.
 * @param[out] estimate The estimate object to initialize.
 *
 * @throws std::invalid_argument If any output vector is not empty.
 * @throws std::runtime_error If any file cannot be opened or contains invalid
 * data.
 *
 * @note The board size is used to validate player positions.
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<uint8_t, Ticket>>> board;
 * Player mr_x;
 * std::vector<Player> detectives;
 * Estimate estimate;
 * initialize_game(board, mr_x, detectives, estimate);
 * @endcode
 */
void initialize_game(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board, Player &mr_x,
    std::vector<Player> &detectives, Estimate &estimate);

/**
 * @brief Initializes the game board with transportation connections from files.
 *
 * This function constructs the game board by reading and populating the list of
 * connections between positions using various transportation types. The board
 * is represented as an adjacency list, where each node contains a list of
 * connected positions and the corresponding ticket type required to travel.
 *
 * The number of positions and the count of each connection type are read from
 * metadata files.
 *
 * @param[out] board A 2D vector representing the game board as an adjacency
 * list. The function resizes and fills this vector. It must be empty.
 *
 * @throws std::invalid_argument If the `board` vector is not empty.
 * @throws std::runtime_error If any of the required files cannot be opened.
 * @throws std::runtime_error If any file contains fewer lines than expected.
 * @throws std::runtime_error If a line in any input file does not contain valid
 * data.
 * @throws std::invalid_argument If any value read from the files cannot be
 * safely converted to `uint8_t` or `uint16_t`.
 * @throws std::runtime_error If a connection refers to a position out of the
 * valid range of the board.
 *
 * @note Position 0 is unused; valid positions range from 1 to `positions_count`
 * - 1. The board is sized using `positions_count` + 1 to account for the unused
 * 0 index.
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<uint8_t, Ticket>>> board;
 * initialize_board(board);
 * // board is now populated with all route connections
 * @endcode
 */
void initialize_board(
    std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board);

/**
 * @brief Initializes the Mr. X player with starting position and tickets.
 *
 * This function reads configuration data from external files to initialize the
 * `mr_x` player instance. It sets Mr. X's starting position and ticket counts.
 *
 * @param[out] mr_x The player object to initialize for Mr. X.
 * @param[in] positions_count The total number of valid board positions.
 * Used to validate the starting position.
 *
 * @throws std::invalid_argument If `mr_x.tickets` is not empty.
 * @throws std::runtime_error If any required file cannot be opened.
 * @throws std::runtime_error If a file contains invalid or insufficient data.
 * @throws std::invalid_argument If any value read cannot be safely converted
 * to `uint8_t`.
 * @throws std::runtime_error If the starting position is not in the valid
 * range [1, `positions_count` - 1].
 *
 * @note The first position index (0) is unused. All valid positions start from
 * index 1.
 *
 * @example
 * @code
 * Player mr_x;
 * uint8_t total_positions = 255;
 * initialize_mr_x(mr_x, total_positions);
 * // mr_x now contains valid starting position and ticket counts
 * @endcode
 */
void initialize_mr_x(Player &mr_x, uint8_t positions_count);

/**
 * @brief Initializes the list of detective players from game configuration
 * files.
 *
 * This function populates the `detectives` vector,
 * initializing their positions and ticket counts based on external data files.
 *
 * @param[out] detectives A vector to store initialized detective players.
 * The function appends new players to this vector and does not clear it. Must
 * be empty.
 * @param[in] positions_count The total number of valid positions on the board.
 * Used to validate starting positions.
 *
 * @throws std::invalid_argument If the `detectives` vector is not empty.
 * @throws std::runtime_error If any of the required files cannot be opened.
 * @throws std::runtime_error If any file contains fewer lines than expected.
 * @throws std::runtime_error If a line in the input files does not contain a
 * valid integer.
 * @throws std::invalid_argument If any internal vector used in `read_ints` is
 * not empty.
 * @throws std::invalid_argument If a value read from the files cannot be safely
 * converted to `uint8_t` using `to_uint8`.
 * @throws std::runtime_error If any detective's starting position is not in the
 * valid range [1, positions_count - 1].
 *
 * @note Position index 0 is unused. All valid board positions start from 1.
 *
 * @note The `detectives` vector is not cleared before initialization. It is
 * the caller's responsibility to ensure that it is empty or in a valid state
 * prior to the call.
 *
 * @example
 * @code
 * std::vector<Player> detectives;
 * uint8_t total_positions = 255;
 * initialize_detectives(detectives, total_positions);
 * // detectives now contains initialized Player objects for each detective
 * @endcode
 */
void initialize_detectives(std::vector<Player> &detectives,
                           uint8_t positions_count);

/**
 * @brief Initializes the estimate data for Mr. X based on game configuration
 * files.
 *
 * This function populates the `estimate` object with the initial ticket counts
 * and possible starting positions for Mr. X, based on external game and board
 * data files. It reads the full set of general starting positions and removes
 * the ones already used by detectives, calculating the valid initial positions
 * for Mr. X.
 *
 * Ticket counts and player/position information are loaded from structured
 * text files under `./../game-data/` and `./../board-data/`.
 *
 * @param[out] estimate The estimate object to populate.
 * @param[in] positions_count The total number of valid positions on the board.
 * Used to validate all loaded position values.
 *
 * @throws std::invalid_argument If any of the estimate vectors is not empty-
 * @throws std::runtime_error If any of the required files cannot be opened.
 * @throws std::runtime_error If any file contains fewer lines than expected.
 * @throws std::runtime_error If any line in the input files does not contain a
 * valid integer.
 * @throws std::invalid_argument If a value read from the file cannot be safely
 * converted to `uint8_t`.
 * @throws std::runtime_error If any converted position exceeds or equals
 * `positions_count`, indicating an invalid board position.
 *
 * @note This function assumes all required input files are present and contain
 * the correct number of entries, as determined by accompanying metadata files.
 *
 * @note Board position index 0 is reserved and not used for connections or
 * player positions. All valid positions range from 1 to `positions_count` - 1.
 *
 * @example
 * @code
 * Estimate estimate;
 * uint8_t total_positions = 255;
 * initialize_mr_x_estimate(estimate, total_positions);
 * // estimate.tickets and estimate.positions are now initialized
 * @endcode
 */
void initialize_mr_x_estimate(Estimate &estimate, uint8_t positions_count);

/**
 * @brief Populates a board with directed connections and a ticket value.
 *
 * This function reads a specified number of integer pairs from a file, where
 * each pair represents a directed edge from one node to another. The edges are
 * then used to populate the `board`, associating each connection with the
 * given `ticket` value.
 *
 * The board is represented by an adjacency list, where each entry at index `u`
 * contains a list of pairs `(v, ticket)`, representing an edge from `u` to `v`.
 *
 * @param[out] board A 2D vector representing the board.
 * @param[in] filepath Path to the input text file containing integer pairs.
 * Each line must contain two valid integers (start and end of a connection).
 * @param[in] count The number of lines (pairs) to read from the file.
 * @param[in] ticket The ticket value to associate with each connection.
 *
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::runtime_error If any line in the file does not contain exactly
 * two valid integers.
 * @throws std::runtime_error If the file contains fewer than `count` lines.
 * @throws std::invalid_argument If `to_uint8` fails to convert a parsed value
 * into `uint8_t` due to it being out of range.
 * @throws std::runtime_error If any converted position value (`u` or `v`) is
 * out of bounds for the given `board`.
 *
 * @note This function assumes that the `board` vector has already been
 * initialized to an appropriate size and structure. It does not resize or
 * validate the internal shape of the board beyond simple bounds checking.
 *
 * @example
 * @code
 * std::vector<std::vector<std::pair<uint8_t, Ticket>>> board(255);
 * populate_board(board, "connections.txt", 100, Ticket::Standard);
 * // board now has up to 100 connections populated based on the file
 * @endcode
 */
void populate_board(std::vector<std::vector<std::pair<uint8_t, Ticket>>> &board,
                    const std::string &filepath, uint16_t count, Ticket ticket);

/**
 * @brief Computes the difference between two vectors of bytes.
 *
 * This function calculates the set difference between the `minuend` and
 * `subtrahend` vectors (i.e., the elements in `minuend` that are not present
 * in `subtrahend`) and stores the result in the `result` vector.
 *
 * @param[out] result A vector to store the resulting difference. Must be empty
 * when passed to the function.
 * @param[in,out] minuend The main input vector from which elements will be
 * subtracted. It is sorted in-place before processing.
 * @param[in,out] subtrahend The vector containing elements to subtract from
 * `minuend`. It is also sorted in-place.
 *
 * @throws std::invalid_argument If the `result` vector is not empty.
 *
 * @note This function modifies both `minuend` and `subtrahend` by sorting them.
 * If original order must be preserved, pass copies instead.
 *
 * @note The function assumes full ownership of writing to `result`. It does not
 * clear or overwrite its contents; instead, it requires the vector to be empty.
 *
 * @example
 * @code
 * std::vector<uint8_t> minuend = {5, 3, 9, 1};
 * std::vector<uint8_t> subtrahend = {1, 3};
 * std::vector<uint8_t> result;
 * vector_diff(result, minuend, subtrahend);
 * // result now contains: {5, 9}
 * @endcode
 */
void vector_diff(std::vector<uint8_t> &result, std::vector<uint8_t> &minuend,
                 std::vector<uint8_t> &subtrahend);
