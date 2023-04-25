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
/*
We bouwen een eenvoudige morse-trainer die je kan gebruiken om te testen hoe
goed je morse-code kent.

Vereisten:
    1. Zodra de applicatie start wordt er een aftelpatroon getoond met de
ledjes, zodat de gebruiker zich kan klaarzetten. Het aftelpatroon werkt als
volgt: je laat eerst de 4 ledjes branden, dan 3, 2, 1 en 0 en dan start de echte
morse-training.

    2. Je herhaalt nu 10 keer volgende stappen:

        2.1. Je toont de morse-code van een willekeurig karakter.
             Om bijvoorbeeld een A te tonen, laat je alle ledjes kort oplichten
en daarna lang oplichten. Voor een Z licht je alle ledjes 2 keer lang op en dan
2 keer kort.

        2.2. Wacht nu even, zodat de gebruiker de tijd krijgt om na te denken en
zijn antwoord voor zichzelf te formuleren.

        2.3. Toon nu het correcte antwoord via printf in de seriële monitor.

    3. Na 10 letters eindigt het programma met een frivool led-dansje dat een
klein beetje tijd in beslag neemt.

Uitbreiding:
    1. Maak gebruik van C arrays om de morse-code in op te slaan.

    2. Schrijf een functie die een string als parameter krijgt, en vervolgens
dat woord in Morse-code toont op de leds...
*/

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
