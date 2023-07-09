/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>
#include <string.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    for( uint8_t temp = 0 ;temp < 5 ; temp++ )
    {
        elog_set_fmt( temp , ELOG_FMT_LVL | ELOG_FMT_TAG | ELOG_FMT_TIME);
    }

    /* add your code here */
    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void) {

    /* add your code here */

}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size)
{
    static uint8_t usart1_dma_buff[64];
    while( HAL_UART_GetState( &huart1 ) != HAL_UART_STATE_READY );
    memcpy( usart1_dma_buff , log , 64 );
    while( HAL_UART_Transmit_DMA( &huart1 , usart1_dma_buff , size ) == HAL_BUSY );
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
    
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
    
}

/**
 * get current time interface
 *
 * @return current time
 */
char time_stamp_string[13];
const char *elog_port_get_time(void) {
    if( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING )
    {
        sprintf( time_stamp_string , "%08ld" , xTaskGetTickCount() );
    }else
    {
        sprintf( time_stamp_string , "%s" , "none time" );
    }
    return time_stamp_string;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    // return " ";
    return NULL;
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    
    /* add your code here */
    // if( taskSCHEDULER_RUNNING == xTaskGetSchedulerState() )
    //     return pcTaskGetName( NULL );
    // else
    //     return "bare";
    return NULL;
}