/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>

void enablePotentio() {
    ADMUX |= (1<<REFS0); // Instellen van de reference voltage. We kiezen op deze manier voor de 5V als reference voltage
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Bepalen van de samplerate door een deelfactor in te stellen. Deelfactor hier: 128
    ADCSRA |= (1<<ADEN); // Enable de ADC

}

uint16_t readPotentio() {
    ADCSRA |= (1<<ADSC); // Start de conversie analoog -> digitaal
    loop_until_bit_is_clear(ADCSRA, ADSC); // Wacht tot conversie gebeurd is
    return ADC; // Lees het resultaat uit
}