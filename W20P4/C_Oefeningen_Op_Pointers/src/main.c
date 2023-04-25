/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <string.h>

#define MAX 5
#define MAXNAMEN 7
#define ZEVENVOUD(getal) (getal * 7)

/*
1) Maak een nieuw project "pointerOef_1"
    Definieer 2 macro's: MAX (om het aantal elementen van een array vast te leggen op 5) en ZEVENVOUD 
    (om van een bepaald getal het zevenvoud te berekenen).

    In de main maak je een array van MAX gehele getallen, die je meteen met 0 initialiseert.

    Roep vanuit de main de functie printArray op en geef de array als parameter mee. 
    Je drukt van de array alle elementen af, én ook de adressen waar die elementen zich bevinden (zie voorbeeldafdruk hieronder).

    Roep vanuit de main de functie vulArray op. Daar vul je de array met zevenvouden.

    Roep opnieuw de functie printArray op om de gewijzigde inhoud van de array te controleren.

Voorbeeld van afdruk in terminal:

Inhoud van array:
  Op adres: 0x8f0 zit de waarde: 0
  Op adres: 0x8f2 zit de waarde: 0
  Op adres: 0x8f4 zit de waarde: 0
  Op adres: 0x8f6 zit de waarde: 0
  Op adres: 0x8f8 zit de waarde: 0
Inhoud van array:
  Op adres: 0x8f0 zit de waarde: 0
  Op adres: 0x8f2 zit de waarde: 7
  Op adres: 0x8f4 zit de waarde: 14
  Op adres: 0x8f6 zit de waarde: 21
  Op adres: 0x8f8 zit de waarde: 28

2) Maak een nieuw project "StringOef_2"

  Doe een include van string.h (voor stringfuncties)

  Declareer in de main een array van 7 strings van 10 karakters en zet daarin de namen van je vrienden. Liefst als volgt: 
  char namen[MAX][10] = {"Hans", "Anniek", "Maarten",  ... };

  Maak een functie drukEersteLetters, die de 7 eerste letters van de namen op één regel afdrukt.

  Schrijf een functie zoekKleinsteNaam, die de alfabetisch kleinste naam als returnvalue teruggeeft. De oproep vanuit de main doe je als volgt:
  char* kleinste = zoekKleinsteNaam(namen);

  Druk deze naam in de main af.

Gewenste afdruk in de serial monitor:
  Eerste letters: HAMWDMM
  Kleinste = Anniek
*/

void printArray(int* pointer) {
  printf("\nInhoud van array:\n");
  for (int i = 0; i <+ MAX; i++) {
    printf("\tOp adres: %p zit de waarde: %d\n", pointer, pointer[i]);
  }
}

void vulArray(int* pointer) {
  for (int i = 0; i < MAX; i++) {
    pointer[i] = ZEVENVOUD(i);
  }
}

void drukEersteLetters(char (*pointer)[10]) {
  printf("Eerste letters: ");
  for (int i = 0; i <= MAXNAMEN; i++) {
    printf("%c", pointer[i][0]);
  }
  printf("\n");
}

// Deze declaratie geeft aan dat zoekKleinsteNaam() een pointer teruggeeft naar een char-array.
char *zoekKleinsteNaam(char (*pointer)[10]) {
  int lens[MAXNAMEN]; // array om de lengtes op te slaan
  int index = 0;
  int kleinste = 10;
  for (int i = 0; i < MAXNAMEN; i++) {
    lens[i] = strlen(pointer[i]);
    if (kleinste > lens[i]) {
        kleinste = lens[i];
        index = i;
    }
  }
  return pointer[index];
}

int main() {
  initUSART();
/*
  // pointerOef_1
  int myArray[MAX] = {0}; // Alles op 0.
  printArray(myArray);
  vulArray(myArray);
  printArray(myArray);
*/
  
  // pointerOef_2
  char namen[MAXNAMEN][10] = {"Camille", "Cedric", "Daan", "Dylan", "Jacob", "Tim", "Noah"};
  drukEersteLetters(namen);
  char* kleinste = zoekKleinsteNaam(namen);
  printf("Kleinste = %s", kleinste);

  return 0;
}
