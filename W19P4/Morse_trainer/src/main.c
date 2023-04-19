/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define ARRAY_SIZE 3
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <led.h>

/*
We bouwen een eenvoudige morse-trainer die je kan gebruiken om te testen hoe goed je morse-code kent.

Vereisten:
    1. Zodra de applicatie start wordt er een aftelpatroon getoond met de ledjes, zodat de gebruiker zich kan klaarzetten. 
    Het aftelpatroon werkt als volgt: je laat eerst de 4 ledjes branden, dan 3, 2, 1 en 0 en dan start de echte morse-training.

    2. Je herhaalt nu 10 keer volgende stappen:

        2.1. Je toont de morse-code van een willekeurig karakter. 
             Om bijvoorbeeld een A te tonen, laat je alle ledjes kort oplichten en daarna lang oplichten. 
             Voor een Z licht je alle ledjes 2 keer lang op en dan 2 keer kort.

        2.2. Wacht nu even, zodat de gebruiker de tijd krijgt om na te denken en zijn antwoord voor zichzelf te formuleren.

        2.3. Toon nu het correcte antwoord via printf in de seriële monitor.

    3. Na 10 letters eindigt het programma met een frivool led-dansje dat een klein beetje tijd in beslag neemt.

Uitbreiding:
    1. Maak gebruik van C arrays om de morse-code in op te slaan.

    2. Schrijf een functie die een string als parameter krijgt, en vervolgens dat woord in Morse-code toont op de leds...
*/

void streep() {
    lightUpAllLeds(); // Zet al de Lets aan.
    _delay_ms(3000); // Wacht 3 seconden.
    lightDownAllLeds(); // Zet al de Lets uit.
    _delay_ms(1000); // Wacht 1 seconden.
}

void punt() {
    lightUpAllLeds(); // Zet al de Lets aan.
    _delay_ms(1000); // Wacht 1 seconden.
    lightDownAllLeds(); // Zet al de Lets uit.
    _delay_ms(1000); // Wacht 1 seconden.
}

void vertaling(char karakter) {
    switch (karakter) {
        case 'a': {
            punt();
            streep();
            break;
        }
        case 'b': {
            streep();
            punt();
            punt();
            punt();
            break;
        }
        case 'c': {
            streep();
            punt();
            streep();
            punt();
            break;
        }
        case 'd': {
            streep();
            punt();
            punt();
            break;
        }
        case 'e': {
            punt();
            break;
        }
        case 'f': {
            punt();
            punt();
            streep();
            punt();
            break;
        }
        case 'g': {
            streep();
            streep();
            punt();
            break;
        }
        case 'h': {
            punt();
            punt();
            punt();
            punt();
            break;
        }
        case 'i': {
            punt();
            punt();
            break;
        }
        case 'j': {
            punt();
            streep();
            streep();
            streep();
            break;
        }
        case 'k': {
            streep();
            punt();
            streep();
            break;
        }
        case 'l': {
            punt();
            streep();
            punt();
            punt();
            break;
        }
        case 'm': {
            streep();
            streep();
            break;
        }
        case 'n': {
            streep();
            punt();
            break;
        }
        case 'o': {
            streep();
            streep();
            streep();
            break;
        }
        case 'p': {
            punt();
            streep();
            streep();
            punt();
            break;
        }
        case 'q': {
            streep();
            streep();
            punt();
            streep();
            break;
        }
        case 'r': {
            punt();
            streep();
            punt();
            break;
        }
        case 's': {
            punt();
            punt();
            punt();
            break;
        }
        case 't': {
            streep();
            break;
        }
        case 'u': {
            punt();
            punt();
            streep();
            break;
        }
        case 'v': {
            punt();
            punt();
            punt();
            streep();
            break;
        }
        case 'w': {
            punt();
            streep();
            streep();
            break;
        }
        case 'x': {
            streep();
            punt();
            punt();
            streep();
            break;
        }
        case 'y': {
            streep();
            punt();
            streep();
            streep();
            break;
        }
        case 'z': {
            streep();
            streep();
            punt();
            punt();
            break;
        }
        case '0': {
            streep();
            streep();
            streep();
            streep();
            streep();
            break;
        }
        case '1': {
            punt();
            streep();
            streep();
            streep();
            streep();
            break;
        }
        case '2': {
            punt();
            punt();
            streep();
            streep();
            streep();
            break;
        }
        case '3': {
            punt();
            punt();
            punt();
            streep();
            streep();
            break;
        }
        case '4': {
            punt();
            punt();
            punt();
            punt();
            streep();
            break;
        }
        case '5': {
            punt();
            punt();
            punt();
            punt();
            punt();
            break;
        }
        case '6': {
            streep();
            punt();
            punt();
            punt();
            punt();
            break;
        }
        case '7': {
            streep();
            streep();
            punt();
            punt();
            punt();
            break;
        }
        case '8': {
            streep();
            streep();
            streep();
            punt();
            punt();
            break;
        }
        case '9': {
            streep();
            streep();
            streep();
            streep();
            punt();
            break;
        }
    }
}

// Uitbreiding 2.
void vertalingStr(char str[], int len) {

    for (int i = 0; i <= len; i++) {
        vertaling(str[i]);
    }
    

}

int main() {
    /* Uitbreiding 2. (TEST)
    enableAllLeds(); // Schakelt al de leds in.
    lightUpAllLeds(); // Zet al de Lets aan.
    
    char data[ARRAY_SIZE] = "sos";
    int len = ARRAY_SIZE;

    vertalingStr(data, len);
    */
    

    
    // Vereisten 1.
    enableAllLeds(); // Schakelt al de leds in.
    lightUpAllLeds(); // Zet al de Lets aan.
    srand(0); // Set the seed for the random number generator.
    
    for (int i = 0; i < 4; i++) {
        _delay_ms(1000); // Wacht 1 seconden.
        lightDownLed(i); // Zet led x uit.
    }
    lightDownAllLeds();

    // Uitbreiding 1.
    char karakters[10];

    for (int i = 0; i < 10; i++) { // ASCII tabel enzo :-)
        int random_karakter = rand() % 36; // Er zijn 26 letters in het alfabet en 10 cijfers.
        if (random_karakter < 26) {
            karakters[i] = 'a' + random_karakter; // Voeg een willekeurige letter toe.
        } else {
            karakters[i] = '0' + (random_karakter - 26); // Voeg een willekeurig cijfer toe.
        }
    }

    // Vereisten 2.
    // Vereisten 2.1.
    for (int i = 0; i < 10; i++) {
        int random_getal = rand() % 10; // Random getal van 0 tot 9.

        vertaling(karakters[random_getal]);
        // Vereisten 2.2.
        _delay_ms(5000); // Wacht 5 seconden.
        // Vereisten 2.3.
        printf("Hier is het correcte antwoord %c", karakters[0]);
    }

    // Vereisten 3.
    for (int i = 0; i < 5; i++) {
        for (int y = 0; y < 4; y++) { // Led aan.
            lightUpLed(y);
            _delay_ms(100);
        }
        for (int y = 0; y < 4; y++) { // Led uit.
            lightDownLed(y);
            _delay_ms(100);
        }
    }
    return 0;
}
