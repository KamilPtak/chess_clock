#pragma once

#include "player_time.h"


enum class Color {
    White,
    Black
};


struct Player {
    const Color color;
    PlayerTime time;

    Player(Color color, PlayerTime time)
        : color(color), time(time)
    {}
};
