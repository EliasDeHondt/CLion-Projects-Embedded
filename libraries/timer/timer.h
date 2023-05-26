/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

// Enable
void enableTimer2(); // Compare interrupt enable. (TIMSK2 = 00000010). (OCIE2A = 1). (OCIE2B = 0).

// Start
void startTimer2(); // Schalingsfactor = 256. (TCCR2B = 00000110). (CS22 = 1). (CS21 = 1). (CS20 = 0).

// Stop
void stopTimer2(); // Schalingsfactor = 0. (TCCR2B = 00000000). (CS22 = 0). (CS21 = 0). (CS20 = 0).