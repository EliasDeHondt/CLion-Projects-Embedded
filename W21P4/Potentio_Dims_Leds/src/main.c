/**
 * @author Elias De Hondt
 * @see https://eliasdh.com
 * @since 02/05/2023
 */

#include <avr/io.h>
#include <led.h>
#include <potentio.h>
#include <usart.h>
#include <util/delay.h>

int main() {
  initUSART();
  enableLed(0);
  lightDownLed(0);
  enablePotentio();

  while (1) {
    uint16_t value = readPotentio(); // 0 ... 1023
    int percentage = value % 101; // 0 ... 100
    dimLed(0, percentage, 10);
    printf("%d\n", percentage);
  }
  return 0;
}
