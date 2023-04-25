/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 25/04/2023
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Enable
void enableButton(int button) {
  if (button < 0 || button > 2) { return; } // 0, 1 of 2 (3 button)

  DDRC &= ~(1 << button);
  PORTC |= (1 << button);
}

// Pushed
void enableAllButtons() { 
  for (int i = 0; i < 3; i++) { enableButton(i); }
}

int buttonPushed(int button) {
  if (button < 0 || button > 2) { return -1; } // 0, 1 of 2 (3 button)

  if ((PINC & (1 << (PC1 + button))) == 0) { return 1; } // (knop ingeduwd)
  else { return 0; }
}

// Released
int buttonReleased(int button) {
  return !buttonPushed(button); // (knop niet ingeduwd)
}

// Enable Interrupt
void enableButtonInterrupt(int button) {
  if (button < 1 || button > 3) { return -1; } // 1, 2 of 3 (3 button)
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << button);
  sei();
}

void enableAllButtonInterrupts() {
  for (int i = 1; i <= 3; i++) { enableButtonInterrupt(i); }
}