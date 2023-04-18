#include <util/delay.h>
#include <avr/io.h>
 
int main() {
    // DDRB = 0b00100000; // We schrijven een binair getal naar Data Direction Register B. Hierdoor wordt schrijven ge-activeerd op pin 5 van port B.
    DDRB |= 0b00100000; // Beter doen we een bitwise OR, zodat we eventuele 1-tjes die op andere posities van DDRB stonden niet wissen!
    // DDRB |= (1 << 5); // Door gebruik te maken van de << bitshift operator kunnen we het binair getal eenvoudiger aanmaken
    // DDRB |= (1 << (PB2 + 3)); // We gebruiken de poortbenamingen uit io.h om onze code leesbaarder te maken

    while (1) {
        PORTB = (0 << (PB2 + 3)); // We schrijven een 0 naar PB2+3 om het LEDje dat daarop geconnecteerd is aan te zetten
        _delay_ms(1000); // We gebruiken de _delay_ms(..) functie uit delay.h om de uitvoering 1000 milliseconden te pauzeren
        PORTB = (1 << (PB2 + 3)); // We schrijven een 1 naar PB2+3 om het LEDje dat daarop geconnecteerd is uit te zetten
        _delay_ms(1000);
    }
    return 0;
}