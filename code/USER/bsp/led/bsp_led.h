#pragma once

#include <stdint.h>

//向外声明bsp的功能全部由C函数实现
#ifdef __cplusplus
extern "C"{
#endif

typedef enum
{
    BOARD_LED0 = 0,
    BOARD_LED1 = 1
}bsp_led_e;

void led_on( bsp_led_e  led);
void led_off( bsp_led_e led);


#ifdef __cplusplus
}
#endif
