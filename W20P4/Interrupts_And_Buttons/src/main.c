/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <led.h>
// #include <button.h>
#include <usart.h>

// Check eerst de code in de main functie!
// Deze ISR wordt aangeroepen als Pin Change Interrupt 1 afgaat (PCINT1_vect)
// Dit is de interrupt voor PORTC, die waarop de knopjes hangen...
ISR(PCINT1_vect) {
  if (buttonPushed(0)) {
    // We wachten 1000 microseconden en checken dan nog eens (debounce!)
   _delay_us(1000);
    if (buttonPushed(0)) { //function uit button.h
      printf("FLIP ");
      flipLed(1); //function uit led.h
    }
  }
}

int main() {
  initUSART();
  enableAllLeds();
  enableButton(0);
  lightDownAllLeds();
  PCICR |= (1 << PCIE1);  // in Pin Change Interrupt Control Register: geef aan
                        // welke interrupt(s) je wil activeren (PCIE0: poort B,
                        // PCIE1: poort C, PCIE2: poort D)
  PCMSK1 |= (1 << PC1);  // in overeenkomstig Pin Change Mask Register: geef
                           // aan welke pin(s) van die poort de ISR activeren
  sei();  // Set Enable Interrupts --> globaal interrupt systeem aanzetten
  while (1) {
    printf("Heartbeat...\n");
    flashLed(0, 500); //function uit led.h
  }
  return 0;
}