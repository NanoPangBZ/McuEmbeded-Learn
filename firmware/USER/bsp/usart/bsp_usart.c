#include "bsp_usart.h"

#include <string.h>
#include "usart.h"

#define USART1_TX_BUFF_SIZE (128)
#define USART1_RX_BUFF_SIZE (128)

static uint8_t usart1_tx_sbuffer[ USART1_TX_BUFF_SIZE ];

bsp_error_e usart_send_sync( uint8_t* data , uint16_t len )
{
    while( HAL_UART_GetState( &huart1 ) != HAL_UART_STATE_READY );
    HAL_UART_Transmit( &huart1 , data , len , 100 );
    return BSP_OK;
}

bsp_error_e usart_send_asyn( uint8_t* data , uint16_t len )
{
    if( len > USART1_TX_BUFF_SIZE )
    {
        uint16_t s_len;
        do{
            while( HAL_UART_GetState( &huart1 ) != HAL_UART_STATE_READY );
            s_len = len > USART1_TX_BUFF_SIZE ? USART1_TX_BUFF_SIZE : len ;
            memcpy( usart1_tx_sbuffer , data , s_len );
            while( HAL_UART_Transmit_DMA( &huart1 , usart1_tx_sbuffer , s_len ) == HAL_BUSY );
            len -= s_len;
            data += s_len;
        }while( len != 0 );
    }
    else
    {
        while( HAL_UART_GetState( &huart1 ) != HAL_UART_STATE_READY );
        memcpy( usart1_tx_sbuffer , data , len );
        while( HAL_UART_Transmit_DMA( &huart1 , usart1_tx_sbuffer , len ) == HAL_BUSY );
    }
    return BSP_OK;
}

bsp_error_e usart_recive_sync( uint8_t*buf , uint16_t len )
{
    return HAL_UART_Receive( &huart1 , buf , len , 100) == HAL_OK ? BSP_OK : BSP_TIMEOUT ;
}
