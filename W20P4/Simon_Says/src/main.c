/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

/*
We werken het bekende spel Simon Says uit. In onze versie "speelt" de Arduino
een telkens langer wordend patroon van lichtjes af, de speler moet proberen dat
patroon na te spelen met de knopjes. Het patroon heeft een maximale lengte
van 10. Wanneer de speler erin slaagt om dat te halen is hij de Simon Master.

Een voorbeeld van de werking:
  Opstart: led4 knippert aan en uit en wacht tot de speler op knop1 duwt, daarna
start het spel Spel zelf: Arduino licht led1 op Speler drukt op knop1: correct
(led4 flikkert paar keer aan en uit). Arduino licht achtereenvolgens led1 en
led3 op Speler drukt achtereenvolgens op knop1 en knop 3: correct (led4 flikkert
paar keer aan en uit). Arduino licht achtereenvolgens led1, led3 en led2 Speler
drukt achtereenvolgens op knop1, knop 3 en knop2: correct (led4 flikkert paar
keer aan en uit). Arduino licht achtereenvolgens led1, led3, led2 en led1 Speler
drukt achtereenvolgens op knop1, knop3, knop2, knop2: fout! (alle 4 de ledjes
gaan aanstaan).

Op de Serial Monitor verschijnt ook informatie:
  bij start: "Druk op knop1 om het spel te starten"
  bij elke druk op een knop: "Je drukte op knop x, correct!" of "Je drukte op
knop x, fout!" bij juiste ingave van een reeks: "Correct, we gaan naar level x"
  bij foute ingave: "Fout, het juiste patroon was: [1 0 2 2 ]"
  bij behalen van eindreeks (level 10): "Proficiat, je bent de Simon Master!"


Om het voor jullie wat eenvoudiger te maken hebben we de oefening hieronder in
een aantal stappen opgedeeld. Als je die volgt zou je tot een mooi werkend
eindresultaat moeten geraken. Je maakt gebruik van functies en ook #define kan
handig zijn om dit project goed leesbaar te houden. Uiteraard kan je ook je
zelfgeschreven libraries (led.h en button.h) gebruiken!

Opgave 1: De opstart
  Zorg dat led4 knippert zolang de speler niet op een knop duwt
  Je gebruikt hiervoor verplicht een interrupt routine (ISR)
  Gebruik een globale variabele "button_pushed" die je op 0 zet (de taal C kent
geen type boolean, 0 staat voor false, 1 (of een ander cijfer) voor true). Je
laat het ledje knipperen zolang die globale variabele op 0 staat. In je ISR zorg
je ervoor dat de variabele op 1 komt te staan.

Opgave 2: Seeden van de randomgenerator
  We willen uiteraard steeds een andere random reeks. Om de random generator
telkens met een andere waarden te 'seeden' kunnen we een handig trukje
gebruiken: we houden een tellertje bij zolang led4 knippert (zorg dat het snel
knippert!), en zodra de gebruiker op een knop drukt gebruiken we de waarde van
dat tellertje als seed voor de randomgenerator. Werk dit uit en test door een
reeks van 10 random getallen naar de Serial Monitor te sturen. Check of je reeks
inderdaad steeds andere waardes krijgt...

Opgave 3: Aanmaken van de random reeks
  Definieer een array van 10 uint8_t in de main functie.
  Schrijf nu een functie "generatePuzzle" die de array (en de lengte van de
array!) meekrijgt als parameter. In deze functie vul je de array op met 10
random getallen tussen 0 en 2 (inclusief). Dit ga je straks gebruiken om led1,
led2 of led3 op te lichten. Om dit te testen schrijf je ook een functie
"printPuzzle" die eveneens de array en een lengte meekrijgt. In deze functie
print je de array naar de Serial Monitor (tussen [], voorbeeld: [1 2 2 1 0 2 0 1
2 1 ]) Test uit!

Opgave 4: Afspelen van de puzzle
  Schrijf nu een functie "playPuzzle" die een array van getallen afspeelt op de
ledjes. De functie krijgt een array van uint8_t en het aantal mee als parameter
en licht de overeenkomstige ledjes op (met een korte delay, gebruik hiervoor een
#define DELAY, zodat je dat makkelijk kan instellen) Maak uiteraard gebruik van
je zelf geschreven led.h library!

Opgave 5: Uitlezen van de input van de gebruiker
  Schrijf een functie "readInput", die eveneens de array en zijn lengte
meekrijgt. De functie geeft een getal terug: 0 om aante geven dat de gebruiker
een fout maakte, 1 als de gebruiker de hele reeks juist heeft ingegeven. Je kan
hier gebruik maken van een oneindige lus waarin je telkens controleert wat de
gebruiker ingaf, je hoeft dus geen interrupts te gebruiken.

Opgave 6: Het volledige spel
  Combineer nu de uitgewerkte functies tot een werkend spel, zie het voorbeeld
boven. Zorg voor feedback in de Serial Monitor!
*/

int main() { 
  
  return 0;

}
