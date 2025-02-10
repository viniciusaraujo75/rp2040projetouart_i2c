#include "pico/stdlib.h"
#include "leds.h"

#define GREEN_LED 11
#define BLUE_LED 12

void leds_init() {
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_put(GREEN_LED, 0);

    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_put(BLUE_LED, 0);
}

void toggle_green_led() {
    gpio_put(GREEN_LED, !gpio_get(GREEN_LED));
}

void toggle_blue_led() {
    gpio_put(BLUE_LED, !gpio_get(BLUE_LED));
}
