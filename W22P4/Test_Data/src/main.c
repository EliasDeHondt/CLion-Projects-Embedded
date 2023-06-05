#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>
#include <avr/io.h>
#include <button.h>
#include <buzzer.h>
#include <display.h>
#include <led.h>
#include <potentio.h>
#include <stdlib.h>
#include <usart.h>
#include <util/delay.h>
#include <string.h>

typedef struct {
  char* naam;
  int id;
} STUDENT;

typedef struct {
  char* klasNaam;
  int aantalStudenten;
  STUDENT* studenten;
} KLAS;


int main() {
  initUSART();

  int a = 0;
  int* b = &a;
  printf("a = %d\n", a);
  printf("b = %d\n", *b);

  int c[] = {1, 2, 3, 4, 5};
  int* d = c; // Kan ook: int* d = &c[0]; of int* d = &c; of int* d = c; of int* d = &c[0][0];
  printf("%d", d[0]); // Dit print 1.
  printf("%d", *d); // Dit print ook 1.

  int e[2][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int* f = e; // Kan ook: int* f = &e[0][0]; of int* f = &e[0]; of int* f = e[0]; of int* f = &e;
  for (int i = 0; i < 6; i++) {
    // of printf("e[%d] = %d\n", i, *(f + i)); of printf("e[%d] = %d\n", i, *(*f + i)); of printf("e[%d] = %d\n", i, **(f + i));
    printf("e[%d] = %d\n", i, f[i]); 
  }


  int g[2][3][4] = {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10 ,11, 12}}, {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22 ,23, 24}}};
  int* h = g; // Kan ook: int* h = &g[0][0][0]; of int* h = &g[0][0]; of int* h = &g[0]; of int* h = g[0]; of int* h = &g;
  for (int i = 0; i < 24; i++) {
    // of printf("g[%d] = %d\n", i, *(h + i)); of printf("g[%d] = %d\n", i, *(*h + i)); of printf("g[%d] = %d\n", i, **(h + i)); of printf("g[%d] = %d\n", i, ***h + i);
    printf("g[%d] = %d\n", i, h[i]); 
  }

  // Dynamische allocatie van geheugen:

  // calloc() zet alle bits op 0.
  // malloc() alles blijft zoals het is in het geheugen.
  // realloc() verandert de grootte van de geheugenblokken.
  // free() geeft het geheugen weer vrij.

  // hier is een voorbeeld van gebruik van malloc() en realloc() en free():
  int* i = malloc(5 * sizeof(int));
  // Kan ook: int* i = calloc(5, sizeof(int));

  for (int j = 0; j < 5; j++) i[j] = j; // i[0] = 0, i[1] = 1, i[2] = 2, i[3] = 3, i[4] = 4
  
  for (int j = 0; j < 5; j++) printf("i[%d] = %d\n", j, i[j]); // print i[0] t/m i[4] (1, 2, 3, 4, 5)
  
  i = realloc(i, 10 * sizeof(int)); // i[0] t/m i[4] blijven hetzelfde, maar er is nu ruimte voor 5 extra elementen.

  for (int j = 5; j < 10; j++) i[j] = j; // i[5] = 5, i[6] = 6, i[7] = 7, i[8] = 8, i[9] = 9

  for (int j = 0; j < 10; j++) printf("i[%d] = %d\n", j, i[j]); // print i[0] t/m i[9] (1, 2, 3, 4, 5, 5, 6, 7, 8, 9)

  free(i); // geheugen weer vrijgeven van i[0] t/m i[9] (1, 2, 3, 4, 5, 5, 6, 7, 8, 9)

  // strcpy() kopieert de inhoud van de ene string naar de andere string.
  // Hier een voorbeeld van gebruik van strcpy() met malloc() en free():

  char* namen1[5];
  namen1[0] = malloc(strlen("Elias") + 1);
  strcpy(namen1[0], "Elias");

  STUDENT* student = malloc(sizeof(STUDENT) * 5);

  char* namen2[] = {"naam1", "naam2", "naam3", "naam4", "naam5"};

  for (int i = 0; i < 5; i++) {
    student[i].id = i;
    student->naam = namen2[i]; // ("->") is voor een pointer naar een struct.
  }
  
  // Dinaamische allocatie van geheugen voor een string:
  char* name;
  name = malloc(sizeof(name) + 1);
  strcpy(name, "Elias");
  printf("%s", name);

  // Nu zonder dinamische allocatie van geheugen voor een string:
  char name2[] = "Elias";
  printf("%s", name2);
  


  // Deel 2 van rommel :)

  KLAS* klasen = malloc(sizeof(KLAS) * 4); // Er zijn 4 Klasen.
  klasen->klasNaam = "INF1A";
  klasen->aantalStudenten = 5;
  klasen->studenten = malloc(sizeof(STUDENT) * 5);
  klasen->studenten->naam = "Elias";
  klasen->studenten->id = 1;





  return 0;
}