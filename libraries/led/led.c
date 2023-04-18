#include <util/delay.h>
#include <avr/io.h>

#define NUMBER_OF_LEDS 4 

void enableLed(int lednumber) { // Enable
    if (lednumber < 0 || lednumber > NUMBER_OF_LEDS - 1) return; // If
    DDRB |= (1 << (PB2 + lednumber)); // Else
}

void enableLeds(uint8_t lednumbers) { // Enable
    DDRB |= lednumbers;
}

void enableAllLeds() { // Enable
    DDRB = 0b00111100;
}

void lightUpLed(int lednumber) { // Up
    if (lednumber < 0 || lednumber > NUMBER_OF_LEDS - 1) return; // If
    PORTB &= ~(1 << (PB2 + lednumber)); // Else
}

void lightUpLeds(uint8_t lednumbers) { // Up
    PORTB &= lednumbers;
}

void lightUpAllLeds() { // Up
    PORTB = 0b00000000;
}

void lightDownLed(int lednumber) { // Down
    if (lednumber < 0 || lednumber > 3) return; // If
    PORTB |= (1 << (PB2 + lednumber)); // Else
}

void lightDownLeds(uint8_t lednumbers) { // Down
    PORTB |= lednumbers;
}

void lightDownAllLeds() { // Down
    PORTB = 0b00111100;
}