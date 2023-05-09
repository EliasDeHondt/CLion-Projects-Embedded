/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

/*
We schrijven een programmaatje dat een muziekstukje genereert.
Druk je op een knop, dan genereert je Arduino een willekeurig muziekje en speelt
het 2 keer na elkaar af!

We gebruiken structs om een SONG en een NOTE te definiëren. Vervolgens schrijven
we de functies:

void playNote(NOTE* note): speel een NOTE af op de buzzer. Heeft de NOTE een
frequency van nul, dan spelen we een rust. SONG* generateSong(char* name,
uint16_t length): genereer een SONG bestaande uit een reeks willekeurige noten.
Zorg dat alles netjes op de HEAP gealloceerd wordt!
void playSong(SONG* song): speel de volledige song af.
Dit is niet zo een eenvoudige oefening, omdat we willen dat alle structures
volledig op de HEAP gealloceerd worden. In wat volgt loodsen we jullie stap voor
stap door de oefening. Je kan ook proberen om de oefening volledig op eigen
kracht te maken, maar lees dan nadien zeker onderstaand stappenplan na om te
kijken of je werkwijze gelijkaardig is!
*/

#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>
#include <string.h>
#include <avr/io.h>
#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <potentio.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>

// FREQUENCIES VAN DE VERSCHILLENDE NOTEN
#define C5 523.250   // do
#define D5 587.330   // re
#define E5 659.250   // mi
#define F5 698.460   // fa
#define G5 783.990   // sol
#define A5 880.000   // la
#define B5 987.770   // ti
#define C6 1046.500  // do

int teller = 0; // voor de random

// Je definieert 2 structures: NOTE en SONG. Een NOTE heeft een frequency (float) en een duration (uint16_t). Een SONG heeft een name (char*), 
// een lijst van notes (NOTE**: het is een array van NOTE*, dus een NOTE**), en een length (aantal noten, uint16_t).
typedef struct {
  float frequency;
  uint16_t duration;
} NOTE;

typedef struct {
  char* naam;
  NOTE** notes;
  uint16_t length;

} SONG;

// Schrijf een functie playNote(NOTE* note) die de gegeven noot afspeelt. Is de frequency 0, dan stelt de noot een rust voor en wacht 
// je dus gewoon de duration. Je kan uiteraard gebruik maken van de playTone functie uit de demo!
void playNote(NOTE* note) {
  if (note->frequency == 0) _delay_ms(note->duration);
  else playTone(note->frequency, note->duration);
}

SONG* generateSong(char* name, uint16_t length) {
  // 1. Alloceer voldoende plek op de HEAP om 1 SONG te bevatten en sla op in
  // SONG* song variabele.
  SONG* song = malloc(sizeof(SONG));
  // 2. Gebruik de parameter om song->length in te stellen.
  song->length = length;
  // 3. Alloceer voldoende plek op de HEAP om de name te bevatten: de lengte van
  // de name + 1 voor de sluitnul. Sla op in song->name. Kopieer nu de parameter
  // name naar song->name.
  char* naam = malloc(sizeof(name + 1));
  strcpy(naam, name);
  // 4. Alloceer voldoende plek op de HEAP om een array te reserveren van length
  // aantal NOTE* elementen en sla op in song->notes
  song->notes = calloc(length, sizeof(NOTE*));
  // 5. In een lus alloceer je nu length keer voldoende ruimte om een NOTE te
  // bevatten en sla op in song->notes[i]. Vul een random frequentie in voor
  // elke NOTE. Gebruik hiervoor een array met mogelijke frequencies (zie muziek
  // tutorial voor de waarden van de noten). Vul een random duration in voor
  // elke NOTE: 1000, 500 of 250.
  uint32_t frequencies[] = {C5, D5, E5, F5, G5, A5, B5, C6};
  uint16_t duration[] = {1000, 500, 250};
  for (int i = 0; i < length; i++) {
    srand(teller);
    uint8_t random_frequencies = rand() % 8;  // van 0 tot 7
    uint8_t random_duration = rand() % 3;     // van 0 tot 2
    song->notes[i] = malloc(sizeof(NOTE));
    song->notes[i]->frequency = frequencies[random_frequencies];
    song->notes[i]->duration = duration[random_duration];
    teller++;
    printf("i = %d\t f = %d\t d =  %d\n", (i + 1), (int)song->notes[i]->frequency, song->notes[i]->duration); // Test
  }
  // 6. Return de song die je nu juist hebt aangemaakt.
  printf("Generate song (%s) OK\n", name);
  return song;
}

void playSong(SONG* song) {
  // Schrijf een functie void playSong(SONG* song) die de verschillende noten van de song na elkaar afspeelt. 
  // Je gebruikt uiteraard je functie playNote (zie hierboven).
  for (int i = 0; i < song->length; i++) {
    playNote(song->notes[i]);
  }
}

int main() {
  initUSART();
  enableButton(0);
  enableBuzzer();
  while (1) {
    teller++;
    if (buttonPushed(0)) {
      SONG* newSong = generateSong("newSong", 10);
      playSong(newSong);
      printString("Song 1 OK\n");
      playSong(newSong);
      printString("Song 2 OK\n");
    }
  }
  return 0;
}