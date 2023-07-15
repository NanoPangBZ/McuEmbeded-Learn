#include "stm32f1xx.h"
#include "elog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "function_section.h"
#include "gpio.h"

void test_task( void* param )
{
    elog_i( "prt" , "test task enter");
    while(1)
    {
        elog_i( "test" , "test task send out");
        elog_flush();
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
    elog_i( "prt" , "test task enter");
}
static void sys_tick_led_task( void* param )
{
    elog_i( "prt" , "sys led tick task enter");
    while(1)
    {
        GPIOB->ODR |= GPIO_PIN_5;
        vTaskDelay( 200 / portTICK_PERIOD_MS );
        GPIOB->ODR &= ~GPIO_PIN_5;
        vTaskDelay( 200 / portTICK_PERIOD_MS );
    }
    elog_i( "prt" , "led tick task exit");
}

extern "C" int main()
{
    elog_init();
    elog_start();

    elog_i( "system" , "hardware set up!" );
    elog_flush();

    xTaskCreate(
        test_task , 
        "test",
        1024,
        NULL,
        2 , 
        NULL
    );

    xTaskCreate(
        sys_tick_led_task , 
        "sys led",
        256,
        NULL,
        1 , 
        NULL
    );

    vTaskStartScheduler();

    while(1);

    return 0;
}

extern "C" int test( void* args , ... )
{
    return 0;
}

REGISTER_FUNCTION(test);
