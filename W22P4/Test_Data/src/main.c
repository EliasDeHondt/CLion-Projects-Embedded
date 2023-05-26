#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <led.h>
#include <potentio.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

#define MIN_TIMER 10
#define MAX_TIMER 240

int totaalTijd;
int counter = 0;

int statusB1 = 1;
int statusB2 = 1;
int statusB3 = 1;

typedef struct {
  int tijdstip;
  uint8_t* buttonsPushed;
} Tijdstip;

Tijdstip* logs;

void tick() {
  int frequentieArray[6] = {50, 4000, 2000, 1000, 500, 100};
  playTone(frequentieArray[totaalTijd], 50);
}

uint8_t* getButtonStatus() {
  uint8_t* buttonStatus = calloc(3, sizeof(uint8_t));
  buttonStatus[0] = statusB1;
  buttonStatus[1] = statusB2;
  buttonStatus[2] = statusB3;
  return buttonStatus;
}
ISR(TIMER2_COMPA_vect) {
  counter++;
  if (counter == 250) {
    // 250 * 4 = 1000 ms = dus 1 sec voorbij
    totaalTijd--;
    printf("\ntotale tijd: %d\n", totaalTijd);
    playTone(100, 50);
    logs[totaalTijd].tijdstip = totaalTijd;
    logs[totaalTijd].buttonsPushed = getButtonStatus();
    if (totaalTijd <= 5) {
      if (totaalTijd == 5)
      {
        lightDownAllLeds();
      }
      if (totaalTijd == 4)
      {
        lightDownAllLeds();
      }
      if (totaalTijd == 3)
      {
        lightDownAllLeds();
        lightUpLed(0);
      }
      if (totaalTijd == 2)
      {
        lightDownAllLeds();
        lightUpLed(0);
        lightUpLed(1);
      }
      if (totaalTijd == 1)
      {
        lightDownAllLeds();
        lightUpLed(0);
        lightUpLed(1);
        lightUpLed(2);
      }
      if (totaalTijd == 0)
      {
        lightDownAllLeds();
        lightUpAllLeds();
      }
      tick();
    }

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
void displayAantalSeconden() {
  writeNumberAndWait(totaalTijd, 100); // lib van Elias De Hondt
  //writeNumber(totaalTijd);
  printf("teller: %d\n", totaalTijd);
}

ISR(PCINT1_vect) {
  if (buttonPushed(0) && statusB2 == 1 && statusB3 == 1) {
    statusB1 = 0;
    statusB2 = 1;
    statusB3 = 1;
    printf("button 1 pushed\n");
  }
  if (buttonPushed(1) && statusB1 == 0 && statusB3 == 1) {
    statusB1 = 0;
    statusB2 = 0;
    statusB3 = 1;
    printf("button 2 pushed\n");
  }
  if (buttonPushed(2) && statusB1 == 0 && statusB2 == 0) {
    statusB1 = 0;
    statusB2 = 0;
    statusB3 = 0;
    printf("button 3 pushed\n");
  }
  if (totaalTijd > 0) {
    logs[totaalTijd - 1].tijdstip = totaalTijd;
    logs[totaalTijd - 1].buttonsPushed = getButtonStatus();
    printf("tijdstip: %d\n is knop %d ingedrukt\n", logs[totaalTijd - 1].tijdstip, logs[totaalTijd - 1].buttonsPushed[0]);
  }
}

int main() {
  sei();  // Schakel interrupts in
  initUSART();
  initDisplay();
  initTimer();

  enablePotentio();
  enableBuzzer();
  enableAllLeds();
  enableAllButtons();
  enableAllButtonInterrupts(); // lib van Elias De Hondt
  //enableAllButtonToIntterupt();
  totaalTijd = instellenAantalSeconden();
  uint16_t starttijd = totaalTijd;
  startTimer();
  logs = calloc(totaalTijd, sizeof(Tijdstip));
  while (statusB3 == 1) {
    displayAantalSeconden();
    if (starttijd == 0) printf("BOEM! de bom is ontploft!!!\n");
  }

  for (int i = 0; i < starttijd; i++) printf("tijdstip: %d\n is knop %d ingedrukt\n", logs[i].tijdstip, logs[i].buttonsPushed[0]);
  return 0;
}