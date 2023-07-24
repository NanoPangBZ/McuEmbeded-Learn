#include "stm32f1xx.h"
#include "elog.h"
#include "FreeRTOS.h"
#include "task.h"
#include "function_section.h"
#include "bsp.h"
#include "device.h"
#include <string.h>
#include "ssd1306.h"

static Ssd1306  ssd1306( &oled_spi4_handle );

void test_task( void* param )
{
    elog_i( "prt" , "test task enter");
    elog_i( "prt" , "%s" , ( w25qxx_test() ? "w25qxx error" : "w25qxx pass" ) );
    elog_i( "prt" , "test task exit");
    vTaskDelete( NULL );
}

static void sys_tick_led_task( void* param )
{
    elog_i( "prt" , "sys led tick task enter");
    while(1)
    {
        led_on( BOARD_LED0 );
        vTaskDelay( 50 / portTICK_PERIOD_MS );
        led_off( BOARD_LED0 );
        vTaskDelay( 950 / portTICK_PERIOD_MS );
    }
    elog_i( "prt" , "led tick task exit");
}

static void log_flush_task( void* param )
{
    while(1)
    {
        elog_flush();
        vTaskDelay( 20 / portTICK_PERIOD_MS );
    }
}

extern "C" int main()
{
    elog_init();
    elog_start();

    elog_i( "system" , "hardware set up!" );
    elog_flush();

    ssd1306.drawLine( 0 , 0 , 127 , 63 );
    ssd1306.refresh();

    xTaskCreate(
        test_task , 
        "test",
        1024,
        NULL,
        2 , 
        NULL
    );

    xTaskCreate(
        log_flush_task , 
        "log flush",
        512,
        NULL,
        3 , 
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
