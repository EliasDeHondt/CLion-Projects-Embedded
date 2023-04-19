/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Gebruik onderstaande oefeningen om de syntax van C in de vingers te krijgen. Probeer verzorgde code te schrijven en maak gebruik van functies!

1. Schrijf een programma om de 4 leds van het shield om te beurt te laten oplichten.

2. Schrijf een programma dat één van de leds exact 10 keer laat oplichten.

3. Maak van oefening 2 een functie, waarbij je lednummer en aantal keer oplichten als parameter meegeeft.

4. Schrijf een programma dat een led telkens langer en langer laat branden (begin van 10 ms en loopt tot 1000ms, telkens verhogend met 50ms.

5. Schrijf een programma dat gebruik maakt van een array met daarin 10 cijfers tussen 0 en 4. Je loopt door de array en licht het overeenkomstige led op.

6. Schrijf een programma dat eerst een lege array aanmaakt en deze vervolgens opvult met de getallen van 10 tot 1000 met een stepwaarde van 50ms. 
Gebruik nu deze array om een led te laten oplichten, net zoals in oefening 4.

7. Schrijf een programma dat uitgaande van een string de ledjes laat oplichten. 
De string bevat een opeenvolging van de letters a, b, c en d. Een ‘a’ licht het 1e ledje op, b het 2e enzovoort.

8. Schrijf een programma dat uitgaande van een string de ledjes laat oplichten, deze keer is het een willekeurige reeks letters. 
Bij een a lichtje alle 4 de ledjes 1 keer op, bij een b licht je ze 2 keer op, enzovoort

(Zonder #include <led.h>)
*/

// Vraag 3
void oplichten(int lednumber, int aantal) {
    DDRB |= (1 << (PB2 + lednumber)); // Enable led x
    PORTB = 0b00111100;// Alles UIT

    while (aantal > 0) {
        PORTB &= ~(1 << (PB2 + lednumber)); // AAN
        _delay_ms(1000);
        PORTB |= (1 << (PB2 + lednumber)); // UIT
        _delay_ms(1000);
        aantal--;
    }
}

int main() {
    
    // Vraag 1
    DDRB = 0b00111100; // Enable leds
    PORTB = 0b00111100;// Alles UIT
    for (int i = 0; i < 4; i++) {
        PORTB &= ~(1 << (PB2 + i)); // AAN
        _delay_ms(3000);
        PORTB |= (1 << (PB2 + i)); // UIT
    }

    // Vraag 2
    DDRB = 0b00000100; // Enable led 1
    PORTB = 0b00111100;// Alles UIT

    for (int i = 0; i <= 10; i++) {
        PORTB &= ~(1 << (PB2 + 0)); // AAN
        _delay_ms(1000);
        PORTB |= (1 << (PB2 + 0)); // UIT
        _delay_ms(1000);
    }

    // Vraag 3
    oplichten(1,5);

    // Vraag 4
    DDRB = 0b00000100; // Enable led 1
    PORTB = 0b00111100;// Alles UIT

    for (int i = 10; i <= 1000; i += 50) {
        PORTB &= ~(1 << (PB2 + 0)); // AAN
        _delay_ms(i);
        PORTB |= (1 << (PB2 + 0)); // UIT
        _delay_ms(i);
    }

    // Vraag 5
    DDRB = 0b00111100; // Enable led 1
    PORTB = 0b00111100;// Alles UIT

    int getallenArray1[10] = {0, 1, 2, 3, 2, 1, 0, 3, 0, 3};

    for (int i = 0; i < 10; i++) {
        PORTB &= ~(1 << (PB2 + getallenArray1[i])); // AAN
        _delay_ms(1000);
        PORTB |= (1 << (PB2 + getallenArray1[i])); // UIT
        _delay_ms(1000);
    }

    // Vraag 6
    DDRB = 0b00000100; // Enable led 1
    PORTB = 0b00111100;// Alles UIT
    int getallenArray2[20]; // Lege array
    int teller = 0;

    for (int i = 10; i <= 1000; i += 50) {

        getallenArray2[teller] = i;
        teller++;
    }

    for (int i = 0; i < 20; i++) {
        PORTB &= ~(1 << (PB2 + 0)); // AAN
        _delay_ms(getallenArray2[i]);
        PORTB |= (1 << (PB2 + 0)); // UIT
        _delay_ms(getallenArray2[i]);
    }

    // Vraag 7
    DDRB = 0b00111100; // Enable led alles
    PORTB = 0b00111100;// Alles UIT
    char strABCD1[] = "abcd";


    for (int i = 0; i < 4; i++) {
        if (strABCD1[i] == 'a') PORTB &= ~(1 << (PB2 + 0)); // Led 1 AAN
        if (strABCD1[i] == 'b') PORTB &= ~(1 << (PB2 + 1)); // Led 2 AAN
        if (strABCD1[i] == 'c') PORTB &= ~(1 << (PB2 + 2)); // Led 3 AAN
        if (strABCD1[i] == 'd') PORTB &= ~(1 << (PB2 + 3)); // Led 4 AAN
        _delay_ms(1000);
        if (strABCD1[i] == 'a') PORTB |= (1 << (PB2 + 0)); // Led 1 UIT
        if (strABCD1[i] == 'b') PORTB |= (1 << (PB2 + 1)); // Led 2 UIT
        if (strABCD1[i] == 'c') PORTB |= (1 << (PB2 + 2)); // Led 3 UIT
        if (strABCD1[i] == 'd') PORTB |= (1 << (PB2 + 3)); // Led 4 UIT
        _delay_ms(1000);
    }
    

    // Vraag 8
    DDRB = 0b00111100; // Enable led alles
    PORTB = 0b00111100;// Alles UIT
    char strABCD2[] = "abcd";

    for (int i = 0; i < 4; i++) {

        if (strABCD2[i] == 'a') {
            PORTB = 0b00000000; // AAN
            _delay_ms(1000);
            PORTB = 0b00111100; // UIT
            _delay_ms(1000);
        }
        else if (strABCD2[i] == 'b') {
            for (int y = 0; y < 2; y++) {
                PORTB = 0b00000000; // AAN
                _delay_ms(1000);
                PORTB = 0b00111100; // UIT
                _delay_ms(1000);
            }
        }
        else if (strABCD2[i] == 'c') {
            for (int y = 0; y < 3; y++) {
                PORTB = 0b00000000; // AAN
                _delay_ms(1000);
                PORTB = 0b00111100; // UIT
                _delay_ms(1000);
            }
        }
        else if (strABCD2[i] == 'd') {
            for (int y = 0; y < 4; y++) {
                PORTB = 0b00000000; // AAN
                _delay_ms(1000);
                PORTB = 0b00111100; // UIT
                _delay_ms(1000);
            }
        }
    }

    return 0;
}
