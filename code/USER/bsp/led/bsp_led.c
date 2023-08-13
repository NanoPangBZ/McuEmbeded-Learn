#include "bsp_led.h"
#include "gpio.h"

typedef struct{
    GPIO_TypeDef*   GPIO;
    uint16_t        pin;
    uint8_t         on_level;
}s_bsp_led_t;

const s_bsp_led_t led_list[] = {
    { GPIOB , GPIO_PIN_5 , 0 },
    { GPIOE , GPIO_PIN_5 , 0 }
};

void led_on( bsp_led_e  led)
{
    if( led_list[led].on_level )
    {
        led_list[ led ].GPIO->ODR |= led_list[ led ].pin;
    }else
    {
        led_list[ led ].GPIO->ODR &= ~(led_list[ led ].pin);
    }
}

void led_off( bsp_led_e led)
{
    if( led_list[led].on_level )
    {
        led_list[ led ].GPIO->ODR &= ~(led_list[ led ].pin);
    }else
    {
        led_list[ led ].GPIO->ODR |= led_list[ led ].pin;
    }
}