/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>

#define NUMBER_OF_LEDS 4 

/*
In de demo "Flashing Leds" schreven we een aantal functies om handig met de leds te kunnen werken. In deze oefeningen werken we verder van die code.

Zorg er voor dat je deze functies in een aparte library plaats zodat deze library makkelijk kan hergebruikt worden (zie 3.5 - Een eigen library gebruiken in VS Code ).
Voeg een functie void enableLeds(uint8_t leds) toe die in één keer eender welke combinatie van de 4 leds kan enabelen. De parameter die deze functie meekrijgt is een 8-bit 
waarde, een byte dus. Geef ik bijvoorbeeld 0b00001101 mee, dan worden de 0-de, de 2e en de 3e led ge-enabled voor schrijven. 
Geef ik 0b00000110 mee, dan worden de 1e en de 2e led ge-enabled Voorzie best al deze functies:

void enableLed(int);
void enableLeds(uint8_t);
void enableAllLeds ();
void lightUpLed(int);
void lightUpLeds (uint8_t);
void lightUpAllLeds ();
void lightDownLed(int);
void lightDownLeds (uint8_t);
void lightDownAllLeds ();
Test in een eenvoudig programmaatje... 
*/

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