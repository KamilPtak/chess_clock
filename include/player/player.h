#pragma once

#include "player_time.h"

// Player data structures - represents chess player state
namespace player {

enum class Color { White, Black };

struct PlayerInfo {
  const Color color;
  PlayerTime time;

  PlayerInfo(Color color, const PlayerTime &time) : color(color), time(time) {}

  // Get remaining time as structured format
  RemainingTime get_remaining_time() const { return time.get_remaining_time(); }
};

} // namespace player
