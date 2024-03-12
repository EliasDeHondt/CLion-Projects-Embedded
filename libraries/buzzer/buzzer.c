/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include "buzzer.h"

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C5 523.25
#define D5 587.33
#define E5 659.25
#define F5 698.46
#define G5 783.99
#define A5 880.00
#define B5 987.77

// UIT
void buzzerOff() {
    PORTD |= (1 << PD3); // Afzetten van de buzzer
}

// IN
void buzzerOn() {
    PORTD &= ~(1 << PD3); // Aanzetten van de buzzer
}

// Enable
void enableBuzzer() {
    DDRD |= (1 << PD3); // Buzzer hangt op PD3
    buzzerOff();
}

void playTone(float frequency, uint32_t duration) {
  uint32_t periodInMicro = (uint32_t)(1000000 / frequency); // We berekenen de periode in microseconden uit de frequency
  uint32_t durationInMicro = duration * 1000; // We willen duration in microseconden

  for (uint32_t time = 0; time < durationInMicro; time += periodInMicro) { // Zie tutorial over muziek voor meer uitleg!
    buzzerOn();
    _delay_us(periodInMicro / 2); // Helft van de periode wachten
    buzzerOff();
    _delay_us(periodInMicro / 2); // Weer helft van de periode wachten
  }
}

void positiveTone() {
  playTone(G5, 100);  // speel G5 voor 100 milliseconden
  playTone(A5, 100);  // speel A5 voor 100 milliseconden
  playTone(B5, 100);  // speel B5 voor 100 milliseconden
  playTone(C6, 200);  // speel C6 voor 200 milliseconden
}

void negativeTone() {
  playTone(G5, 100);  // speel G5 voor 100 milliseconden
  playTone(D5, 200);  // speel D5 voor 200 milliseconden
}

void startTone() {
  playTone(C5, 200);  // speel C5 voor 200 milliseconden
  playTone(E5, 200);  // speel E5 voor 200 milliseconden
  playTone(G5, 400);  // speel G5 voor 400 milliseconden
}

void Elise() { // Für Elise
  //intro
  playTone(E5, 250);
  playTone(D5, 250);
  playTone(E5, 250);
  playTone(D5, 250);
  playTone(E5, 250);
  playTone(B4, 250);
  playTone(D5, 250);
  playTone(C5, 250);
  playTone(A4, 250);
  //deel 1
  playTone(E4, 250);
  playTone(A4, 250);
  playTone(E5, 250);
  playTone(D5, 250);
  playTone(C5, 250);
  playTone(E4, 250);
  playTone(A4, 250);
  playTone(E5, 250);
  playTone(D5, 250);
  playTone(C5, 250);
  playTone(B4, 250);
  playTone(E4, 250);
  playTone(G4, 250);
  playTone(B4, 250);
  playTone(C5, 250);
  //deel 2
  playTone(E4, 250);
  playTone(E5, 250);
  playTone(D5, 250);
  playTone(C5, 250);
  playTone(B4, 250);
  playTone(D4, 250);
  playTone(F4, 250);
  playTone(A4, 250);
  playTone(B4, 250);
  playTone(C5, 250);
  playTone(D5, 250);
  playTone(E5, 250);
  playTone(C5, 250);
  playTone(A4, 250);
  playTone(E4, 250);
  playTone(E5, 250);
  playTone(D5, 250);
  playTone(C5, 250);
  playTone(B4, 250);
  playTone(D4, 250);
  playTone(F4, 250);
  playTone(A4, 250);
  playTone(B4, 250);
  playTone(C5, 250);
  playTone(D5, 250);
  playTone(E5, 250);
  playTone(C5, 250);
  playTone(A4, 250);
  playTone(E4, 250);
  playTone(B4, 250);
  playTone(C5, 250);
  playTone(D5, 250);
  playTone(E5, 250);
  playTone(F5, 250);
  playTone(G5, 250);
  playTone(E5, 250);
}