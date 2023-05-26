/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

// Enable
void enablePotentio(); // Interne referentie spanning van 5V gebruiken en schalingsfactor van 128 gebruiken (16MHz / 128 = 125kHz) en enable de ADC

// Read
uint16_t readPotentio(); // Start een conversie met de ADC. ADC is een converteerd een analoog signaal naar een digitaal signaal