/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <led.h>
#include <avr/interrupt.h>

ISR(USART_RX_vect) {      // De interrupt routine voor het ontvangen van dat
    uint8_t byte = UDR0;  // Seriële data zit in UDR0 register
    flipLed(1);           // Flipled om indicatie te geven dat we iets ontvangen hebben
    printf("%c",byte+1);  // Voor dit demootje sturen we dezelfde byte verhoogt met 1 terug...
}

int main(){
  initUSART();
  enableLed(0);
  enableLed(1);
  UCSR0B |= (1 << RXCIE0); // Dit zorgt ervoor dat er een interrupt afgaat zodra er data over serieel ontvangen wordt.
  sei();
  while (1) {
    flipLed(0);//heartbeat...
    _delay_ms(1000);
  }
  return 0;
}