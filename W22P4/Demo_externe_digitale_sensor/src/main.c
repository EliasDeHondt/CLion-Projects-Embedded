/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

/*
In dit voorbeeld hangen we een digitale sensor (bijvoorbeeld een lijnherkennings sensor)
aan de vrije digitale pin ~9 (in code gekend als PB1)
We benaderen ze via dataregister DDRB en kunnen de waarde (0 of 1) uitlezen via PINB
Op dezelfde manier kan je ook de vrije pinnen ~5 en ~6 kunnen gebruiken,
die zijn gekend als PD5 en PD6 en kunnen benaderd worden via DDRD
*/

#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <led.h>

void enableSensor() {  
  DDRB &= ~(1 << PB1); //Digital pin 9 op 0 zetten (input)
}

int main() {
  initUSART();
  enableLed(0);
  lightDownLed(0);
  enableSensor();

  while (1) {
    printf("PB1: ");
    printBinaryByte(PB1);
    printf("  PINB: ");
    printBinaryByte(PINB);
    if ((PINB & (1 << PB1)) == 0) {
      printf(" - Sensor HIGH\n");
      lightUpLed(0);
    }
    else {
      printf(" - Sensor LOW\n");
      lightDownLed(0);
    } 
    _delay_ms(500);
  }

 return 0;
}