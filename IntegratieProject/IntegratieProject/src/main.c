/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 01/05/2023
 */

#include <util/delay.h>    // Provides delay functions for time-sensitive operations.
#include <avr/io.h>        // Provides access to the I/O pins of the AVR microcontroller.
#include <avr/interrupt.h> // Provides functions for handling interrupts.
#include <stdlib.h>        // Provides standard library functions, such as memory allocation and random number generation.
#include <unistd.h>        // Provides access to POSIX operating system API functions.
#include <string.h>        // Provides functions for manipulating strings.

#include <usart.h>         // Provides functions for communicating over a USART serial port.
#include <led.h>           // Provides functions for controlling LEDs.
#include <button.h>        // Provides functions for detecting button presses.
#include <display.h>       // Provides functions for controlling a display screen.
#include <potentio.h>      // Provides functions for reading analog input from a potentiometer.
#include <buzzer.h>        // Provides functions for controlling a buzzer.
#include <timer.h>         // Provides functions for setting up and controlling timers.

#define BUTTONDELAY _delay_ms(500)
#define MULTIPLE 250

typedef struct {
  uint16_t followNumber, missedattacks, minutes, seconds;
} ROUND;

// Global variables.
uint8_t button_pushed = 0;  // Boolean (Staat standaard op 0 = False).
uint32_t counter = 0;
uint16_t seconds = 0;       // Seconds per round.
uint8_t player_Pawn;
uint8_t computer_Pawn[2] = {1, 3};
uint8_t moveDown = 0;       // Boolean (Staat standaard op 0 = False).
uint8_t down = 2;           // Boolean (Staat standaard op 2 = NULL).
uint8_t teller = 0;         // Indicate which display segment should be addressed. (Van 0 tot 5) 
uint8_t score = 0;          // The score is increased by 1 after each round.

void initializing() { // Default configuration and initialization.
  initUSART();
  initDisplay();
  displayOff();
  enableAllLeds();
  lightDownAllLeds();
  enableAllButtons();
  enableBuzzer();
  enableTimer2();
  printString("Basic initialization completed.\n"); // Serial feedback.
}

uint8_t startup() { // Preparing the game.
  printString("Turn the potentiometer and press a button of your choice to start the game.\n"); // Serial feedback.
  while (1) { // Player has not started the game yet.
    heartbeat(400);
    if (buttonPushed(0) || buttonPushed(1) || buttonPushed(2)) {
      uint16_t seed = readPotentio(); // 0 ... 1023
      uint8_t live = 4;
      srand(seed);
      countdown();
      startTone(); // Small sound to indicate that the game is about to start.
      startTimer2();
      return live;
    }
  }
}

void accessHeap(ROUND* rounds, uint8_t read) { // Read/Write To/From Heap
  if (read) { // Read From Heap.
    for (uint8_t i = 0; i < 4; i++) {
      printf("FollowNumber: %d \t Missedattacks: %d \t", rounds[i].followNumber, rounds[i].missedattacks);
      printf("Minutes: %d \t Seconds: %d\n", rounds[i].minutes, rounds[i].seconds);
    }
  } 
  else { // Write To Heap
    // Calculate the score for the current round
    uint8_t total_missedattacks = 0;
    for (uint8_t i = 0; i < 4; i++) total_missedattacks += rounds[i].missedattacks;
    uint8_t current_round_score = score - total_missedattacks;
    // Update the current round data in the heap
    for (uint8_t i = 0; i < 3; i++) {
      rounds[i] = rounds[i+1];
      rounds[i].followNumber = i + 1;
    }
    rounds[3].followNumber = 4;
    rounds[3].missedattacks = current_round_score;
    rounds[3].minutes = seconds / 60;
    rounds[3].seconds = seconds % 60;
  }
}

void gameOver(ROUND* rounds) { // This method is responsible for the conclusion of the game.
  printString("Gameplay:\n"); // Serial feedback.
  accessHeap(rounds, 1); // Read From Heap.

  int totalTime = 0;
  for (uint8_t i = 0; i < 4; i++) totalTime = totalTime + rounds[i].seconds;
  printf("Total time: %d\n", totalTime); // Serial feedback.

  printf("Personalized message:\t%d points: %s\n", score, score <= 4 ? "not bad" : (score > 4 && score <= 10 ? "you are so great!" : "thats amazing!")); // Serial feedback.

  scrollingString("eindscore", 1000);
  stopTimer2(); // Shutting down game timer.
  free(rounds); // free heap.
  printString("Press the restart button to play again.\n");
  while(1) ledLus(); // Endless Light Show does not stop ()
}

