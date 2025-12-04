#pragma once

#include <player.h>


class ChessClock {
public:
    ChessClock(
        Player playerWhite,
        Player playerBlack
    ) 
    : playerWhite(playerWhite)
    , playerBlack(playerBlack)
    , currentPlayer(&playerWhite)
    , running(false) {}

    void start();
    void stop();
    void tick();

    int getTimeRemaining() const;
    bool isRunning() const;

private:
    Player playerWhite;
    Player playerBlack;
    Player* currentPlayer;
    bool running;
};

