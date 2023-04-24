/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>

void increment_byref(int* a){
    printf("Incrementing a (%d)\n", *a);
    (*a)++;
}

void increment_byval(int a){
    printf("Incrementing a (%d)\n",a);
    a++;
}

void array_as_parameter(int* p){
  //hoe groot is de array in bytes?
  printf("sizeof array as parameter:%d\n",sizeof(p));

}

int main(){
  initUSART();
  int a = 10;
  int* b = &a;
  int c[] = {1,2,3};
  int d[] = {1,2,3,4,5,6};

  printf("Value of a: %d\n",a); 
  //hoeveel bytes neemt een int in beslag?
  printf("sizeof a:%d\n",sizeof(a));
  //op welk adres is a opgeslagen (hexadecimaal)? 
  //(Je kan %d gebruiken als je het adres decimaal wil zien, negeer dan de warning...)
  printf("Value of &a: %p\n",&a);
  //b bevat het adres van a
  printf("Value of b: %p\n",b);
  //hoe groot is b (dus hoe groot is een int pointer)?
  printf("sizeof b:%d\n",sizeof(b));
  //en wat is het adres van b zelf?
  printf("Value of &b: %p\n",&b);
  //een array is eigenlijk een pointer naar het eerste element...
  printf("Value of c: %p\n",c);
  //een array is dus hetzelfde als het adres van het eerste element...
  printf("Value of &c[0]: %p\n",&c[0]);
  //hoe groot is de array in bytes?
  printf("sizeof c:%d\n",sizeof(c));
  //geef array als parameter mee
  array_as_parameter(c);
  printf("Value of d: %p\n",d);
  printf("sizeof d:%d\n",sizeof(d));
  increment_byval(a);
  printf("Value of a after by val increment: %d\n",a);
  increment_byref(&a);
  printf("Value of a after by ref increment: %d\n",a);

  return 0;
}