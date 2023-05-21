/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 21/05/2023
 */


#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <led.h>
#include <potentio.h>
#include <usart.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>

#define MIN_TIMER 10
#define MAX_TIMER 240

uint16_t instellenAantalSeconden() {
  uint16_t potentio;
  while (!buttonPushed(1) && (printf("potentio: %d\n", potentio), potentio = (readPotentio() < MIN_TIMER) ? MIN_TIMER : (readPotentio() > MAX_TIMER) ? MAX_TIMER : readPotentio(), 1));
  return potentio;
}

void displayAantalSeconden() {
  uint16_t aantalSeconden = instellenAantalSeconden();
  for (int i = 0; i < 1000 / 20; i++) for (int j = 0; j < 4; j++, _delay_ms(5)) writeNumberToSegment(j, (j == 0) ? aantalSeconden / 1000 : ((j == 1) ? (aantalSeconden / 100) % 10 : ((j == 2) ? (aantalSeconden / 10) % 10 : aantalSeconden % 10)));
}

int main() {
  initUSART(), initDisplay(), enablePotentio(), displayAantalSeconden();
  return 0;
}
