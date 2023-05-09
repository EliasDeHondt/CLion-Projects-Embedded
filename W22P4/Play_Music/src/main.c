/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>  //voor interrupt van buttons
#include <avr/io.h>
#include <button.h>
#include <led.h>
#include <usart.h>
#include <util/delay.h>
#include <buzzer.h>
 
// DURATION IS IN MILLISECONDEN
#define DURATION 250
 
// FREQUENCIES VAN DE VERSCHILLENDE NOTEN
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.000
#define B5 987.770
#define C6 1046.500
 
int musicOn = 0;  // false
 
ISR(PCINT1_vect) {
  if (buttonPushed(0) == 1) {
    _delay_us(500);  // debounce
    if (buttonPushed(0) == 1) {
      musicOn = !musicOn;
    }
  }
}
 
int main() {
  initUSART();
  enableButton(0);
  enableButtonInterrupt(0);
  uint32_t frequencies[] = {C5, D5, E5, F5, G5, A5, B5, C6};  // do-re-mi...
  enableBuzzer();
  enableLed(0);
  lightDownLed(0);
  enableBuzzer();
  
  while (1) {
    for (int note = 0; note < 8; note++) {
      if (musicOn) {
        playTone(frequencies[note], DURATION);
        printf("Period: %lu\n", frequencies[note]);
        lightUpLed(0);
        _delay_ms(DURATION);
        lightDownLed(0);
      }
    }
  }
  return 0;
}