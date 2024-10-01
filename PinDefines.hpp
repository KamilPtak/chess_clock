#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

#include "Arduino.h"
#include <stdint.h>

constexpr uint8_t pin1 = 1;


void configurePins() {
  pinMode(pin1, INPUT);
}

#endif
