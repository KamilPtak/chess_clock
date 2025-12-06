#include <Arduino.h>

#include "clock.h"
#include "hardware_setup/hardware_setup.h"
#include "hardware_setup/pin_defines.h"
#include "hardware_setup/serial_setup.h"
#include "player/player.h"

static constexpr uint16_t SERIAL_BAUD_RATE = 9600;
static constexpr uint16_t TIMER_INTERVAL_MS = 1500;

static player::PlayerInfo *playerWhite;
static player::PlayerInfo *playerBlack;

void setup() {
  hardware::setupHardware(SERIAL_BAUD_RATE, TIMER_INTERVAL_MS);

  Serial.print("Timer Interval: ");
  Serial.print(TIMER_INTERVAL_MS);
  Serial.println(" ms");

  playerWhite = new player::PlayerInfo(
      player::Color::White,
      player::PlayerTime(0, 0, 10, optional<uint8_t>(), optional<uint8_t>()));
  playerBlack = new player::PlayerInfo(
      player::Color::Black,
      player::PlayerTime(0, 5, 0, optional<uint8_t>(), optional<uint8_t>()));

  chess_clock::Clock::instance =
      new chess_clock::Clock(*playerWhite, *playerBlack, TIMER_INTERVAL_MS);

  chess_clock::Clock::instance->start();

  Serial.println("Chess Clock initialized!");
}

void loop() {
  if (chess_clock::Clock::instance and
      chess_clock::Clock::instance->consumeSecondFlag() and
      chess_clock::Clock::instance->isRunning() and playerWhite and
      playerBlack) {

    chess_clock::Clock::instance->tick();

    digitalWrite(hardware::LED_PIN, !digitalRead(hardware::LED_PIN));

    Serial.println("\n--- Time Updated ---");
    hardware::printPlayerTime(playerWhite);
    hardware::printPlayerTime(playerBlack);
  }
}