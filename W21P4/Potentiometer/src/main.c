/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

void initADC(){ 
  ADMUX |= (1<<REFS0); // Instellen van de reference voltage. We kiezen op deze manier voor de 5V als reference voltage
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Bepalen van de samplerate door een deelfactor in te stellen. Deelfactor hier: 128
  ADCSRA |= (1<<ADEN); // Enable de ADC
}

int main(){
  initUSART();
  initADC();
  while (1) {
    ADCSRA |= (1<<ADSC); // Start de conversie analoog -> digitaal
    loop_until_bit_is_clear(ADCSRA,ADSC); // Wacht tot conversie gebeurd is
    uint16_t value = ADC; // Lees het resultaat uit
    printf("Value:%d\n", value);
  }
  return 0;
}