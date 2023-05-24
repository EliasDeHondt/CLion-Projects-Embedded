/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

/*
We kunnen de Arduino gebruiken om een willekeurige toon te produceren, onze
eigen kleine synthesizer...

Om deze oefening op te lossen moet je een aantal voorgaande technieken
combineren: de led-display gebruiken, interrupts op knoppen opvangen, de
potentiometer uitlezen aan de hand van de ADC. Het gebruik van je libraries is
dus zeer aangewezen. Heb je voor al die functionaliteit nog geen libraries
gemaakt, dan is dit misschien een goed moment om dat ineens te doen! (Maak
bijvoorbeeld de libraries "potentio" en "buzzer")

Je zorgt ervoor dat de gebruiker door aan de potentiometer te draaien een
frequentie kan kiezen. De frequentie wordt getoond op de display. Zodra je op
een knop drukt wordt de toon afgespeeld. Gebruik interrupts en een variabele
playing die je buiten de main declareert (een globale variabele dus) en die
aangeeft of de toon gespeeld moet worden of niet. Het afspelen van de toon
gebeurt in je main loop, speel telkens een stukje van bijvoorbeeld 500
milliseconden af en herhaal dat. Druk je nogmaals op de knop, dan verander je de
waarde van playing en stopt de toon.
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <potentio.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

int playing = 0;

ISR(PCINT1_vect) {
  if (buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) {
    _delay_us(500);
  if (buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) playing = !playing;
  }
}

int main() {
  initUSART();
  initDisplay();
  enablePotentio();
  enableAllButtonInterrupts();
  enableAllButtons();
  enableBuzzer();

  while (1) {
    int frequentie = readPotentio();
    if (playing) playTone(frequentie, 500);
    else {
      writeNumberAndWait(frequentie, 2000);
      printf("Potentiometer waarde: %d\n", frequentie);
    }
  }
  return 0;
}