/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <string.h>

int main() {
  initUSART();
  int getal = 123;
  printf("\ngetal -> \n");
  printf("Waarde: %d\n", getal); // 123
  printf("Adres: %p\n", &getal); // 0x8ef
  printf("Bytes: %d\n", sizeof(getal)); // 2

  int* p = &getal;
  printf("\np -> \n");
  printf("Waarde: %d\n", p); // 2287
  printf("Adres: %p\n", &p); // 0x8f1
  printf("Bytes: %d\n", sizeof(p)); // 2

  int tab[] = {100, 200, 300};
  printf("\ntab -> \n");
  for (int i = 0; i < 3; i++) {

    printf("Waarde van tab[%d]: %d\n", i ,tab[i]); // 100, 200, 300
    printf("Adres: %p\n", &tab[i]); // 0x8e7, 0x8e9, 0x8eb
    printf("Bytes: %d\n", sizeof(tab[i])); // 2
  }
  printf("Grootte: %d", sizeof(tab)); // 2

  char str[10] = "arduino";
  printf("\nstr -> \n");
  printf("str -> %s", str);

  for (int i = 0; i < 10; i++) {
    printf("In str[%d] zit '%c' (ascii %d) op adres %p\n", i, str[i], str[i], str[i]);
  }
  printf("Lengte: %d\n", strlen(str)); // 7
  printf("Lengte: %d\n", sizeof(str)); // 10
  
  return 0;
}