/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#include <util/delay.h> // Provides delay functions for time-sensitive operations.
#include <avr/io.h>     // Provides access to the I/O pins of the AVR microcontroller.

void enablePotentio() {
    ADMUX |= (1 << REFS0); // Interne referentie spanning van 5V gebruiken
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Schalingsfactor van 128 gebruiken (16MHz / 128 = 125kHz)
    ADCSRA |= (1 << ADEN); // Enable de ADC

}

uint16_t readPotentio() {
    ADCSRA |= (1 << ADSC); // Start een conversie met de ADC. ADC is een converteerd een analoog signaal naar een digitaal signaal
    loop_until_bit_is_clear(ADCSRA, ADSC); // Wacht tot de conversie klaar is
    return ADC; // Return de waarde van de ADC wat een getal tussen 0 en 1023 is en digitaal is
}