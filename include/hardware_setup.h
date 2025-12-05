#pragma once

#include <Arduino.h>

#include "hardware_timer.h"
#include "pin_defines.h"


// Button flags are defined in a single source file (`hardware_setup.cpp`).
extern volatile bool whitePressed;
extern volatile bool blackPressed;

// ISR handlers for the two buttons
void onWhitePressed();
void onBlackPressed();

// Initialize pins, interrupts and timers
void setupHardware();