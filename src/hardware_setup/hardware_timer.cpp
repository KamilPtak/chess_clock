#include <Arduino.h>
#include <avr/interrupt.h>

#include "clock.h"
#include "hardware_setup/hardware_timer.h"

namespace hardware {

void setupTccimer1(uint16_t milliseconds) {
  cli();

  // cppcheck-suppress cstyleCast
  TCCR1A = 0;
  // cppcheck-suppress cstyleCast
  TCCR1B = 0;

  // CTC mode
  // cppcheck-suppress cstyleCast
  TCCR1B |= (1 << WGM12);
  // prescaler 1024
  // cppcheck-suppress cstyleCast
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Compute OCR1A for requested milliseconds interval
  uint32_t ticks = (static_cast<uint32_t>(F_CPU) / 1024ul / 1000ul) *
                   static_cast<uint32_t>(milliseconds);
  if (ticks == 0)
    ticks = 1;
  if (ticks > 0xFFFF)
    ticks = 0xFFFF;
  // cppcheck-suppress cstyleCast
  OCR1A = static_cast<uint16_t>(ticks - 1);

  // cppcheck-suppress cstyleCast
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

} // namespace hardware

ISR(TIMER1_COMPA_vect) { chess_clock::Clock::notifySecond(); }
