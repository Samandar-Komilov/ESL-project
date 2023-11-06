/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"

#define LED_COUNT 3
#define BUTTON_PIN NRF_GPIO_PIN_MAP(1, 6)
#define LED_R NRF_GPIO_PIN_MAP(0, 8)
#define LED_G NRF_GPIO_PIN_MAP(1,9)
#define LED_B NRF_GPIO_PIN_MAP(0,12)

const uint32_t led_sequence[LED_COUNT] = {LED_R, LED_G, LED_B};
char sequence[6] = {'R', 'R', 'G', 'G', 'G', 'B'};

// Converts the characters from the sequence into LED indexes
uint8_t hash_led(int c){
    if (c == 'R') return 0;
    else if (c == 'G') return 1;
    else if (c == 'B') return 2;
    else return 0;
}

// Plays the given sequence
void play(uint8_t idx){
    nrf_gpio_pin_write(led_sequence[idx], 0);
    nrf_delay_ms(500);
    nrf_gpio_pin_write(led_sequence[idx], 1);
    nrf_delay_ms(500);
}

// Turns off all leds if user stops pressing the button
void clear_all(){
    nrf_gpio_pin_write(LED_R, 1);
    nrf_gpio_pin_write(LED_G, 1);
    nrf_gpio_pin_write(LED_B, 1);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    bsp_board_init(BSP_INIT_LEDS);

    nrf_gpio_cfg_output(LED_R);
    nrf_gpio_cfg_output(LED_G);
    nrf_gpio_cfg_output(LED_B);
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
    static uint8_t current_led = 0;

    while (1){
        if (nrf_gpio_pin_read(BUTTON_PIN) == 0){
            play(hash_led(sequence[current_led]));
            current_led = (current_led + 1) % 6;
        } else{
            clear_all();
        }
    }
}

/**
 *@}
 **/