#pragma once

#include <cstdint>
#include <vector>

/**
 * @brief Represents the types of transportation tickets available in the game.
 *
 * Each ticket corresponds to a mode of transportation or a special move.
 * Players use tickets to traverse the game board via various connections.
 */
enum Ticket : std::uint8_t {
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
    int position = 0;
    /// Number of tickets for each type, indexed by the Ticket enum.
    std::vector<int> tickets;
};
