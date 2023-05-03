/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <util/delay.h>
#include <usart.h>
#include <string.h>
#include <button.h>
#include <stdlib.h>

/*
Jantje is stout geweest in de les en moet van de meester 100 keer de zin 
"Ik mag niet praten in de les" op bord schrijven. Jantje is een slim kereltje en vraagt of het ok is als hij een 
programmaatje schrijft dat die zin 100 keer naar de heap van zijn ATMega328p schrijft. De meester gaat akkoord!
 Help je Jantje even bij zijn strafwerk?

Opgave 1
  Schrijf een eenvoudig programmaatje dat 100 keer de zin "Ik mag niet praten in de les" 
  naar de Serial Monitor stuurt, zodra er op de eerste knop van de Arduino gedrukt wordt. 
  Je maakt GEEN gebruik van interrupts voor deze oefening.

Verwachtte output op de Serial Monitor:
  ...
  96:Ik mag niet praten in de les.
  97:Ik mag niet praten in de les.
  98:Ik mag niet praten in de les.
  99:Ik mag niet praten in de les.
  100:Ik mag niet praten in de les.

Opdracht 2
  Schrijf een functie void schrijfStrafOpHeap(char zin[]) die nu de zin op  de heap gaat plaatsen:
    Je alloceert juist voldoende plek op de heap om de zin te kunnen bevatten. 
    Je moet hiervoor de lengte van de string vinden, daarvoor kan je stringfuncties uit string.h gebruiken. Vergeet de sluitnul niet!
    Je gebruikt een stringfunctie uit string.h om de meegegeven string naar de ge-alloceerde plaatst op de heap te kopiëren.

Pas nu je hoofdlus (in de main) aan, zodat bovenstaande functie gebruikt wordt om de string telkens naar de heap te kopiëren. 
Wat merk je? 
Extra: probeer te weten te komen hoeveel plaats er eigenlijk op de heap effectief is. 
Je kan dit bijvoorbeeld doen door in een globale variabele bij te houden hoeveel plek je juist gereserveerd hebt, 
en dit elke keer af te printen...

Verwachte output:
  ...
  51:Ik mag niet praten in de les.
  "Ik mag niet praten in de les." staat op heap...
  Op heap zijn nu 1530 bytes bezet...
  52:Ik mag niet praten in de les.
  "Ik mag niet praten in de les." staat op heap...
  Op heap zijn nu 1560 bytes bezet...
  ...
*/

char str[] = "Ik mag niet praten in de les.";

void schrijfStrafOpHeap(char zin[]) {
    int lengte = strlen(zin);

}

int main() {
  initUSART();
  enableButton(0);
  
  while (1) if (buttonPushed(0)) {
    for (int i = 1; i <= 100; i++) {
        printf("%d:%s\n", i, str);
        
        //schrijfStrafOpHeap(str);
    }

  }
  return 0;
}