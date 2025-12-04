#pragma once

#include <stdint.h> 
#include <optional.h>


struct PlayerTime {
    PlayerTime(
        uint8_t hours,
        uint8_t minutes,
        uint8_t seconds,
        optional<uint8_t> incrementSeconds, 
        optional<uint8_t> incrementMinutes)
        :incrementSeconds(incrementSeconds.value_or(0) + 60 * incrementMinutes.value_or(0))
        ,initialSeconds(hours * 3600 + minutes * 60 + seconds)
        ,remainingSeconds(initialSeconds)
    {}


    const optional<int> incrementSeconds;
    const int initialSeconds;
    int remainingSeconds;
};