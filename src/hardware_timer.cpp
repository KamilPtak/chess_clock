#include <Arduino.h>
#include <avr/interrupt.h>

#include "hardware_timer.h"
#include "clock.h"

void setupTccimer1(uint16_t milliseconds) {
	cli();

	TCCR1A = 0;
	TCCR1B = 0;

	// CTC mode
	TCCR1B |= (1 << WGM12);
	// prescaler 1024
	TCCR1B |= (1 << CS12) | (1 << CS10);

	// Compute OCR1A for requested milliseconds interval
	// OCR1A = F_CPU / (prescaler) * (ms/1000) - 1
	uint32_t ticks = (uint32_t)F_CPU * (uint32_t)milliseconds / 1000ul;
	ticks /= 1024ul;
	if (ticks == 0) ticks = 1;
	if (ticks > 0xFFFF) ticks = 0xFFFF;
	OCR1A = (uint16_t)(ticks - 1);

	TIMSK1 |= (1 << OCIE1A);

	sei();
}

ISR(TIMER1_COMPA_vect) {
	ChessClock::notifySecond();
}
