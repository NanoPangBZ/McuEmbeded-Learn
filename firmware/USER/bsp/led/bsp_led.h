#pragma once

#include <stdint.h>

typedef enum
{
    BOARD_LED0 = 0,
    BOARD_LED1 = 1
}bsp_led_e;

void led_on( bsp_led_e  led);
void led_off( bsp_led_e led);

