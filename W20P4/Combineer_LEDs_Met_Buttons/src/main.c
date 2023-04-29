/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <button.h>
#include <led.h>

/*
Voor deze oefening werk je verplicht met interrupts, dus zorg dat je de tutorials doorgenomen hebt!

Je schrijft een programmaatje waarbij de 3 knoppen een ander resultaat op de leds genereren:
  Druk je op knop 0, dan begint led 0 te knipperen, druk je nogmaals dan gaat die uit.
  Druk je op knop 1, dan begint led 1 te knipperen, druk je nogmaals dan gaat die uit.
  Druk je op knop 2, dan begint led 2 te knipperen, druk je nogmaals dan gaat die uit.

Opgelet: druk ik bijvoorbeeld op knop 0 én op knop 1, dan verwacht ik dat zowel led 0 als led 1 knipperen!

Je kan best je library button.h en button.c eerst uitbreiden met 2 functies:
  enableButtonInterrupt(int button);
  enableAllButtonInterrupts();
*/

int button0_pressed = 0;
int button1_pressed = 0;
int button2_pressed = 0;

ISR(PCINT1_vect) {
  if (buttonPushed(0)) button0_pressed = !button0_pressed;
  if (buttonPushed(1)) button1_pressed = !button1_pressed;
  if (buttonPushed(2)) button2_pressed = !button2_pressed;
}

int main() {
  enableAllLeds();
  lightDownAllLeds();
  enableAllButtons();
  enableAllButtonInterrupts();

  while (1) {
      if (button0_pressed) flashLed(0, 500);
      else lightDownLed(0);

      if (button1_pressed) flashLed(1, 500);
      else lightDownLed(1);

      if (button2_pressed) flashLed(2, 500);
      else lightDownLed(2);
    }
    return 0;
}