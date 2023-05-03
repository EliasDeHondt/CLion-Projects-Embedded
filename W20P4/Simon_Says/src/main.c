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

#define DELAY _delay_ms(500)

int button_pushed = 0;
int teller = 0;
int status = 1;

ISR(PCINT1_vect) {
  if (buttonPushed(0)) button_pushed = !button_pushed;
}

void opstart() {
  printf("\nDruk op knop1 om het spel te starten\n");
  while (!button_pushed) {
    if (button_pushed) lightDownLed(3);
    else {
      flashLed(3, 500);
      teller++;
    }
  }
}

void generatePuzzle(uint8_t* pointer, int len) {
  for (int i = 0; i < len; i++) pointer[i] = rand() % 3;
}

void printPuzzle(uint8_t* pointer, int len) {
  printf("De oplossing -> [");
  for (int i = 0; i < len; i++) printf("%d ", pointer[i]);
  printf("]\n");
}

void playPuzzle(uint8_t* pointer, int len) {
  printf("Simon Says:\n");
  for (int i = 0; i < len; i++) {
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
      if (pointer[index] == 0) index++;
      else return 0;
      DELAY;
    }
    if (buttonPushed(1)) {
      if (pointer[index] == 1) index++;
      else return 0;
      DELAY;
    }
    if (buttonPushed(2)) {
      if (pointer[index] == 2) index++;
      else return 0;
      DELAY;
    }
    if (index == len + 1) return 1;
  }
}

void gameLoop(uint8_t* pointer, int len) {
  for (int i = 0; i < len; i++) {

    // Opgave 4: Afspelen van de puzzle.
    playPuzzle(pointer, i);

    // Opgave 5: Uitlezen van de input van de gebruiker.
    status = readInput(pointer, i);

    // Opgave 6: Het volledige spel
    if (status == 0) {
      printf("Fout, het juiste patroon was: [");
      for (int j = 0; j < i; j++) printf("%d ", pointer[j]);
      printf("]\n");
      break;
    }
    else {
      printf("Correct, we gaan naar level %d\n", (i + 1));
      flashLed(3, 500);
    }
  }
  cli();
}

int main() {
  // Standaard config.
  initUSART(); // Zorgen dat je printf(); kan gebruiken.
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

  // Opgave 4, 5 en 6: Game Loop
  gameLoop(reeks, sizeof(reeks));
  
  if (status) printf("Proficiat, je bent de Simon Master!");
  
  return 0;
}