/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 01/05/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <usart.h>
#include <led.h>
#include <button.h>
#include <display.h>
#include <potentio.h>
#include <buzzer.h>
#include <timer.h>

#define BUTTONDELAY _delay_ms(500);

typedef struct { // TODO
  uint16_t volgnr;
  uint16_t gemisteAanvallen;
  float minuten;
  float seconden;
} RONDE;

uint8_t button_pushed = 0; // Boolean
uint8_t live = 4;
uint8_t pawn;
uint8_t display = 1;
uint8_t moveDown = 0; // Boolean
uint8_t down = 2; // Boolean
uint8_t teller = 0;
uint16_t seed;
uint8_t score = 0; // The score is increased by 1 after each round.

void initializing() { // Default configuration and initialization.
  initUSART();
  initDisplay();
  displayOff();
  enableAllLeds();
  lightDownAllLeds();
  enableAllButtons();
  enableBuzzer();
  printString("Basic initialization completed.\n"); // Serial feedback.
}

void startup() {
  printString("Draai aan de potentiometer en druk op een knop naar keuze om het spel te starten.\n"); // Serial feedback.
  while (1) { // Player has not started the game yet.
    heartbeat(400);
    if (buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) {
      seed = readPotentio(); // 0 ... 1023
      srand(seed);
      countdown();
      startTone(); // Small sound to indicate that the game is about to start.
      BUTTONDELAY;
      break;
    }
  }
}

void gameOver() { // This method is responsible for the conclusion of the game.
  if (score <= 4) printf("Game Over!!!\n%d points: not bad", score); // Serial feedback.
  else if (score > 4 && score <= 10) printf("Game Over!!!\n%d points: you are so great!", score); // Serial feedback.
  else if (score > 10) printf("Game Over!!!\n%d points: thats amazing!”", score); // Serial feedback.
  scrollingString("eindscore", 1000);
  while(1) ledLus();
}

ISR(PCINT1_vect) { // Method that is responsible for all interruptions.
  if (buttonPushed(1)) button_pushed = !button_pushed;
}

void subtractLive() { // The name of the function is self-explanatory :).
  negativeTone();
  live--;
  printf("One live has been subtracted. Number of live: %d\n", live); // Serial feedback.
}

void initializeLedCounter() { // Ensures that the 4 LEDs always display the correct value.
  if (live == 4) lightUpAllLeds(); // Default behavior.
  if (live <= 3) {
    flashLed(live, 1000);
    lightDownLed(live);
  }
}

void printLed() { // Method that is responsible for showing the correct info on the display at all times.
  writeToSegment(pawn, 0b11110111); // Bottom line of seven segment display (Player).
  if (teller == 0 || teller == 1) {
    writeToSegment(display, 0b11111110); // display x led A
  }
  else if (teller == 2) {
    if (down == 0) writeToSegment(display, 0b11011111); // display x led F
    if (down == 1) writeToSegment(display, 0b11111101); // display x led B
  }
  else if (teller == 3) {
    writeToSegment(display, 0b10111111); // display x led G
  }
  else if (teller == 4) {
    if (down == 0) writeToSegment(display, 0b11101111); // display x led E
    if (down == 1) writeToSegment(display, 0b11111011); // display x led C
  }
  else if (teller == 5) {
    writeToSegment(display, 0b11110111); // display x led D
  }
}

void moveEnemy() {
  if (moveDown == 0) { // (A | G | D)
    uint8_t horizontal = rand() % 2; // van 0 tot 1
    if (horizontal == 0 && display > 0) display = display - 1; // Move to the left (Computer).
    if (horizontal == 1 && display < 3) display = display + 1; // Move to the right (Computer).
    teller++;
    moveDown = !moveDown;
  }
  else if (moveDown == 1) { // (F of B | E of C)
    uint8_t vertical = rand() % 2; // van 0 tot 1
    down = vertical;
    teller++;
    moveDown = !moveDown;
  }
  printLed(); // Is a bit redundant, But it looks better.
}

void gameLoop() {
  if (buttonPushed(0)) { // Move to the left (Player).
    if (pawn > 0) pawn--;
    moveEnemy();
    BUTTONDELAY;
  }
  if (button_pushed) { // Pause game.
    printString("The game is paused.\n"); // Serial feedback.
    BUTTONDELAY;
    while (button_pushed) ledLus();
    BUTTONDELAY;
  }
  if (buttonPushed(2)) { // Move to the right (Player).
    if (pawn < 3) pawn++;
    moveEnemy();
    BUTTONDELAY;
  }
  printLed();
}

int main() {
  initializing();
  startup();
  initializeLedCounter(); // Set up the life counter.
  enableButtonInterrupt(1); // Pause game.
  while (1) {
    gameLoop();
    if (pawn == display && teller == 5) {
      subtractLive();
      initializeLedCounter();
      if (live == 0) gameOver();
      teller = 0; // Set counter to zero for a new round.
    }
    if (teller == 5) {
      score++; // Player has completed a round.
      teller = 0; // Set counter to zero for a new round.
      positiveTone();
    }
  }
  return 0;
}