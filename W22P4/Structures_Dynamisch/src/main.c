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

typedef struct {
  int waarde;
  char* kleur; //opgelet: pointer, want we willen juist genoeg reserveren: [OK]
} KAART;

void vulBoek(KAART* boek) {
  char kleuren[4][10] = {"harten", "ruiten", "schoppen", "klaveren"};
  int index;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      index = (i * 13) + j;
      //TODO: gebruik malloc om juist genoeg ruimte te reserveren voor de kleur: [OK]
      boek[index].kleur = malloc(strlen(kleuren[i] + 1));
      //TODO: kopieer de kleur naar de gealloceerde ruimte: [OK]
      strcpy(boek[index].kleur, kleuren[i]);
      //TODO: stel de waarde van de kaart in: [OK]
      boek[index].waarde = j;
    }
  }
}

// OPGELET: er komt een adres van een KAART binnen:
void toonKaart(KAART* deKaart) {
  switch (deKaart->waarde) {
    //TODO: pas onderstaande code aan: [OK]
    case 1:
      printf("%s aas", deKaart->kleur);
      break;
    case 11:
      printf("%s boer", deKaart->kleur);
      break;
    case 12:
      printf("%s dame", deKaart->kleur);
      break;
    case 13:
      printf("%s heer", deKaart->kleur);
      break;
    default:  // alle andere kaarten:
      printf("%s %d", deKaart->kleur, deKaart->waarde);
  }
}

// OPGELET: de returnwaarde is een pointer!
KAART* trekKaart(KAART boek[]) {
  int willek = rand() % 52; // Van 0 tot 51
  //TODO: retourneer het adres van de willekeurige kaart: [OK]
  return &boek[willek];
}

int main() {
  initUSART();
  //TODO: Gebruik calloc om de boek kaarten aan te maken: [OK]
  KAART* boek = calloc(52, sizeof(KAART));
  vulBoek(boek);

  // TODO: pas onderstaande code aan zodat ze compileert: [OK]
  for (int i = 0; i < 10; i++) {
    KAART* kaart = trekKaart(boek);
    toonKaart(kaart);
    printf("\n");
  }

  //TODO: geef alle dynamisch gereserveerde ruimte weer vrij: [OK]
  for (int i = 0; i < 52; i++) free(boek[i].kleur);
  //free(boek->kleur);
  free(boek);

  return 0;
}