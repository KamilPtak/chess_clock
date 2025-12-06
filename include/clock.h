#pragma once
#include "player/player.h"

// Chess clock logic - manages game time for both players
namespace chess_clock {

class Clock {
public:
  static Clock *instance;

  Clock(player::PlayerInfo &white, player::PlayerInfo &black,
        uint16_t timerIntervalMs = 1000);

  void start();
  void stop();
  bool isRunning() const;

  void tick();
  void onSecondInterrupt();

  static volatile bool secondElapsed;
  static void notifySecond();
  bool consumeSecondFlag();

  void handleInterruptFlags();

  player::PlayerInfo *currentPlayer;
  player::PlayerInfo &whitePlayer;
  player::PlayerInfo &blackPlayer;

  uint16_t timerIntervalMs;
  bool running = false;
};

} // namespace chess_clock
