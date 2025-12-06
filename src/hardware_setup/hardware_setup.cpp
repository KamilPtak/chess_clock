
#include "hardware_setup/hardware_setup.h"
#include "hardware_setup/serial_setup.h"

// Single definition of flags used by ISRs and other modules
volatile bool whitePressed = false;
volatile bool blackPressed = false;

namespace hardware {

void onWhitePressed() { whitePressed = true; }

void onBlackPressed() { blackPressed = true; }

void setupHardware(const uint16_t serialMonitorBaudRate,
                   const uint16_t timerIntervalMs) {
  pinMode(BUTTON_PIN_WHITE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_BLACK, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_WHITE), onWhitePressed,
                  FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_BLACK), onBlackPressed,
                  FALLING);

  // Configure Timer1 to produce a 1-second tick
  setupTccimer1(timerIntervalMs);

  setupSerialMonitor(serialMonitorBaudRate);
}

} // namespace hardware
