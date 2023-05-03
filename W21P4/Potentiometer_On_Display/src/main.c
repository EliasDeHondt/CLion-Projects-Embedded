/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <display.h>
#include <util/delay.h>
#include <usart.h>
#include <string.h>
#include <potentio.h>

/*
Deze oefening combineert het gebruik van de display library  en de ADC.

Opgave 1:
  Lees de waarde van de potentiometer uit en toont deze op de display. 
  Maak net zoals in de demo gebruik van de 5V als referentiewaarde. 

Opgave 2:
  Pas de oefening aan: maak nu gebruik van 2.5V als referentiewaarde. 
  Zoek op hoe je dit doet in het artikel onderaan de tutorial rond Analog To Digital Conversie:
    https://canvas.kdg.be/courses/38313/pages/1-analoog-digitaal-conversie

Opgave 3:
  Aangezien de knoppen aangesloten zijn op PC1, PC2 en PC3, kan je de input van de knoppen ook door de ADC laten gaan. 
  Probeer dat eens door de ADMUX aan te passen en bestudeer het (vrij zinloze!) resultaat...
*/

void opgave1() { // Opgave 1:
  enablePotentio();
  while (1) {
    uint16_t value = readPotentio(); 
    writeNumberAndWait(value, 1000); // 0 ... 1023
    printf("Potentiometer waarde: %d\n", value);
  }
}

void opgave2() { // Opgave 2:
  ADMUX |= (1 << REFS1); // Set reference voltage to 2.5V
  ADMUX &= ~(1 << REFS0); // Set AREF as reference voltage

  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN);

  while (1) {
    uint16_t value = readPotentio(); 
    writeNumberAndWait(value, 1000); // 0 ... 1023
    printf("Potentiometer waarde: %d\n", value);
  }
}

void opgave3() { // Opgave 3:
  ADMUX |= (1 << REFS1); // Set reference voltage to 2.5V
  ADMUX &= ~(1 << REFS0); // Set AREF as reference voltage

  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN);

  while (1) {
    for (uint8_t i = 1; i <= 3; i++) { // Read ADC input for each button
      ADMUX &= 0xF0; // Clear ADC input selection
      ADMUX |= i; // Select ADC input (1, 2, or 3)
      ADCSRA |= (1 << ADSC); // Start ADC conversion
      while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
      uint16_t value = ADC; // Read ADC result
      printf("Button %d ADC value: %d\n", i, value);
      writeNumberAndWait(value, 1000);
    }
  }
}

int main() {
  initUSART();
  initDisplay();
  //opgave1();
  //opgave2();
  opgave3();
  return 0;
}
