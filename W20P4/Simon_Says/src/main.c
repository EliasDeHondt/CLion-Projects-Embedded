/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <usart.h>
#include <led.h>
#include <button.h>
#include <usart.h>

#define DELAY _delay_ms(500)

int button_pushed = 0;
int teller = 0;

ISR(PCINT1_vect) {
  if (buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) { button_pushed = !button_pushed; }
}

void opstart() {
  printf("Druk op één van de 3 knoppen voor het spel te starten\n");
  while (!button_pushed) {
    if (button_pushed) { lightDownLed(3); } 
    else { 
      lightUpLed(3);
      DELAY;
      lightDownLed(3);
      DELAY;
      teller++;
    }
  }
}

void generatePuzzle(uint8_t* pointer, int len) {
  for (int i = 0; i <= len; i++) { pointer[i] = rand() % 3; }
}

void printPuzzle(uint8_t* pointer, int len) {
  printf("De oplossing -> [");
  for (int i = 0; i <= len; i++) { printf("%d ", pointer[i]); }
  printf("]\n");
}

void playPuzzle(uint8_t* pointer, int len) {
  printf("Simon Says:\n");
  for (int i = 0; i <= len; i++) {
    lightUpLed(pointer[i]);
    DELAY;
    lightDownLed(pointer[i]);
    DELAY;
  }
}

int readInput(uint8_t* pointer, int len) {
  printf("Vul nu je antwoord in\n");
  int index = 0;
  while (1) {
    if (buttonPushed(0)) {
      if (pointer[index] == 0) { index++; }
      else { return 0; }
      DELAY;
    }
    if (buttonPushed(1)) {
      if (pointer[index] == 1) { index++; }
      else { return 0; }
      DELAY;
    }
    if (buttonPushed(2)) {
      if (pointer[index] == 2) { index++; }
      else { return 0; }
      DELAY;
    }
    if (index == len + 1) { return 1; }
  }
}

int main() {
  // Standaard config.
  initUSART(); // Ervoor zorgen dat je printf(); kan gebruiken.
  enableAllLeds();
  enableAllButtons();
  enableAllButtonInterrupts();
  lightDownAllLeds();

  // Opgave 1: De opstart.
  opstart();

  // Opgave 2: Seeden van de randomgenerator.
  srand(teller);

  // Opgave 3: Aanmaken van de random reeks.
  uint8_t reeks[10];
  generatePuzzle(reeks, sizeof(reeks));
  printPuzzle(reeks, sizeof(reeks));

  // Opgave 4: Afspelen van de puzzle.
  playPuzzle(reeks, sizeof(reeks));

  // Opgave 5: Uitlezen van de input van de gebruiker.
  int status = readInput(reeks, sizeof(reeks));

  // Opgave 6: Het volledige spel
  if (status) { printf("Gefeliciteerd, je hebt alles juist!!!"); }
  else { printf("Je hebt een fout gemaakt!!!"); }

  return 0;
}