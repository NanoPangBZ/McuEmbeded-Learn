#include "bsp_usart.h"

#include <string.h>
#include "usart.h"

#define USART1_TX_BUFF_SIZE (128)

static uint8_t usart1_tx_sbuffer[ USART1_TX_BUFF_SIZE ];

void usart_send( uint8_t* data , uint16_t len )
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
}
