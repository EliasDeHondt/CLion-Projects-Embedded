/*
Een led kan enkel volledig aan of volledig af gezet worden. Om een led "half" aan te zetten (te "dimmen" eigenlijk) maken we gebruik van een trukje: 
we zetten de led in een lus heel snel aan en af zodat hij de helft van de tijd aan is, en de andere helft uit. 
Als we dat snel genoeg doe, zien onze ogen dat als een lampje dat 50% gedimd is. 
Om een ledje tot 20% te dimmen moeten we er dan voor zorgen dat het maar 20% van de tijd aan is, en 80% uit. Deze techniek wordt PWM genoemd (Pulse Width Modulation).

Voeg een functie dimLed(int lednumber, int percentage, int duration) 
toe aan de led library die ervoor zorgt dat de led gedurende de gegeven periode (in milliseconden) gedimd wordt tot het gegeven percentage.

Voeg een functie fadeInLed(int led, int duration) die gebruik maakt van de dimLed functie om een led van 0 tot 100% te laten "infaden" over een periode van duration milliseconden.

Test in een eenvoudig programmaatje!
*/
#include <util/delay.h>
#include <avr/io.h>

void dimLed(int lednumber, int percentage, int duration) {
    // We schuiven de 1 een x (lednumber = x) aantal plaatsen naar links.
    DDRB = (1 << (PB2 + lednumber)); // Enable
    
    // Is de opgegeven tijdsperiode.
    for (int i = duration; i > 0; i -= 10) {

        PORTB = (1 << (PB2 + lednumber)); // Led x uitzetten;

        _delay_ms(percentage/10); // De tijd dat de Led uit moet staan.

        PORTB = ~(1 << (PB2 + lednumber)); // Led x aanzetten.

        _delay_ms((100-percentage)/10); // De tijd dat de Led aan moet staan.
    }
}

void fadeInLed(int led, int duration) {
    // Door alle mogelijke percentages gaan.
    for (int percentage = 0; percentage <= 100; percentage++) {

        
        dimLed(led, percentage, duration);

        
    }
}



// Test
int main() {
    // dimLed(1,90,10000);

    fadeInLed(1,10000);

    return 0;
}
