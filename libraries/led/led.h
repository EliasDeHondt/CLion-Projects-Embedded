#include <util/delay.h>
#include <avr/io.h>

void enableLed(int lednumber);

void enableLeds(uint8_t lednumbers);

void enableAllLeds();

void lightUpLed(int lednumber);

void lightUpLeds(uint8_t lednumbers);

void lightUpAllLeds();

void lightDownLed(int lednumber);

void lightDownLeds(uint8_t lednumbers);

void lightDownAllLeds();