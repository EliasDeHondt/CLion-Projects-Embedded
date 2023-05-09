/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <avr/io.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h>

// Hier definieren we een eigen datatype: KAART met 2 velden: waarde en kleur
typedef struct {
  int waarde;
  char kleur[10];
} KAART;

// Deze functie krijgt als parameter de array van kaarten mee en vult die
// ... met 4 * 13 speelkaarten

void vulBoek(KAART boek[52]) { // OF: KAART* boek[]
  char kleuren[4][10] = {"harten", "ruiten", "schoppen", "klaveren"};
  int index;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      index = (i * 13) + j;
      boek[index].waarde = (j + 1);
      strcpy(boek[index].kleur, kleuren[i]);
    }
  }
}

// Deze functie toont de meegegeven KAART
void toonKaart(KAART deKaart) {
  switch (deKaart.waarde) {
    // de speciale kaarten:
    case 1:
      printf("%s aas", deKaart.kleur);
      break;
    case 11:
      printf("%s boer", deKaart.kleur);
      break;
    case 12:
      printf("%s dame", deKaart.kleur);
      break;
    case 13:
      printf("%s heer", deKaart.kleur);
      break;
    default:  // alle andere kaarten:
      printf("%s %d", deKaart.kleur, deKaart.waarde);
  }
}

// Deze functie trekt een willekeurige kaart uit de array
KAART trekKaart(KAART boek[]) { // OF: KAART* boek[]
  // De random generator wordt wel NIET geseed, dus bij elke run: zelfde reeks kaarten
  int willek = rand() % 52; // Van 0 tot 51
  return boek[willek]; // OF: *(boek + willek);
}

int main() {
  initUSART();
  KAART boek[52]; // een array van structures
  vulBoek(boek);
  // Trek 10 willekeurige kaarten en toon ze:
  for (int i = 0; i < 10; i++) {
    KAART kaart = trekKaart(boek);
    toonKaart(kaart);
    printf("\n");
  }
  return 0;
}