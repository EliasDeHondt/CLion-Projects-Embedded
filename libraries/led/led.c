#define __DELAY_BACKWARD_COMPATIBLE__
#define NUMBER_OF_LEDS 4 
#include <util/delay.h>
#include <avr/io.h>

void enableLed(int lednumber) {
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return;
  DDRB |= (1 << (PB2 + lednumber)); // 1 op juiste pin want output
}
 
void enableLeds(uint8_t leds) {
  leds &= 0b00001111; // Eerste 4 bits staan nu op 0
  DDRB |= (leds << PB2); // Shiften en juiste pins op 1 zetten
}
 
void enableAllLeds() { 
    enableLeds(0b00001111); 
}
 
void lightUpLed(int lednumber) {
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return;
  PORTB &= ~(1 << (PB2 + lednumber)); // Juiste pin op 0 zetten 
}
 
void lightUpLeds(uint8_t leds) {
  leds &= 0b00001111;
  PORTB &= ~(leds << PB2);
}
 
void lightUpAllLeds() { 
    lightUpLeds(0b00001111); 
}
 
void lightDownLed(int lednumber) {  // Juiste pin 0 (AAN)
  if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return;
  PORTB |= (1 << (PB2 + lednumber)); // Juiste pin op 1 zetten
}
 
void lightDownLeds(uint8_t leds) {
  leds &= 0b00001111;  
  PORTB |= (leds << PB2);
}
 
void lightDownAllLeds() { 
    lightDownLeds(0b00001111); 
}

void dimLed(int lednumber, int percentage, int duration) {
    for (int i = duration; i > 0; i -= 10) { // Is de opgegeven tijdsperiode. (Stap waarde 10)
        lightDownLed(lednumber); // Led x uitzetten.
        _delay_ms(percentage/10); // De tijd dat de Led uit moet staan. (Stap waarde 10)
        lightUpLed(lednumber); // Led x aanzetten.
        _delay_ms((100-percentage)/10); // De tijd dat de Led aan moet staan. (Stap waarde 10)
    }
}

void fadeInLed(int lednumber, int duration) {
    for (int percentage = 1; percentage <= 100; percentage++) { // Door alle mogelijke percentages gaan. (1% tot 100%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightUpLed(lednumber); // Eindpositie van Led.
}

void fadeOutLed(int lednumber, int duration) {
    for (int percentage = 100; percentage > 1; percentage--) { // Door alle mogelijke percentages gaan. (100% tot 1%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightDownLed(lednumber); // Eindpositie van Led.
}

void flipLed(int lednumber) {
    if (lednumber < 0 || lednumber >= NUMBER_OF_LEDS) return;

  // Huidige status van de LED lezen
  int pin_mask = (1 << (PB2 + lednumber));
  int current_state = (PINB & pin_mask) ? 1 : 0;

  // Status van de LED omdraaien
  if (current_state) {
    lightDownLed(lednumber); // Als LED aanstaat, uitzetten
  } else {
    lightUpLed(lednumber); // Als LED uitstaat, aanzetten
  }
}