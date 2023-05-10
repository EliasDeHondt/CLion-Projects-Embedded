/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <display.h>
#include <usart.h>
#include <button.h>

#define VEELVOUD 250

// Globale variabelen.
int counter = 0;
int seconden = 0;
int minuten = 0;

void initTimer() {
    TCCR2A |= (1 << (WGM21)); // Clear Timer on Compare Mode.
    OCR2A = 250; // Zet de compare match waarde op 250 (OCR2A = 250).
    TIMSK2 |= (1 << (OCIE2A)); // OCRA interrupt enablen.
    sei(); // Interrupts globaal enablen.
}

void startTimer() {
    TCCR2B |= (1 << (CS22)) | (1 << (CS21)); // Schalingsfactor = 256. (startTimer)
    printString("Timer Start\n");
}

void stopTimer() {
    TCCR2B = (0 << (CS22)) | (0 << (CS21)) | (0 << (CS20)); // Schalingsfactor = 0.
    printString("Timer Stop\n");
}

void writeTimeAndWait(uint8_t minuten, uint8_t seconden, int delay) {
    for (int i = 0; i < delay / 20; i++) {
        writeNumberToSegment(0, (minuten / 10) % 10);
        _delay_ms(5);
        writeNumberToSegment(1, minuten % 10);
        _delay_ms(5);
        writeNumberToSegment(2, (seconden / 10) % 10);
        _delay_ms(5);
        writeNumberToSegment(3, seconden % 10);
        _delay_ms(5);
    }
}

// Deze functie moet elke seconde opgeroepen worden.
void tick(){
   // Bereken seconden en minuten en stockeer ze in globale variabele seconden en minuten.
   seconden++;
    if (seconden >= 60) {
        seconden = 0;
        minuten++;
    }
    printf("Seconden: %d Minuten: %d\n", seconden, minuten);
}

// Deze ISR loopt elke 4ms.
ISR(TIMER2_COMPA_vect) {
    // Verhoog counter met 1.
    counter++;
    // Als counter + 1 deelbaar is door VEELVOUD tel één seconde.
    if (counter % VEELVOUD == 0) tick();
    counter = 0;
}

int main() {
    initUSART();
    initDisplay();
    initTimer();
    printf("Start de stopwatch met S1, stop met S2, en reset met S3\n");
    while (1) {
        if (buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) {
            _delay_ms(100);
            if (buttonPushed(0)) startTimer();
            if (buttonPushed(1)) stopTimer();
            if (buttonPushed(2)) {
                seconden = 0;
                minuten = 0;
            }
        }
        writeTimeAndWait(seconden, minuten, 20);
    }
    return 0;
}