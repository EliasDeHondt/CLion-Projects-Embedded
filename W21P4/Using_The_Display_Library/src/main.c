/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <display.h>
#include <usart.h>
#include <util/delay.h>

int main(void) {
  initUSART();
  initDisplay();
  while (1) {
    for (int i = 0; i < 4; i++) {
      writeNumberToSegment(i, 8);
      _delay_ms(1000);
    }
    // Wil je een getal van 4 cijfers tonen, dan kan je de writeNumber functie
    // gebruiken
    writeNumber(1974);
    _delay_ms(1000);
    // probleem: doordat deze functie 1 voor 1 de cijfers toont en dan een delay
    // doet, blijft enkel het laatste cijfer langer staan oplossing: om het
    // volledige getal zichtbaar te krijgen moet je het in een lus herhalen
    for (int i = 0; i < 10000; i++) {
      writeNumber(1974);
    }
    // Of je kan deze functie uit de library gebruiken, als je wil kunnen
    // meegeven hoe lang het moet blijven staan
    writeNumberAndWait(1974, 1000);
  }
}