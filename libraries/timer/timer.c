/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void initTimer0() {
    // STAP 1: kies de WAVE FORM en dus de Mode of Operation
    // Hier kiezen we FAST PWM waardoor de TCNT0 steeds tot 255 telt
    TCCR0A |= (1 << (WGM00)) | (1 << (WGM01)); // WGM00 = 1 en WGM01 = 1 --> Fast PWM Mode

    // STAP 2: stel *altijd* een PRESCALER in, anders telt hij niet.
    // De snelheid van tellen wordt bepaald door de CPU-klok (16Mhz) gedeeld door deze factor.
    TCCR0B |= (1 << (CS02)) | (1 << (CS00)); // CS02 = 1 en CS00 = 1 --> prescalerfactor is nu 1024 (=elke 64µs)

    // STAP 3: enable INTERRUPTs
    // Enable interrupts voor twee gevallen: TCNT0 == TOP en TCNT0 == OCR0A
    TIMSK0 |= (1 << (TOIE0)); // overflow interrupt enablen
    TIMSK0 |= (1 << (OCIE0A)); // OCRA interrupt enablen

    sei(); // interrupts globaal enablen
}