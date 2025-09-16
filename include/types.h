#pragma once

#include <vector>

enum Ticket {
    TAXI,
    BUS,
    UNDERGROUND,
    BLACK,
    DOUBLE_MOVE,
};

struct Player {
    int position;
    std::vector<int> tickets;
};
