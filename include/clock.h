#pragma once
#include "player.h"

class ChessClock {
public:
    static ChessClock* instance;

    ChessClock(Player& white, Player& black);

    void start();
    void stop();
    bool isRunning() const;

    void tick();
    void onSecondInterrupt();

    static volatile bool secondElapsed;
    static void notifySecond();
    bool consumeSecondFlag();

    void handleInterruptFlags();

    Player* currentPlayer;
    Player& whitePlayer;
    Player& blackPlayer;

    bool running = false;
};
