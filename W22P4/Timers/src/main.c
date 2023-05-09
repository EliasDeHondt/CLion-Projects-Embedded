/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

uint32_t counter = 0;

void initTimer0() {
    // STAP 1: kies de WAVE FORM en dus de Mode of Operation
    // Hier kiezen we FAST PWM waardoor de TCNT0 steeds tot 255 telt
    TCCR0A |= _BV(WGM00) | _BV(WGM01); // WGM00 = 1 en WGM01 = 1 --> Fast PWM Mode

    // STAP 2: stel *altijd* een PRESCALER in, anders telt hij niet.
    // De snelheid van tellen wordt bepaald door de CPU-klok (16Mhz) gedeeld door deze factor.
    TCCR0B |= _BV(CS02) | _BV(CS00); // CS02 = 1 en CS00 = 1 --> prescalerfactor is nu 1024 (=elke 64µs)

    // STAP 3: enable INTERRUPTs
    // Enable interrupts voor twee gevallen: TCNT0 == TOP en TCNT0 == OCR0A
    TIMSK0 |= _BV(TOIE0); // overflow interrupt enablen
    TIMSK0 |= _BV(OCIE0A); // OCRA interrupt enablen

    sei(); // interrupts globaal enablen
}

// deze ISR runt telkens wanneer TCNT0 gelijk is aan de waarde in het OCRA-register
ISR(TIMER0_COMPA_vect) {
   counter++;
   PORTB &= ~(_BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5));
}

// deze ISR runt telkens wanneer TCNT0 gelijk is aan de waarde TOP-waarde (255)
ISR(TIMER0_OVF_vect) {
   counter++;
   PORTB |= _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5);
}

int main() {

 initUSART(); // initialiseer USART
 initTimer0(); // initialiseer Timer 0

 DDRB |= _BV(PB2) | _BV(PB3) | _BV(PB4) | _BV(PB5);  // LEDs in output zetten

 while (1) {

     printf("************************************************************************************\n");
     printf("***************************** Tik Tak Demo *****************************************\n");
     printf("************************************************************************************\n");

     printf("Timer 0 is ingesteld om elke 64 µs zijn TCNT0-register te verhogen tot maximaal 255.\n");
     printf("Momenteel is de waarde van het TCNT0-register %d\n\n", TCNT0);

     printf("We gaan een OCR0A-waarde instellen waarmee TCNT0 continu vergeleken zal worden.\n");
     printf("Kijk daarna goed naar je LEDs...\n");

     printf("Geef OCR0A-waarde in m.b.v. 3 cijfers (000-255):");

     OCR0A = getNumber(); // OCR0A kan je steeds vrij kiezen tussen 0 en 255

     printf("Timer 0 genereert nu *achter de schermen* continu twee interrupts:\n");
     printf("\t*) wanneer jouw ORC0A (%d) bereikt wordt.\n", OCR0A);
     printf("\t*) wanneer zijn TOP (%d) bereikt wordt.\n\n", 255);

     printf("Ondertussen zitten we in totaal al aan %d interrupts.\n\n", counter);
  }

  return 0;

}