
#include "hardware_setup.h"

// Single definition of flags used by ISRs and other modules
volatile bool whitePressed = false;
volatile bool blackPressed = false;

void onWhitePressed() {
    whitePressed = true;
}

void onBlackPressed() {
    blackPressed = true;
}

void setupHardware() {
    pinMode(BUTTON_PIN_WHITE, INPUT_PULLUP);
    pinMode(BUTTON_PIN_BLACK, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_WHITE), onWhitePressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_BLACK), onBlackPressed, FALLING);

    // Configure Timer1 to produce a 1-second tick
    setupTccimer1(1000);
}
