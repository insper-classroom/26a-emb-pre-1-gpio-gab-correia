#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN  = 28;
const int LED1 = 5;   
const int LED2 = 8;   
const int LED3 = 11;  
const int LED4 = 15;

void init_pin(int pin, int dir) {
    gpio_init(pin);
    gpio_set_dir(pin, dir);
    if (dir == GPIO_IN) gpio_pull_up(pin);
}

int main() {
  stdio_init_all();

  init_pin(BTN,  GPIO_IN);
  init_pin(LED1, GPIO_OUT);
  init_pin(LED2, GPIO_OUT);
  init_pin(LED3, GPIO_OUT);
  init_pin(LED4, GPIO_OUT);

  while (true) {

    if (!gpio_get(BTN)) {
      while (!gpio_get(BTN));  

      gpio_put(LED1, 1);
      sleep_ms(300);
      gpio_put(LED1, 0);

      gpio_put(LED2, 1);
      sleep_ms(300);
      gpio_put(LED2, 0);

      gpio_put(LED3, 1);
      sleep_ms(300);
      gpio_put(LED3, 0);

      gpio_put(LED4, 1);
      sleep_ms(300);
      gpio_put(LED4, 0);
    }
  }
}