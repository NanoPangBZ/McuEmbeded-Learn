#pragma once

#include <stdint.h>
#include "bsp.h"

//向外声明bsp的功能全部由C函数实现
#ifdef __cplusplus
extern "C"{
#endif

/* 异步发送 */
bsp_error_e usart_send_asyn( uint8_t* data , uint16_t len );
/* 同步发送 */
bsp_error_e usart_send_sync( uint8_t* data , uint16_t len );

/* 开启异步接收 */
bsp_error_e usart_rx_interrupt_enable(void);

uint16_t  usart_get_rx_len(void);
uint8_t* usart_get_rx_buf();
void usart_clear_rx_buf();
uint8_t usart_push_rx_buf(uint16_t len);

#ifdef __cplusplus
}
#endif
