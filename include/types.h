#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

/**
 * @brief Represents the types of transportation tickets available in the game.
 *
 * Each ticket corresponds to a mode of transportation or a special move.
 * Players use tickets to traverse the game board via various connections.
 */
enum Ticket : uint8_t {
    /// Taxi ticket — used for short-distance travel via taxi routes.
    TAXI,
    /// Bus ticket — used for medium-distance travel via bus routes.
    BUS,
    /// Underground ticket — used for long-distance travel via underground
    /// routes.
    UNDERGROUND,
    /// Black ticket — a wildcard ticket allowing travel via any route (Mr. X
    /// only).
    BLACK,
    /// Double-move ticket — allows Mr. X to move twice in a single turn (Mr. X
    /// only).
    DOUBLE_MOVE,
};

/**
 * @brief Represents a player in the game, either Mr. X or a detective.
 *
 * Stores the current position of the player and their available tickets.
 */
struct Player {
    /// The player's current location on the board.
    uint8_t position = 0;
    /// Number of tickets for each type, indexed by the Ticket enum.
    std::vector<uint8_t> tickets;
};

/**
 * @brief Represents an estimate of Mr. X's possible tickets and positions.
 *
 * Positions start from index 1.
 */
struct Estimate {
    /// Counts of Mr. X's available tickets
    std::vector<uint8_t> tickets;
    /// Possible board positions of Mr. X
    std::vector<uint8_t> positions;
};

/**
 * @brief Safely converts a signed 32-bit integer to an unsigned 8-bit integer.
 *
 * @param[in] n The int32_t value to convert.
 *
 * @return The converted uint8_t value.
 *
 * @throws std::invalid_argument If `n` is less than 0 or greater than 255.
 *
 * @note This function prevents data loss by validating the input range before
 * conversion.
 */
uint8_t to_uint8(int32_t n);

/**
 * @brief Safely converts a size_t value to an unsigned 8-bit integer.
 *
 * @param[in] n The size_t value to convert.
 *
 * @return The converted uint8_t value.
 *
 * @throws std::invalid_argument If `n` is greater than 255.
 *
 * @note This function prevents data loss by validating the input range before
 * conversion.
 */
uint8_t to_uint8(size_t n);

/**
 * @brief Safely converts a signed 32-bit integer to an unsigned 16-bit integer.
 *
 * @param[in] n The int32_t value to convert.
 *
 * @return The converted uint16_t value.
 *
 * @throws std::invalid_argument If `n` is less than 0 or greater than 65535.
 *
 * @note This function prevents data loss by validating the input range before
 * conversion.
 */
uint16_t to_uint16(int32_t n);

/**
 * @brief Safely converts a signed 32-bit integer to an unsigned 32-bit integer.
 *
 * @param[in] n The int32_t value to convert.
 *
 * @return The converted uint32_t value.
 *
 * @throws std::invalid_argument If `n` is less than 0.
 *
 * @note This function prevents data loss by validating the input range before
 * conversion.
 */
uint32_t to_uint32(int32_t n);
