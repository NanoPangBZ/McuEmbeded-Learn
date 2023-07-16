#pragma once

//向外声明bsp的功能全部由C函数实现
#ifdef __cplusplus
extern "C"{
#endif

typedef enum 
{
    BSP_UNDEFINE = 1,
    BSP_OK = 0,
    BSP_ERR = -1,
    BSP_BUSY = -2,
    BSP_TIMEOUT = -3
}bsp_error_e;

#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./spi/bsp_spi.h"

#ifdef __cplusplus
}
#endif
