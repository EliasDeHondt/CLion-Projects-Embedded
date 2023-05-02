/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <display.h>
#include <util/delay.h>
#include <usart.h>

/*
Dit is een eenvoudige oefening op het gebruik van de display-library.
Schrijf een programma dat de cijfers van rechts naar links laat binnen 'scrollen'.
Dus eerst verschijnt '1234' en één seconde later: '2345' en vervolgens: '3456',  enz...
Opgelet: na '7890' willen we dat '8901' verschijnt en daarna '9012' enz... Dus het programma blijft eindeloos verdergaan.

TIP: natuurlijk gebruik je een for-loop met een teller en de modulo-operator!
*/

int main() {
    initUSART();
    initDisplay();
    while (1) {
        for (int i = 0; i < 10; i++) {
            int d = i;
            int h = (i + 1) % 10;
            int t = (i + 2) % 10;
            int e = (i + 3) % 10;
            int getal = (d * 1000) + (h * 100) + (t * 10) + e;
            writeNumberAndWait(getal, 1000);
            printf("Getal: %4d\n", getal);
        }
    }
    return 0;
}