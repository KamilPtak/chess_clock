#include "clock.h"


void ChessClock::start() { running = true; }
void ChessClock::stop() { running = false; }
void ChessClock::tick() {
    auto& remainingTime = currentPlayer->time.remainingSeconds;

    if (running and remainingTime > 0) {
        //TODO: Handle switch between players 
        remainingTime--;
        if (remainingTime == 0) {
            stop();

            return;
        }
        remainingTime += currentPlayer->time.incrementSeconds.value_or(0);
    }
}
int ChessClock::getTimeRemaining() const { /*TODO*/; }
bool ChessClock::isRunning() const { return running; }