/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void enableTimer2() { // 
    TCCR2A |= (1 << (WGM21)); // Clear Timer on Compare Mode.
    OCR2A = 250; // Zet de compare match waarde op 250 (OCR2A = 250).
    TIMSK2 |= (1 << (OCIE2A)); // OCRA interrupt enablen.
    sei(); // Interrupts globaal enablen.
}

void startTimer2() {
    TCCR2B |= (1 << (CS22)) | (1 << (CS21)); // Schalingsfactor = 256. (startTimer)
    printString("Timer Start\n");
}

void stopTimer2() {
    TCCR2B = (0 << (CS22)) | (0 << (CS21)) | (0 << (CS20)); // Schalingsfactor = 0.
    printString("Timer Stop\n");
}