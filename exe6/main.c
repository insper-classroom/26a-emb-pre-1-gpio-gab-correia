#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


const int SEG[] = {2, 3, 4, 5, 6, 7, 8};
const int BTN = 28;


const int digits[10][7] = {
    {1,1,1,1,1,1,0}, 
    {0,1,1,0,0,0,0}, 
    {1,1,0,1,1,0,1}, 
    {1,1,1,1,0,0,1}, 
    {0,1,1,0,0,1,1}, 
    {1,0,1,1,0,1,1}, 
    {1,0,1,1,1,1,1}, 
    {1,1,1,0,0,0,0}, 
    {1,1,1,1,1,1,1}, 
    {1,1,1,1,0,1,1}, 
};

void show_digit(int n) {
    for (int i = 0; i < 7; i++) {
        gpio_put(SEG[i], digits[n][i]);
    }
}

int main() {
    stdio_init_all();

 
    for (int i = 0; i < 7; i++) {
        gpio_init(SEG[i]);
        gpio_set_dir(SEG[i], GPIO_OUT);
    }

    
    gpio_init(BTN);
    gpio_set_dir(BTN, GPIO_IN);
    gpio_pull_up(BTN);

    int cnt = 0;
    show_digit(0);  
    sleep_ms(500);

    while (true) {
        if (!gpio_get(BTN)) {
            sleep_ms(20);                
            if (!gpio_get(BTN)) {
                cnt = (cnt + 1) % 10;  
                show_digit(cnt);
                while (!gpio_get(BTN)); 
                sleep_ms(20);
            }
        }
    }
}
