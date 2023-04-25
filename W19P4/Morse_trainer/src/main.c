/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <led.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usart.h>
#include <util/delay.h>

char karakters[36] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                      'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                      'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0',
                      '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char morse[36][6] = {".-",    "-...",  "-.-.",  "-..",   ".",     "..-.",
                     "--.",   "....",  "..",    ".---",  "-.-",   ".-..",
                     "--",    "-.",    "---",   ".--.",  "--.-",  ".-.",
                     "...",   "-",     "..-",   "...-",  ".--",   "-..-",
                     "-.--",  "--..",  "-----", ".----", "..---", "...--",
                     "....-", ".....", "-....", "--...", "---..", "----."};

void streep() {
  lightUpAllLeds();    // Zet al de Lets aan.
  _delay_ms(3000);     // Wacht 3 seconden.
  lightDownAllLeds();  // Zet al de Lets uit.
  _delay_ms(1000);     // Wacht 1 seconden.
}

void punt() {
  lightUpAllLeds();    // Zet al de Lets aan.
  _delay_ms(1000);     // Wacht 1 seconden.
  lightDownAllLeds();  // Zet al de Lets uit.
  _delay_ms(1000);     // Wacht 1 seconden.
}

void startLed() {
  for (int i = 0; i < 4; i++) {
    _delay_ms(1000);  // Wacht 1 seconden.
    lightDownLed(i);  // Zet led x uit.
  }
  lightDownAllLeds();
}

void dans() {
  for (int i = 0; i < 5; i++) {
    for (int y = 0; y < 4; y++) {  // Led aan.
      lightUpLed(y);
      _delay_ms(100);
    }
    for (int y = 0; y < 4; y++) {  // Led uit.
      lightDownLed(y);
      _delay_ms(100);
    }
  }
}

int main() {
  initUSART();       // Voor printf().
  enableAllLeds();   // Schakelt al de leds in.
  lightUpAllLeds();  // Zet al de Lets aan.
  srand(0);          // Set the seed for the random number generator.
  startLed();        // Start Led timer.

  for (int i = 0; i < 10; i++) {
    int random_index = rand() % 36;  // Kies een willekeurig index nummer tussen 0 en 35.
    char karakter = karakters[random_index];

    for (int j = 0; morse[random_index][j] != '\0';
         j++) {  // Zolang dat we niet op het einde van de string zitten.
      if (morse[random_index][j] == '.') {
        punt();  // toon een korte lichtsignaal
      } else {
        streep();  // toon een lange lichtsignaal
      }
    }
  }
  
  dans();  // Led dans.
  return 0;
}
