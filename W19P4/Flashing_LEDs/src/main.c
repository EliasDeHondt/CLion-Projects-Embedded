#include <util/delay.h>
#include <avr/io.h>

#define NUMBER_OF_LEDS 4  // #define is een "preprocessor directive". Het zorgt ervoor dat in onderstaande file elke NUMBER_OF_LEDS vervangen wordt door 4.  

void enableLed(int lednumber) { // C werkt niet met classes: functies staan gewoon rechtstreeks in de .c file.
    if (lednumber < 0 || lednumber > NUMBER_OF_LEDS - 1) return;
    DDRB |= (1 << (PB2 + lednumber)); // Check de tutorial "Schrijven naar een PIN". Uit de documentatie van de Multifunctional Shield weten we dat de leds beginnen op PB2
}

void lightUpLed(int lednumber) { // Opgelet: ge-enabelde leds staan ook ineens aan (want 0 = aan)
    if (lednumber < 0 || lednumber > NUMBER_OF_LEDS - 1) return;
    PORTB &= ~(1 << (PB2 + lednumber)); // Check de tutorial "Bit operaties" om te weten wat hier juist gebeurd.
}

void lightDownLed(int lednumber) {
    if (lednumber < 0 || lednumber > 3) return;
    PORTB |= (1 << (PB2 + lednumber)); // Zorg ook dat je deze code goed begrijpt!
}

int main() {
    for (int i=0; i < 4 ; i++) {
        enableLed(i);
    }
    while (1) {
        for (int i=0; i < 4; i++) {
            lightUpLed(i);
            _delay_ms(100);
        }
        for (int i=0; i < 4; i++) {
            lightDownLed(i);
            _delay_ms(100);
        }
    }
    return 0;
}