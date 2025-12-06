#pragma once

#include "../player/player.h"
#include <stdint.h>

// Serial communication and debugging output
namespace hardware {

void setupSerialMonitor(const uint16_t serialMonitorBaudRate);
void printPlayerTime(const player::PlayerInfo *player);

} // namespace hardware