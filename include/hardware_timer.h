#pragma once

#include <stdint.h>

// Configure Timer1 to generate compare-match interrupts every `milliseconds`.
void setupTccimer1(uint16_t milliseconds);