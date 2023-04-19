/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>

int main() {
  DDRB = 0b00100000;
  while (1) { // LUS
    PORTB = 0b00000000; // AAN
    _delay_ms(1000);
    PORTB = 0b00100000; // UIT
    _delay_ms(1000);
  }
}