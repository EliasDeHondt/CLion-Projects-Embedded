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

uint16_t seed = 0;
int beschikbaarAantal;
int minAantal = 1;
int maxAantal;
int p_aantal = 1;
int c_aantal;
int berekening = 1;
char speler;

void initializing() { // Default configuration and initialization.
  initUSART();
  initDisplay();
  enablePotentio();
  enableAllButtons();
  printf("Basic initialization completed.\n"); // Serial feedback.
}

void startSpel() { // Deze methode is verantwoordelijk voor de opstart van het spel en de seed.
    printf("Gelieve een waarde te kiezen via de potentiometer.\n");
    while (1) {
        if (buttonPushed(0)) {
        seed = readPotentio(); // 0 ... 1023
        srand(seed);
        beschikbaarAantal = (rand() % 79) + 21; // 21, 22, ..., 99
        // Controleer of maxAantal niet meer is dan een vijfde van beschikbaarAantal
        maxAantal = (rand() % (beschikbaarAantal / 5 - 2)) + 3; // 3, 4, ..., beschikbaarAantal / 5
        writeNumberAndWait(seed, 1000);
        printf("De waarde van (beschikbaarAantal): %d\n", beschikbaarAantal);
        printf("De waarde van (maxAantal): %d\n", maxAantal);
        printf("Potentiometer waarde: %d\n", seed);
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

void verloopSpel() {
    if (speler == 'P') {
        if (buttonPushed(0)) {
            if (p_aantal != minAantal) p_aantal--; // Er wordt 1 bij het p_aantal afgetrokken wanneer het niet kleiner  is dan minAantal aantal.
            _delay_ms(500);
        }
        if (buttonPushed(1)) {
            if (beschikbaarAantal  >= p_aantal) {
                beschikbaarAantal  = beschikbaarAantal  - p_aantal;
                printf("De player heeft het volgende aantal gekozen: %d\n", p_aantal);
                kiesSpeler();
            }
            printf("Het gekozen aantal is te hoog of te laag.\n");
            _delay_ms(500);
        }
        if (buttonPushed(2)) {
            if (p_aantal != maxAantal) p_aantal++; // Er wordt 1 bij het p_aantal geteld wanneer het niet groter is dan maxAantal aantal.
            _delay_ms(500);
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
            kiesSpeler();
            _delay_ms(500);
        }
    }
    LedDisplays();
}

void gewonnen() {
    printf("Gefeliciteerd speler %c heeft gewonnen.", speler);
    // ToDo print geheugen?
    while (1) ledLus();
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