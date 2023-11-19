#include <stdint.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"

#define LED_COUNT 4
#define BUTTON_PIN NRF_GPIO_PIN_MAP(1, 6)
#define LED_R NRF_GPIO_PIN_MAP(0, 8)
#define LED_G NRF_GPIO_PIN_MAP(1,9)
#define LED_B NRF_GPIO_PIN_MAP(0,12)
#define LED_Y NRF_GPIO_PIN_MAP(0,6)
#define DELAY 500

const uint8_t led_sequence[LED_COUNT] = {LED_R, LED_G, LED_B, LED_Y};

void turn_on_led(int idx){
    nrf_gpio_pin_write(led_sequence[idx], 0);
    nrf_delay_ms(DELAY);
}

void turn_off_led(int idx){
    nrf_gpio_pin_write(led_sequence[idx], 1);
    nrf_delay_ms(DELAY);
}

void toggle_led(int idx){
    turn_on_led(idx);
    turn_off_led(idx);
}