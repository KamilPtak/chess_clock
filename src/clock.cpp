#include "clock.h"
#include <avr/interrupt.h>

extern volatile bool whitePressed;
extern volatile bool blackPressed;

volatile bool ChessClock::secondElapsed = false;
ChessClock* ChessClock::instance = nullptr;

ChessClock::ChessClock(Player& white, Player& black)
    : whitePlayer(white), blackPlayer(black)
{
    currentPlayer = &whitePlayer;
}

void ChessClock::start() {
    running = true;
}

void ChessClock::stop() {
    running = false;
}

bool ChessClock::isRunning() const {
    return running;
}

void ChessClock::handleInterruptFlags() {
    if (whitePressed and currentPlayer->color == Color::White) {
        whitePressed = false;
        currentPlayer->time.remainingSeconds +=
            currentPlayer->time.incrementSeconds.value_or(0);
        currentPlayer = &blackPlayer;
        return;
    }

    if (blackPressed and currentPlayer->color == Color::Black) {
        blackPressed = false;
        currentPlayer->time.remainingSeconds +=
            currentPlayer->time.incrementSeconds.value_or(0);
        currentPlayer = &whitePlayer;
        return;
    }
}

void ChessClock::tick() {
    if (!running)
        return;

    handleInterruptFlags();

    int& t = currentPlayer->time.remainingSeconds;

    if (t > 0) {
        t--;

        if (t <= 0) {
            t = 0;
            stop();
        }
    }
}

void ChessClock::notifySecond() {
    secondElapsed = true;
}

void ChessClock::onSecondInterrupt() {
    notifySecond();
}

bool ChessClock::consumeSecondFlag() {
    if (secondElapsed) {
        secondElapsed = false;
        return true;
    }
    return false;
}
