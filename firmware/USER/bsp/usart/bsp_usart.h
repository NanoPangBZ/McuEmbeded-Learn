#pragma once

#include <stdint.h>
#include "bsp.h"

//向外声明bsp的功能全部由C函数实现
#ifdef __cplusplus
extern "C"{
#endif


bsp_error_e usart_send_asyn( uint8_t* data , uint16_t len );
bsp_error_e usart_send_sync( uint8_t* data , uint16_t len );

bsp_error_e usart_recive_sync( uint8_t*buf , uint16_t len );

bsp_error_e usart_recive(  );

#ifdef __cplusplus
}
#endif
