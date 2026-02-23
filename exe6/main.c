#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"

#define FIRST_GPIO 2
#define BTN_PIN_G 28

static const int bits[10] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66,
    0x6d, 0x7d, 0x07, 0x7f, 0x67
};

void seven_seg_init(void) {
    for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
    }
    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);
}

void seven_seg_display(int value) {
    for (int i = 0; i < 7; i++) {
        int gpio = FIRST_GPIO + i;
        int bit = (bits[value] >> i) & 1;
        gpio_put(gpio, bit);
    }
}

int main(void) {
    stdio_init_all();
    
    seven_seg_init();
    seven_seg_display(0);
    
    int cnt = 0;
    int last_btn = 1;
    
    while (true) {
        int btn = gpio_get(BTN_PIN_G);
        if (last_btn && !btn) {
            cnt = (cnt + 1) % 10;
            seven_seg_display(cnt);
            printf("cnt: %d\n", cnt);
        }
        last_btn = btn;
        sleep_ms(10);
    }
}
