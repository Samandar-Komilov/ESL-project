#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"
#include "manage_leds.c"

#define ID_LEN 4
#define BUTTON_PRESSED   nrf_gpio_pin_read(BUTTON_PIN) == 0

const uint8_t id[ID_LEN] = {7,2,1,2};

// Setup
void main_setup(void){
    bsp_board_init(BSP_INIT_LEDS);

    nrf_gpio_cfg_output(LED_R);
    nrf_gpio_cfg_output(LED_G);
    nrf_gpio_cfg_output(LED_B);
    nrf_gpio_cfg_output(LED_Y);
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    main_setup();
    uint8_t idx = 0;
    uint8_t digit = id[idx];

    while (1){
        if (BUTTON_PRESSED){
            toggle_led(idx);
            digit--;
            if (digit == 0){
                idx++;
                idx = idx % ID_LEN;
                digit = id[idx];
            }
        }
    }
}

/**
 *@}
 **/