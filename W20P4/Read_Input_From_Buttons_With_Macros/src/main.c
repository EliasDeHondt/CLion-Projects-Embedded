/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

//in deze code gebruiken we een aantal voorgedefinieerde macro's, zoals _BV en bit_is_clear
//Deze macro's maken de code leesbaarder.
//Ze zijn gedefinieerd in avr/sfr_defs.h en worden ge-include in avr/io.h

int main() {
  initUSART();
  DDRC &= ~_BV(PC1); //DDR instellen, ipv (1<<PC1) gebruiken we de macro _BV(bit) (BV staat voor "Bit Value") 
  printf("DDRC: ");
  printBinaryByte(DDRC);
  PORTC |= _BV(PC1); //Pull up aanzetten van C1, ipv (1<<PC1) gebruiken we de macro _BV(bit)
  printf("\nPORTC: ");
  printBinaryByte(PORTC);
  while (1) {
    printf("\nPINC: ");
    printBinaryByte(PINC);
    if (bit_is_clear(PINC, PC1)) {//ipv (!(PINC & (1 << PC1))) gebruiken we de macro bit_is_clear
      printf(" - Button 1 pushed!\n");
    }
    else {
      printf(" - Button 1 NOT pushed!!\n");
    } 
    _delay_ms(1000);
  }
  return 0;
}