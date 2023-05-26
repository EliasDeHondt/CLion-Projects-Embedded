/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 18/04/2023
 */

// Enable
void enableLed(int lednumber); // Enable de LED
void enableLeds(uint8_t lednumbers); // Enable de LEDs
void enableAllLeds(); // Enable alle LEDs

// Up
void lightUpLed(int lednumber); // Zet de LED aan
void lightUpLeds(uint8_t lednumbers); // Zet de LEDs aan
void lightUpAllLeds(); // Zet alle LEDs aan

// Down
void lightDownLed(int lednumber); // Zet de LED uit
void lightDownLeds(uint8_t lednumbers); // Zet de LEDs uit
void lightDownAllLeds(); // Zet alle LEDs uit

void dimLed(int lednumber, int percentage, int duration); // Dim de LED

void fadeInLed(int lednumber, int duration); // Fade de LED in

void fadeOutLed(int lednumber, int duration); // Fade de LED uit

void flipLed(int lednumber); // Zet de LED aan als hij uit staat en zet de LED uit als hij aan staat

void flashLed(int lednumber, int duration); // Laat de LED knipperen

// Van Elias :-)
void heartbeat(int duration); // Laat de LED knipperen als een hartslag (1x per seconde) voor een bepaalde tijd

void countdown(); // Laat de LED knipperen als een countdown (1x per seconde) voor een bepaalde tijd