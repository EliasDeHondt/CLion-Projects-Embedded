/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <avr/io.h>
#include <button.h>
#include <led.h>
#include <usart.h>
#include <util/delay.h>

/*
Voor deze oefening schrijf je een kleine bibliotheek (button.h/button.c)
die een aantal handige button functies implementeert die je in toekomstige
projecten kan hergebruiken. We verwachten minimaal een implementatie van
volgende functies:

void enableButton(int button);
int buttonPushed(int button);
int buttonReleased(int button);

Hierbij is de parameter telkens de nummer van het knopje op je shield (0=meest
linkse knopje). Werk de library uit en gebruik in een voorbeeldprogrammaatje dat
output naar de seriële monitor stuurt!
*/

/*
void enableButton(int button) {
  if (button < 0 || button > 2) { return; } // 0, 1 of 2 (3 button)

  DDRC &= ~(1 << button);
  PORTC |= (1 << button);
}

void enableAllButtons() {
  for (int i = 0; i < 3; i++) { enableButton(i); }
}

int buttonPushed(int button) {
  if (button < 0 || button > 2) { return -1; } // 0, 1 of 2 (3 button)

  if ((PINC & (1 << (PC1 + button))) == 0) { return 1; } // (knop ingeduwd)
  else { return 0; }
}

int buttonReleased(int button) {
  return !buttonPushed(button); // (knop niet ingeduwd)
}
*/


int main() {
  initUSART();
  enableAllLeds();
  enableAllButtons();
  lightDownAllLeds();

  while (1) {
    for (int i = 0; i < 3; i++) {
      if (buttonPushed(i)) {
        lightDownAllLeds();
        printf("Button pushed: %d\n", i);
        _delay_ms(1000);
        // flashLed(i, 100);
      }
    }
  }
  return 0;
}