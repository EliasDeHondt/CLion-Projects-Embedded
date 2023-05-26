/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/interrupt.h>  // Provides functions for handling interrupts.
#include <avr/io.h>         // Provides access to the I/O pins of the AVR microcontroller.
#include <util/delay.h>     // Provides delay functions for time-sensitive operations.

void enableTimer2() {
    TCCR2A |= (1 << (WGM21)); // CTC mode. (Clear Timer on Compare) (WGM21 = 1). (WGM20 = 0). (WGM22 = 0). (TCCR2A = 00000010).
    OCR2A = 250; // Compare value. (OCR2A = 250).
    TIMSK2 |= (1 << (OCIE2A)); // Compare interrupt enable. (TIMSK2 = 00000010). (OCIE2A = 1). (OCIE2B = 0).
    sei(); // Enable global interrupts. (SREG = 10000000).
}

void startTimer2() {
    TCCR2B |= (1 << (CS22)) | (1 << (CS21)); // Schalingsfactor = 256. (TCCR2B = 00000110). (CS22 = 1). (CS21 = 1). (CS20 = 0).
    printString("Timer Start\n"); // Serial feedback.
}

void stopTimer2() {
    TCCR2B = (0 << (CS22)) | (0 << (CS21)) | (0 << (CS20)); // Schalingsfactor = 0. (TCCR2B = 00000000). (CS22 = 0). (CS21 = 0). (CS20 = 0).
    printString("Timer Stop\n"); // Serial feedback.
}