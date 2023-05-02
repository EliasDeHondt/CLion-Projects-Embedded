/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <display.h>
#include <util/delay.h>
#include <usart.h>
#include <string.h>

/*
We gaan de display-library uitbreiden zodat we ook letters kunnen tonen.IMG_4335.JPG

In display.h voeg je volgende functieprototypes toe:
  void writeCharToSegment(uint8_t segment, char character);
  void writeString(char* str);
  void writeStringAndWait(char* str, int delay);

In display.c voeg je bovenaan de declaratie toe van een array met de 26 letters van het alfabet:
  const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2,
                                  0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
                                  0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1,
                                  0xC1, 0xD5, 0x89, 0x91, 0xA4};

Werk nu de functie writeCharToSegment uit:
  Controleer het character dat binnenkomt: als het een kleine letter is, 
  converteer dan naar een hoofdletter (door er 32 af te trekken).
  Als het character geen letter uit het alfabet is, dan tonen we een leeg segment. 
  Definieer daarvoor eerst bovenaan een macro SPACE met de waarde 0xFF
  Als het character wél een letter is, dan haal je de overeenstemmende waarde op uit de ALPHABET_MAP
  Stuur nu de waarde naar het specifieke segment (baseer je op de code van writeNumberToSegment)

Werk nu de functie writeString uit:
  Gebruik de juist geschreven functie writeCharToSegment en toon enkel de eerste 4 letters van de string op de display

Tenslotte schrijf je de functie writeStringAndWait (naar analogie van de bestaande functie writeNumberAndWait).
Klaar is Kees! Test uit met een eenvoudige main.
*/

int main() { // Demo
  initDisplay();

  while (1) {
    //writeCharToSegment(0 , 'A');
    //writeStringAndWait("EAZY", 1000);
    //scrollingString("HEY HALLO", 1000);
    //writeStringAndWait("YES", 1000);
    scrollingString("FCOO FAZO FCOO FCOO", 1000);
  }
  return 0;
}