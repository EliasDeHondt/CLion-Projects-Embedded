/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 09/05/2023
 */

// Enable
void enableTimer1(); // Compare interrupt enable. (TIMSK1 = 00000010). (OCIE1A = 1). (OCIE1B = 0).

void enableTimer2(); // Compare interrupt enable. (TIMSK2 = 00000010). (OCIE2A = 1). (OCIE2B = 0).

// Start
void startTimer1(); // Schalingsfactor = 1024. (TCCR1B = 00000101). (CS12 = 1). (CS11 = 0). (CS10 = 1).

void startTimer2(); // Schalingsfactor = 256. (TCCR2B = 00000110). (CS22 = 1). (CS21 = 1). (CS20 = 0).

// Stop
void stopTimer1(); // Schalingsfactor = 0. (TCCR1B = 00000000). (CS12 = 0). (CS11 = 0). (CS10 = 0).

void stopTimer2(); // Schalingsfactor = 0. (TCCR2B = 00000000). (CS22 = 0). (CS21 = 0). (CS20 = 0).

// Reset
void resetTimer1(); // Reset timer. (TCNT1 = 0). (TCCR1B = 00000000).

void resetTimer2(); // Reset timer. (TCNT2 = 0). (TCCR2B = 00000000).