ISR(PCINT1_vect) { // Method that is responsible for all interruptions.
  if (buttonPushed(1)) button_pushed = !button_pushed;
}

uint8_t subtractLive(uint8_t live) { // The name of the function is self-explanatory :).
  negativeTone();
  live--;
  printf("One live has been subtracted. Number of live: %d\n", live); // Serial feedback.
  return live;

}

void initializeLedCounter(uint8_t live) { // Ensures that the 4 LEDs always display the correct value.
  if (live == 4) lightUpAllLeds(); // Default behavior.
  if (live <= 3) {
    flashLed(live, 1000);
    lightDownLed(live);
  }
}

void printLed(uint8_t pawn) { // Method that is responsible for showing the correct info on the display at all times.
  writeToSegment(player_Pawn, 0b11110111); // Bottom line of seven segment display (Player).

  if (teller == 1) writeToSegment(pawn, 0b11111110); // display x led A

  else if (teller == 2) {
    if (down == 0) writeToSegment(pawn, 0b11011111); // display x led F
    if (down == 1) writeToSegment(pawn, 0b11111101); // display x led B
  }

  else if (teller == 3) writeToSegment(pawn, 0b10111111); // display x led G

  else if (teller == 4) {
    if (down == 0) writeToSegment(pawn, 0b11101111); // display x led E
    if (down == 1) writeToSegment(pawn, 0b11111011); // display x led C
  }

  else if (teller == 5) writeToSegment(pawn, 0b11110111); // display x led D
  
}

void moveEnemy() {
  if (moveDown == 0) { // (A | G | D) (False)
    for (uint8_t i = 0; i < 2; i++) {
      uint8_t horizontal = rand() % 2; // van 0 tot 1
      if (horizontal == 0 && computer_Pawn[i] > 0) computer_Pawn[i] -= 1; // Move to the left (Computer).
      if (horizontal == 1 && computer_Pawn[i] < 3) computer_Pawn[i] += 1; // Move to the right (Computer).
    }
    teller++;
    moveDown = !moveDown;
  }
  else if (moveDown == 1) { // (F of B | E of C) (True)
    uint8_t vertical = rand() % 2; // van 0 tot 1
    down = vertical;
    teller++;
    moveDown = !moveDown;
  }
  printf("JavaData %d%d%d%d\n", computer_Pawn[0], player_Pawn, teller, down); // JavaFx (EXTRA)
  if (score >= 2) printf("JavaData %d%d%d%d\n", computer_Pawn[1], player_Pawn, teller, down); // JavaFx (EXTRA)
}

ISR(TIMER2_COMPA_vect) { // This ISR runs every 4ms. Timer Interrupt.
  counter++; // Increase counter by 1.
  // Als counter + 1 deelbaar is door VEELVOUD tel één seconde.
  if (counter % MULTIPLE == 0) { // If counter + 1 is divisible by MULTIPLE count one second.
    moveEnemy();
    seconds++;
  }
}

void gameLoop() {
  if (buttonPushed(0)) { // Move to the left (Player).
    if (player_Pawn > 0) player_Pawn--;
    BUTTONDELAY;
  }
  if (button_pushed) { // Pause game.
    printString("The game is paused.\n"); // Serial feedback.
    BUTTONDELAY;
    stopTimer2();
    while (button_pushed) ledLus();
    startTimer2();
    BUTTONDELAY;
  }
  if (buttonPushed(2)) { // Move to the right (Player).
    if (player_Pawn < 3) player_Pawn++;
    BUTTONDELAY;
  }
  printLed(computer_Pawn[0]);
  if (score >= 2) printLed(computer_Pawn[1]);
}

int main() {
  initializing();
  uint8_t live = startup();
  initializeLedCounter(live); // Set up the life counter.
  enableButtonInterrupt(1); // Pause game.
  ROUND* rounds = calloc(4, sizeof(ROUND)); // Reserving 4 rounds In the heap.

  while (1) {
    gameLoop();
    
    if ((player_Pawn == computer_Pawn[0] || player_Pawn == computer_Pawn[1]) && teller == 5) { // Next round is initiated.
      live = subtractLive(live);
      accessHeap(rounds, 0); // Write To Heap.
      initializeLedCounter(live);
      if (live == 0) gameOver(rounds);
      teller = 0; // Set counter to zero.
      seconds = 0;
    }

    else if (teller == 5) { // Keeping the same round.
      score++; // Player has completed a round.
      teller = 0; // Set counter to zero.
      positiveTone();
    }
  }
  return 0;
}