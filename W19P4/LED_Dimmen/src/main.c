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

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/io.h>
#include <led.h>

/*
void dimLed(int lednumber, int percentage, int duration) {
    for (int i = duration; i > 0; i -= 10) { // Is de opgegeven tijdsperiode. (Stap waarde 10)
        lightDownLed(lednumber); // Led x uitzetten.
        _delay_ms(percentage/10); // De tijd dat de Led uit moet staan. (Stap waarde 10)
        lightUpLed(lednumber); // Led x aanzetten.
        _delay_ms((100-percentage)/10); // De tijd dat de Led aan moet staan. (Stap waarde 10)
    }
}

void fadeInLed(int lednumber, int duration) {
    for (int percentage = 1; percentage <= 100; percentage++) { // Door alle mogelijke percentages gaan. (0% tot 100%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightUpLed(lednumber); // Eindpositie van Led.
}

void fadeOutLed(int lednumber, int duration) {
    for (int percentage = 100; percentage > 1; percentage--) { // Door alle mogelijke percentages gaan. (100% tot 0%)
        dimLed(lednumber, percentage, (duration/100));
    }
    lightDownLed(lednumber); // Eindpositie van Led.
}
*/

// Test
int main() {
    enableAllLeds();
    lightDownAllLeds();

    dimLed(0,90,10000);
    fadeInLed(1,10000);
    fadeOutLed(2,10000);

    return 0;
}
