#include <Arduino.h>

#include "pin_defines.h"
#include "clock.h"
#include "player.h"


Player playerWhite(Color::White, PlayerTime(0, 5, 0, optional<uint8_t>(), optional<uint8_t>()));
Player playerBlack(Color::Black, PlayerTime(0, 5, 0, optional<uint8_t>(), optional<uint8_t>()));
ChessClock chessClock(playerWhite, playerBlack);



void setup(){
    pinMode (13, OUTPUT);
}

void loop(){
    digitalWrite (LED_PIN, HIGH);
    delay (500);
    digitalWrite (LED_PIN, LOW);
    delay (500);
}