#pragma once

#include <stdint.h>

// Timer management - hardware timer configuration
namespace hardware {

// Configure Timer1 to generate compare-match interrupts every `milliseconds`.
void setupTccimer1(uint16_t milliseconds);

} // namespace hardware