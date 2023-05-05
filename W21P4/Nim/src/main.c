/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
#include <button.h>
#include <potentio.h>
#include <display.h>

#define DELAY _delay_ms(500);

uint8_t beschikbaarAantal = 21; // The number of available matches.
uint8_t p_aantal = 1; // Number chosen by the player (Default 1).
uint8_t c_aantal; // Number chosen by the computer.
uint8_t berekening = 1; // boolean
uint8_t teller = 0; // Keeps track of which round of the game it is.
char speler; // P of C
char* spelDataSpeler[21];
int* spelDataAantal[21];

void initializing() { // Default configuration and initialization.
  initUSART();
  initDisplay();
  enablePotentio();
  enableAllButtons();
  printf("Basic initialization completed.\n"); // Serial feedback.
}

void writeOnHeab() {
    if (speler == 'C') {
        spelDataSpeler[teller] = malloc(strlen("Computer") + 1);
        strcpy(spelDataSpeler[teller], "Computer");

        spelDataAantal[teller] = malloc(sizeof(uint8_t));
        *(spelDataAantal[teller]) = c_aantal;  // waarde toewijzen aan de uint8_t door middel van dereferencing 
    }
    if (speler == 'P') {
        spelDataSpeler[teller] = malloc(strlen("Player") + 1);
        strcpy(spelDataSpeler[teller], "Player");

        spelDataAantal[teller] = malloc(sizeof(uint8_t));
        *(spelDataAantal[teller]) = p_aantal;  // waarde toewijzen aan de uint8_t door middel van dereferencing
    }
    printString("Game data is transferred to the head.\n");
}

void readTheHeab() {
    for (uint8_t i = 0; i < teller; i++) {
        // %hhu is een formaatspecificatie die gebruikt wordt in C om een unsigned char of uint8_t variabele te formatteren.
        printf("%s took %hhu matches on turn %hhu.\n", spelDataSpeler[i], *spelDataAantal[i], (i+1));
        free(spelDataSpeler[i]);
        free(spelDataAantal[i]);
    }
}

void startSpel() { // Deze methode is verantwoordelijk voor de opstart van het spel en de seed.
    printf("Gelieve een waarde te kiezen via de potentiometer.\n");
    while (1) {
        if (buttonPushed(0)) {
            uint16_t potentioValue = readPotentio(); // 0 ... 1023
            float seed = (float)potentioValue / 1023.0 * 9999.0;
            srand(seed);
            writeNumberAndWait((int)seed, 1000);
            printf("Potentiometer waarde: %d\n", potentioValue);
            printf("Seed waarde: %d\n", (int)seed);
            break; 
        }
    }
}

void kiesSpeler() { // Deze methode bepaalt wie er aan de beurt is.
    if (speler != 'P' && speler != 'C') {
        int random = rand() % 2; // 0, 1
        if (random == 0) speler = 'P';
        else speler = 'C';
    }
    else if (speler == 'P') speler = 'C';
    else if (speler == 'C') speler = 'P';
    printf("Het is momenteel aan speler: %c\n", speler);
    if (speler == 'C') berekening = 1; // Zodat de computer logica maar eenmalig wordt uitgevoerd.
}

void LedDisplays() {
    if (speler == 'P') writeNumberToSegment(0, p_aantal); // Gaat alleen maar aan wanneer het aan de player is.
    if (speler == 'C') writeNumberToSegment(0, c_aantal); // Gaat alleen maar aan wanneer het aan de computer is.
    writeCharToSegment(1, speler); // Flikkeren van P of C
    writeNumberToSegment(2, (beschikbaarAantal  / 10) % 10);
    writeNumberToSegment(3, beschikbaarAantal  % 10);
}

void gewonnen() {
    printf("Gefeliciteerd speler %c heeft gewonnen.\n", speler);
    readTheHeab();
    while (1) ledLus();
}

void verloopSpel() {
    uint8_t minAantal = 1; // The minimum number of matches you can grab.
    uint8_t maxAantal = 3; // The maximum number of matches you can grab.
    if (speler == 'P') {
        if (buttonPushed(0)) {
            if (p_aantal != minAantal) p_aantal--; // Er wordt 1 bij het p_aantal afgetrokken wanneer het niet kleiner  is dan minAantal aantal.
            DELAY;
        }
        if (buttonPushed(1)) {
            if (beschikbaarAantal  >= p_aantal) {
                beschikbaarAantal  = beschikbaarAantal  - p_aantal;
                printf("De player heeft het volgende aantal gekozen: %d\n", p_aantal);
                writeOnHeab();
                teller++;
                kiesSpeler();
                DELAY;
            }
            else {
                printf("Het gekozen aantal is te hoog of te laag.\n");
                DELAY;
            }
        }
        if (buttonPushed(2)) {
            if (p_aantal != maxAantal) p_aantal++; // Er wordt 1 bij het p_aantal geteld wanneer het niet groter is dan maxAantal aantal.
            DELAY;
        }
    }
    if (speler == 'C') {
        if (berekening == 1) {  // Zodat de computer logica maar eenmalig wordt uitgevoerd.
            int Clogica = ((beschikbaarAantal - 1) % (maxAantal + 1));
            if (Clogica == 0) c_aantal = (rand() % maxAantal) + 1; // 1, 2, .., maxAantal
            else c_aantal = Clogica;
            berekening = !berekening;  // Zodat de computer logica maar eenmalig wordt uitgevoerd.
        }
        if (buttonPushed(1)) {
            beschikbaarAantal = beschikbaarAantal - c_aantal;
            printf("De computer heeft het volgende aantal gekozen: %d\n", c_aantal);
            writeOnHeab();
            teller++;
            kiesSpeler();
            DELAY;
        }
    }
    LedDisplays();
}

int main()  {
    initializing();
    startSpel();
    kiesSpeler();
    while (1) {
        verloopSpel();
        if (beschikbaarAantal == 0) gewonnen();
    }
    return 0;
}