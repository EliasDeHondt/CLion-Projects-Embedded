#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <led.h>
#include <potentio.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define MIN_TIMER 10
#define MAX_TIMER 240

int counter = 0;
int seconden = 0;
int teller = 5;

int statusB1 = 0;//status van de knoppen is 0 als ze ingedrukt zijn
int statusB2 = 0;//status van de knoppen is 0 als ze ingedrukt zijn
int statusB3 = 0;//status van de knoppen is 0 als ze ingedrukt zijn



ISR(PCINT1_vect) {
statusB1 = 1;//niet ingedrukt
statusB2 = 1;//niet ingedrukt
statusB3 = 1;//niet ingedrukt
  if (buttonPushed(0) && statusB2 == 1&& statusB3 == 1) {
    statusB1 = 0;
  }  
  if (buttonPushed(1)&& statusB1 == 0&& statusB3 == 1) {
    statusB2 = 0;
  }  
  if (buttonPushed(2)&& statusB1 == 0&& statusB2 == 0) {
    statusB3 = 0;
  }

}


void tick() {
  int frequentieArray[6] = {100,500,1000,2000,4000,50};  
  if (teller >=0 && teller <=5)
  {
    teller--;
    playTone(frequentieArray[teller], 50);
  }
}
ISR(TIMER2_COMPA_vect) {
  counter++;
  if (counter == 250) {
    // 250 * 4 = 1000 ms = dus 1 sec voorbij
    tick();
    counter = 0;
  }
}
void startTimer() {
  TCCR2B |= _BV(CS22) | _BV(CS21);
}
void initTimer() {
  TCCR2A |= _BV(WGM21);
  TIMSK2 |= _BV(OCIE2A);  
  OCR2A = 249;
 
}


// fase 1: instellen van de timer
uint16_t instellenAantalSeconden() {
  uint16_t potentio;

  while (!buttonPushed(1)) {
    printf("potentio: %d\n", potentio);
    potentio = readPotentio();

    if (potentio < MIN_TIMER) {
      potentio = MIN_TIMER;
    } else if (potentio > MAX_TIMER) {
      potentio = MAX_TIMER;
    }
  }

  return potentio;
}
// fase 2: displayen van de timer en aftellen met een buzzer
void displayAantalSeconden(uint16_t aantalSeconden) {
  uint16_t teller = 0;

  while (aantalSeconden > 0) {
    uint16_t secondenToShow = aantalSeconden - teller;
    writeNumberAndWait(secondenToShow, 1000);
    teller++;
    printf("teller: %d\n", secondenToShow-1);
    playTone(100, 50);
    if (teller == aantalSeconden) {
      break;
    }
  }
}

void ontploffen(){

}

int main() {
  sei();  // Schakel interrupts in
  initUSART();
  initDisplay();
  initTimer();
  //enableAllButtonToIntterupt();
  enableAllButtonInterrupts(); // Lib van Elias De Hondt = enableAllButtonToIntterupt();
  enablePotentio();
  enableBuzzer();
 
  uint16_t aantalSeconden = instellenAantalSeconden();
  while (statusB3 == 0) {
    for (int i = 0; i < aantalSeconden; i++) {
      displayAantalSeconden(aantalSeconden);
      if (aantalSeconden <= 5 || aantalSeconden >= 1) {
        displayAantalSeconden(aantalSeconden);
        startTimer();
      }
    }
  }

  return 0;
}