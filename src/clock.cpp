#include "clock.h"
#include <avr/interrupt.h>

extern volatile bool whitePressed;
extern volatile bool blackPressed;

namespace chess_clock {

volatile bool Clock::secondElapsed = false;
Clock *Clock::instance = nullptr;

Clock::Clock(player::PlayerInfo &white, player::PlayerInfo &black,
             uint16_t timerIntervalMs)
    : whitePlayer(white), blackPlayer(black), timerIntervalMs(timerIntervalMs) {
  currentPlayer = &whitePlayer;
}

void Clock::start() { running = true; }

void Clock::stop() { running = false; }

bool Clock::isRunning() const { return running; }

void Clock::handleInterruptFlags() {
  if (whitePressed and currentPlayer->color == player::Color::White) {
    whitePressed = false;
    currentPlayer->time.increaseBySeconds(
        currentPlayer->time.getIncrementSeconds());
    currentPlayer = &blackPlayer;
    return;
  }

  if (blackPressed and currentPlayer->color == player::Color::Black) {
    blackPressed = false;
    currentPlayer->time.increaseBySeconds(
        currentPlayer->time.getIncrementSeconds());
    currentPlayer = &whitePlayer;
    return;
  }
}

void Clock::tick() {
  if (!running)
    return;

  handleInterruptFlags();

  if (currentPlayer->time.getRemainingMilliseconds() <= timerIntervalMs) {
    currentPlayer->time.decreaseByMilliseconds(
        currentPlayer->time.getRemainingMilliseconds());
    stop();
  } else {
    currentPlayer->time.decreaseByMilliseconds(timerIntervalMs);
  }
}

void Clock::notifySecond() { secondElapsed = true; }

void Clock::onSecondInterrupt() { notifySecond(); }

bool Clock::consumeSecondFlag() {
  if (secondElapsed) {
    secondElapsed = false;
    return true;
  }
  return false;
}

} // namespace chess_clock
