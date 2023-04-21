/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

// Enable
void enableLed(int lednumber);
void enableLeds(uint8_t lednumbers);
void enableAllLeds();

// Up
void lightUpLed(int lednumber);
void lightUpLeds(uint8_t lednumbers);
void lightUpAllLeds();

// UIT
void lightDownLed(int lednumber);
void lightDownLeds(uint8_t lednumbers);
void lightDownAllLeds();

void dimLed(int lednumber, int percentage, int duration);

void fadeInLed(int lednumber, int duration);

void fadeOutLed(int lednumber, int duration);