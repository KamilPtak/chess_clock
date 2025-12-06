#include <HardwareSerial.h>

#include "hardware_setup/serial_setup.h"
#include "player/player.h"

namespace hardware {

void setupSerialMonitor(const uint16_t serialMonitorBaudRate) {
  Serial.begin(serialMonitorBaudRate);
  Serial.println("Chess Clock Started!");
}

void printPlayerTime(const player::PlayerInfo *player) {
  const char *color =
      (player->color == player::Color::White) ? "White" : "Black";

  player::RemainingTime time = player->get_remaining_time();

  Serial.print(color);
  Serial.print(" - ");

  Serial.print(time.hours);
  Serial.print(":");
  if (time.minutes < 10)
    Serial.print("0");

  Serial.print(time.minutes);
  Serial.print(":");
  if (time.seconds < 10)
    Serial.print("0");

  Serial.print(time.seconds);
  Serial.print(".");
  if (time.milliseconds < 100)
    Serial.print("0");
  if (time.milliseconds < 10)
    Serial.print("0");
  Serial.println(time.milliseconds);
}

} // namespace hardware