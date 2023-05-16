/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "usart.h"

#define VCC 5 // VCC is 5V = bronspanning

#define A 0.001129148
#define B 0.000234125
#define C 0.0000000876741

#define sbi(register, bit) (register |= _BV(bit)) // _BV(bit) = (1 << bit)
#define cbi(register, bit) (register &= ~_BV(bit))
#define write_mask(register, mask) (register = mask)

void initADC() {
 sbi(ADMUX, REFS0); // kies interne 5V (VCC) als referentiespanning
 write_mask(ADCSRA, _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2)); // stel prescaling factor in op 16 Mhz / 128 = 125 Khz
 sbi(ADCSRA, ADEN); // enable AD conversie

}

uint16_t readADC(uint8_t channel) {
 ADMUX = (ADMUX & 0xf0) | channel; // plaats het gewenste channel in de laagste 4 bits van ADMUX-register
 sbi(ADCSRA, ADSC); // trigger conversie
 loop_until_bit_is_clear(ADCSRA, ADSC); // wacht tot ADSC nul (cleared) is, dan is conversie gedaan
 return ADC;
}

double to_voltage(int rawADC) {
  return rawADC / 1023.0 * VCC; // 0 = 0V en 1023 = 5V
}

double ntcResistance(int rawADC) {
  float R1 = 5000;
  // return R1 * (1023.0 / rawADC - 1.0); // pull-down resistor (veel tutorials op het net)
  return R1 / (1023.0 / rawADC - 1.0); // pull-up resistor (ons geval)
}

double thermister(int rawADC) {
  double Rntc = ntcResistance(rawADC);
  double lnRntc = log(Rntc); // log = ln
  double T = 1 / (A + B * lnRntc + C * pow(lnRntc, 3));
  return T - 273.15;
}

int main() {
  initUSART();
  initADC();

  while (1) {

     uint16_t rawADC = readADC(PC5); // lees ADC waarde op A5 (PC5). Testen kan ook op PC0
     double voltage = to_voltage(rawADC); // zet ADC om naar spanning ter controle

     double resistance = ntcResistance(rawADC); // zet ADC om naar weerstand van warmteweerstand (NTC)
     double temp = thermister(rawADC); // zet ADC om naar temperatuur

     char outstr[8];

     printf("ADC %d", rawADC);
     printf(", de spanning is %s V", dtostrf(voltage, 4, 2, outstr)); // ".2f werkt niet daarom dtostrf gebruiken uit stdlib.h"
     printf(", de weerstand is %s Ohm,", dtostrf(resistance, 4, 2, outstr)); // ".2f werkt niet daarom dtostrf gebruiken uit stdlib.h"
     printf(", de temperatuur is %s °C\n", dtostrf(temp, 4, 2, outstr)); // ".2f werkt niet daarom dtostrf gebruiken uit stdlib.h"

    _delay_ms(500);
  }

 return 0;

}