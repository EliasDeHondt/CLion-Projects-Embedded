/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/interrupt.h>  // Provides functions for handling interrupts.
#include <avr/io.h>         // Provides access to the I/O pins of the AVR microcontroller.
#include <util/delay.h>     // Provides delay functions for time-sensitive operations.
#include <usart.h>          // Provides functions for communicating over a USART serial port.

// TCCRxB is voor de schalingsfactor.
// OCRxA is voor de compare value. Dus de waarde waarmee TCNTx vergeleken wordt.
// TIMSKx is voor de compare interrupt enable.

// Timer 1
void enableTimer1() {
    TCCR1B |= (1 << (WGM12)); // CTC mode. (Clear Timer on Compare) (WGM12 = 1). (WGM11 = 0). (WGM10 = 0). (TCCR1B = 00001000).
    OCR1A = 250; // Compare value. (OCR1A = 250).
    TIMSK1 |= (1 << (OCIE1A)); // Compare interrupt enable. (TIMSK1 = 00000010). (OCIE1A = 1). (OCIE1B = 0).
    sei(); // Enable global interrupts. (SREG = 10000000).
}

void startTimer1() {
    TCCR1B |= (1 << (CS12)) | (1 << (CS10)); // Schalingsfactor = 1024. (TCCR1B = 00000101). (CS12 = 1). (CS11 = 0). (CS10 = 1).
    printString("Timer 1 Start\n"); // Serial feedback.
}

void stopTimer1() {
    TCCR1B = (0 << (CS12)) | (0 << (CS11)) | (0 << (CS10)); // Schalingsfactor = 0. (TCCR1B = 00000000). (CS12 = 0). (CS11 = 0). (CS10 = 0).
    printString("Timer 1 Stop\n"); // Serial feedback.
}

void resetTimer1() {
    TCNT1 = 0; // Reset timer. (TCNT1 = 0).
    printString("Timer 1 Reset\n"); // Serial feedback.
}

// Timer 2
void enableTimer2() {
    TCCR2A |= (1 << (WGM21)); // CTC mode. (Clear Timer on Compare) (WGM21 = 1). (WGM20 = 0). (WGM22 = 0). (TCCR2A = 00000010).
    OCR2A = 250; // Compare value. (OCR2A = 250).
    TIMSK2 |= (1 << (OCIE2A)); // Compare interrupt enable. (TIMSK2 = 00000010). (OCIE2A = 1). (OCIE2B = 0).
    sei(); // Enable global interrupts. (SREG = 10000000).
}

void startTimer2() {
    TCCR2B |= (1 << (CS22)) | (1 << (CS21)); // Schalingsfactor = 256. (TCCR2B = 00000110). (CS22 = 1). (CS21 = 1). (CS20 = 0).
    printString("Timer 2 Start\n"); // Serial feedback.
}

void stopTimer2() {
    TCCR2B = (0 << (CS22)) | (0 << (CS21)) | (0 << (CS20)); // Schalingsfactor = 0. (TCCR2B = 00000000). (CS22 = 0). (CS21 = 0). (CS20 = 0).
    printString("Timer 2 Stop\n"); // Serial feedback.
}

void resetTimer2() {
    TCNT2 = 0; // Reset timer. (TCNT2 = 0).
    printString("Timer2 Reset\n"); // Serial feedback.
}