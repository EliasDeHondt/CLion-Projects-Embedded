/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 01/05/2023
 */

#include <avr/io.h>

#define LOW 0
#define HIGH 1
/* Define shift register pins used for seven segment display */
#define LATCH_DIO PD4
#define CLK_DIO PD7
#define DATA_DIO PB0

#define LSBFIRST 0
#define MSBFIRST 1
#define NUMBER_OF_SEGMENTS 8

#define sbi(register, bit) (register |= _BV(bit))
#define cbi(register, bit) (register &= ~_BV(bit))

#define DELAYE _delay_ms(100);

void initDisplay();
void writeNumberToSegment(uint8_t segment, uint8_t value);
void writeNumber(int number);
void writeNumberAndWait(int number, int delay);

void writeCharToSegment(uint8_t segment, char character);
void writeString(char* str);
void writeStringAndWait(char* str, int delay);

void scrollingString(char* str, int delay);

void writeToSegment(uint8_t segment, uint8_t value);
void ledLus();
void displayOff();