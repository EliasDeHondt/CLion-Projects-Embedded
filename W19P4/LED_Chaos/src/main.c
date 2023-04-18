/*
Schrijf een programmaatje dat de verschillende leds in een random patroon laat flikkeren: willekeurig gekozen leds worden gedurende willekeurig lange periodes 
(tussen bijvoorbeeld 100 en 1000 milliseconden) aan en uit gezet.

Om dit te kunnen doen zal je moeten uitvissen hoe je een random getal kan genereren in de programmeertaal C. Je zal hiervoor de stdlib.h library moeten includen.

In die documentatie kom je deze regel tegen om de random generator een 'seed' te geven:
srand((unsigned) time(&t));

Het idee is dat je de huidige tijd gebruikt als seed van je randomgenerator. Dat werkt prima op een computer die een klok bevat, maar onze AVR heeft geen klok 
(wel een oscillator die 'tikt', maar die begint telkens terug van nul als we de AVR aanzetten). 
Bijgevolg kunnen we onze random generator niet op die manier seeden, en zal er dus steeds dezelfde random reeks gegenereerd worden. 
Je kan aan de srand functie dus gewoon 0 meegeven, maakt niet zoveel uit. In de toekomst zouden we bijvoorbeeld de input van de potentiometer kunnen gebruiken als seed...
*/


