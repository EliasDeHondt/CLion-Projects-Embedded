/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <usart.h>
#include <led.h>
#include <button.h>
#include <display.h>
#include <buzzer.h>
#include <timer.h>

#define VEELVOUD 250
#define MAXFUEL 1500
#define NUMBER_OF_LEDS 4

typedef struct {
  float distance;
  int currentSpeed;
  uint8_t burst;
  uint16_t fuelReserve;
} TIMESTAMP;

TIMESTAMP* timestamps;
int counter = 0;
int seconds = 0;

// Startsituatie:
int currentSpeed = 100;  //  snelheid - m/s  (meter per seconde)
double gravity = 1.622;     // versnelling – m/s²
float distance = 9999;     // afstand tot het maanoppervlak in meter – m
uint16_t fuelReserve = 1500;  // liter (brandstof * 4 = fuelReserve)
uint8_t burst = 0;            // Burst heeft een waarde tussen 0 en 50

void printlogboek() {
    for (int i = 0; i < 50; i++) {
        printf("Op seconden: %d\n", (i + 1));
        printf("Distance: %f\nCurrentSpeed: %d\n", timestamps[i].distance, timestamps[i].currentSpeed);
        printf("Burst: %d\nFuelReserve: %d\n", timestamps[i].burst, timestamps[i].fuelReserve);
    }
}

void landt() {
    stopTimer2();
    lightDownAllLeds();
    positiveTone();
    printString("Gefeliciteerd, je bent geland op de maan.\n");
    printlogboek();
    ledLus();
}

void crash() {
    stopTimer2();
    lightDownAllLeds();
    negativeTone();
    printString("Je bent gecrasht op de maan, helaas.\n");
    printlogboek();
    ledLus();
}

// Deze ISR loopt elke 4ms.
ISR(TIMER2_COMPA_vect) { // Timer interrupt.
    counter++; // Verhoog counter met 1.
    // Als counter + 1 deelbaar is door VEELVOUD tel één seconde.
    if (counter % VEELVOUD == 0) { // Nieuwe situatie: (Wordt elke seconde uitgevoerd).
        currentSpeed +=  gravity - burst / 5;
        distance -= currentSpeed;
        fuelReserve -= burst;
        
        if (fuelReserve < (MAXFUEL/8)) negativeTone(); // Brandstof is bijna op.
        if (distance <= 3 && currentSpeed <= 5) landt(); // Gewonnen.
        if (distance <= 0) crash(); // Verloren.
        timestamps[seconds].distance = distance;
        timestamps[seconds].currentSpeed = currentSpeed;
        timestamps[seconds].burst = burst;
        timestamps[seconds].fuelReserve = fuelReserve;
        burst = 0;
        printf("%d\n", seconds);
        seconds++;
    }
}

ISR(PCINT1_vect) { // Button interrupt.
    int timestamp = counter;
    while (buttonPushed(1) && timestamp == counter) {
        if (burst < 50) {
            burst++;
            writeNumberAndWait(distance, 20); // Unnecessary, but it looks a bit better this way :-°)
        }
    }
}

void showDashboard() { // Runs every second.
    writeNumberAndWait(distance, 500); // Write the distance to the display.
    // Calculate the number of lit LED lights based on the fuel reserve.
    int numLedsLit = fuelReserve / (MAXFUEL / NUMBER_OF_LEDS);
    // Light up the corresponding LED lights.
    for (int i = 0; i < numLedsLit; i++) lightUpLed(i);
    // Check if the next LED light should be flashing.
    if (fuelReserve % (MAXFUEL / NUMBER_OF_LEDS) > 0) {
        flashLed(numLedsLit, 100);
        writeNumberAndWait(distance, 500); // Unnecessary, but it looks a bit better this way :-°)
    }
    // Turn off the remaining LED lights.
    for (int i = numLedsLit; i < NUMBER_OF_LEDS; i++) lightDownLed(i);
}

int main() {
    initUSART();
    enableAllLeds();
    lightUpAllLeds();
    initDisplay();
    enableBuzzer();
    enableButton(1);
    enableButtonInterrupt(1);
    enableTimer2();
    startTimer2();

    timestamps = calloc(75, sizeof(TIMESTAMP));

    while (1) {
        showDashboard();
    }
    return 0;
}