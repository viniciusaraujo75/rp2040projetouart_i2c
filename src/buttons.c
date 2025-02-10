#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "buttons.h"
#include "leds.h"

#define BUTTON_A 5
#define BUTTON_B 6

volatile bool button_a_pressed = false;
volatile bool button_b_pressed = false;

void button_a_callback(uint gpio, uint32_t events) {
    button_a_pressed = true;
}

void button_b_callback(uint gpio, uint32_t events) {
    button_b_pressed = true;
}

void buttons_init() {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_a_callback);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_b_callback);
}
