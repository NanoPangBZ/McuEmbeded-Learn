#include "stm32f1xx.h"
#include "elog.h"
#include "FreeRTOS.h"
#include "task.h"


void test_task( void* param )
{
    while(1)
    {
        elog_i( "task" , " test task ");
        elog_flush();
        vTaskDelay( 1000 / portTICK_PERIOD_MS );
    }
}

extern "C" int user_main()
{
    elog_init();
    elog_start();

    TaskHandle_t a;
    xTaskCreate(
        test_task , 
        "test",
        1024,
        NULL,
        1 , 
        &a
    );

    vTaskStartScheduler();

    while(1);

    return 0;
}
