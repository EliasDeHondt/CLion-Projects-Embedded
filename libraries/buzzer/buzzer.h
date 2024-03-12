/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <stdlib.h>
#include <avr/io.h>

// FREQUENCIES VAN DE VERSCHILLENDE NOTEN
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.000
#define B5 987.770
#define C6 1046.500

// UIT
void buzzerOff();

// IN
void buzzerOn();

// Enable
void enableBuzzer();

void playTone(float frequency, uint32_t duration);

void positiveTone();
void negativeTone();
void startTone();
void Elise(); // Für Elise