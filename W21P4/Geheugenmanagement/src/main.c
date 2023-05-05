/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <stdlib.h>
#include <usart.h>
#include <string.h>

#define MAX 5
#define AANTAL 7

void drukNamen(char** namen, int aantal) {
  printString("\nNamen: \n");
  for (int i = 0; i < aantal; i++) {
    printf("de %d° naam is: %s\n", i, namen[i]);
  }
}

int main() {
  initUSART();

  int* tabc;
  tabc = calloc(MAX, sizeof(int));

  printString("\nDe inhoud van de array tabc:");

  for (int i = 0; i < MAX; i++) {  // doorlopen van de array gebruikmakende van de []-notatie
    printf(" %d ", tabc[i]);       // initiële waarde
  }

  int* tabm;
  tabm = malloc(MAX * sizeof(int));

  printString("\nDe inhoud van de array tabm:");

  for (int i = 0; i < MAX; i++) {  // doorlopen van de array gebruikmakende van de pointer-notatie
    printf(" %d ", *(tabm + i));       // initiële waarde *(tabm + i) = tabm[i]
  }

  int* p;
  p = tabm;

  printString("\nDe inhoud van de array p:");

  for (int i = 0; i < MAX; i++) {  // doorlopen van de array gebruikmakende van een variabele pointer
    *p = i * i;
    printf("\np= %d tabm= %d", *p, tabm[i]);
    p++;
  }


  free(tabc);
  free(tabm);


  char namen[AANTAL][10] = {"Hans", "Anniek", "Wim", "Wouter", "Maarten", "Mark"," Dominique"};
  char* pnamen[AANTAL];  // een array van pointers naar een char

  for (int i = 0; i < AANTAL; i++) {
    pnamen[i] = malloc(strlen(namen[i]) + 1);
    strcpy(pnamen[i], namen[i]);
  }

  drukNamen(pnamen, AANTAL); // print
  for (int i = 0; i < AANTAL; i++) free(pnamen[i]); // Drop
  

  char** ppnamen = calloc(AANTAL, sizeof(char*));  // een pointer naar een pointer naar een char
  for (int i = 0; i < AANTAL; i++) {
    *(ppnamen + i) = malloc(strlen(namen[i]) + 1);
    strcpy(*(ppnamen + i), namen[i]);
  }

  drukNamen(ppnamen, AANTAL); // print
  for (int i = 0; i < AANTAL; i++) free(*(ppnamen + i)); // Drop
  


  free(ppnamen);

  return 0;
}