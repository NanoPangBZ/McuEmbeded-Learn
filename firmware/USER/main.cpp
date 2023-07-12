#include "stm32f1xx.h"
#include "elog.h"
#include "FreeRTOS.h"
#include "task.h"

void test_task( void* param )
{
    while(1)
    {
        elog_i( "test" , " test task ");
        elog_flush();
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}

extern "C" int user_main()
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
        1 , 
        NULL
    );

    vTaskStartScheduler();

    while(1);

    return 0;
}
