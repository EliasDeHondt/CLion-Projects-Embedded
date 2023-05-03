/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 01/05/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include <usart.h>
#include <led.h>
#include <button.h>
#include <display.h>

#define BUTTONDELAY _delay_ms(200);

uint8_t button_pushed = 0;
uint8_t points = 0;
uint8_t pawn = 0;
uint8_t display = 1;
uint8_t moveDown = 0;
uint8_t down = 2;
uint8_t teller = 0;
int seed;

void initializing() { // Default configuration and initialization.
  initUSART();
  initDisplay();
  enableAllLeds();
  lightDownAllLeds();
  enableAllButtons();
  enableButtonInterrupt(1); // Pause game.
  printf("Basic initialization completed.\n"); // Serial feedback.
}

ISR(PCINT1_vect) { // Method that is responsible for all interruptions.
  if (buttonPushed(1)) button_pushed = !button_pushed;
}

void won() { // This method is responsible for the conclusion of the game.
  printString("You won!!!\n"); // Serial feedback.
  while(1) ledLus();
}

void addPoint() { // The name of the function is self-explanatory :).
  points++;
  printf("One point has been added. Number of points: %d\n", points); // Serial feedback.
}

void initializeLedCounter() { // Ensures that the 4 LEDs always display the correct value.
  if (points == 0) lightDownAllLeds(); // Default behavior.
  if (points <= 4) {
    flashLed((points-1), 1000);
    lightUpLed((points-1));
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
    srand(seed);
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
  printLed();
}

void gameLoop() {
  if (buttonPushed(0)) { // Move to the left (Player).
    if (pawn > 0) {
      pawn--;
      moveEnemy();
    }
    BUTTONDELAY;
  }
  if (button_pushed) { // Pause game.
    printf("The game is paused.\n"); // Serial feedback.
    BUTTONDELAY;
    while (button_pushed) ledLus();
    BUTTONDELAY;
  }
  if (buttonPushed(2)) { // Move to the right (Player).
    if (pawn < 3) {
      pawn++;
      moveEnemy();
    }
    BUTTONDELAY;
  }
  seed++; // To generate random numbers at all times.
  printLed();
}

int main() {
  initializing();
  initializeLedCounter();
  while (1) {
    gameLoop();
    if (pawn == display && teller == 5) {
      addPoint();
      initializeLedCounter();
      if (points == 4) won();
    }
    if(teller == 5) teller = 0;
  }
  return 0;
}