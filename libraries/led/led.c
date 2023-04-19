#define __DELAY_BACKWARD_COMPATIBLE__
#define NUMBER_OF_LEDS 4 
#include <util/delay.h>
#include <avr/io.h>

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

void dimLed(int lednumber, int percentage, int duration) {
    for (int i = duration; i > 0; i -= 10) { // Is de opgegeven tijdsperiode. (Stap waarde 10)
        lightDownLed(lednumber); // Led x uitzetten.
        _delay_ms(percentage/10); // De tijd dat de Led uit moet staan. (Stap waarde 10)
        lightUpLed(lednumber); // Led x aanzetten.
        _delay_ms((100-percentage)/10); // De tijd dat de Led aan moet staan. (Stap waarde 10)
    }
}

void fadeInLed(int lednumber, int duration) {
    for (int percentage = 1; percentage <= 100; percentage++) { // Door alle mogelijke percentages gaan. (0% tot 100%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightUpLed(lednumber); // Eindpositie van Led.
}

void fadeOutLed(int lednumber, int duration) {
    for (int percentage = 100; percentage > 1; percentage--) { // Door alle mogelijke percentages gaan. (100% tot 0%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightDownLed(lednumber); // Eindpositie van Led.
}