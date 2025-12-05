#include <Arduino.h>

#include "pin_defines.h"
#include "clock.h"
#include "player.h"
#include "hardware_setup.h"

static Player* playerWhite;
static Player* playerBlack;

void setup(){
    setupHardware();
    playerWhite = new Player(Color::White, PlayerTime(0, 5, 0, optional<uint8_t>(), optional<uint8_t>()));
    playerBlack = new Player(Color::Black, PlayerTime(0, 5, 0, optional<uint8_t>(), optional<uint8_t>()));
    ChessClock::instance = new ChessClock(*playerWhite, *playerBlack);
}

void loop(){
    if (ChessClock::instance && ChessClock::instance->consumeSecondFlag()) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }

}