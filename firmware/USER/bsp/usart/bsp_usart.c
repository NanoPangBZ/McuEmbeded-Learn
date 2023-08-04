#include "bsp_usart.h"

#include <string.h>
#include "usart.h"

#define USART1_TX_BUFF_SIZE (128)
#define USART1_RX_BUFF_SIZE (128)

static uint8_t usart1_tx_sbuffer[ USART1_TX_BUFF_SIZE ];
static uint8_t usart1_rx_sbuffer[ USART1_RX_BUFF_SIZE ];
static uint16_t usart1_rx_len = 0;

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
            while( (HAL_UART_GetState( &huart1 ) & HAL_UART_STATE_BUSY_TX)  == HAL_UART_STATE_BUSY_TX );
            s_len = len > USART1_TX_BUFF_SIZE ? USART1_TX_BUFF_SIZE : len ;
            memcpy( usart1_tx_sbuffer , data , s_len );
            while( HAL_UART_Transmit_DMA( &huart1 , usart1_tx_sbuffer , s_len ) == HAL_BUSY );
            len -= s_len;
            data += s_len;
        }while( len != 0 );
    }
    else
    {
        while( (HAL_UART_GetState( &huart1 ) & HAL_UART_STATE_BUSY_TX)  == HAL_UART_STATE_BUSY_TX );
        memcpy( usart1_tx_sbuffer , data , len );
        while( HAL_UART_Transmit_DMA( &huart1 , usart1_tx_sbuffer , len ) == HAL_BUSY );
    }
    return BSP_OK;
}

uint16_t  usart_get_rx_len(void)
{
    return usart1_rx_len;
}

uint8_t* usart_get_rx_buf()
{
    return usart1_rx_sbuffer;
}

void usart_clear_rx_buf()
{
    usart1_rx_len = 0;
}

uint8_t usart_push_rx_buf(uint16_t len)
{
    if( len > usart1_rx_len )   len = usart1_rx_len;
    memmove( usart1_rx_sbuffer , usart1_rx_sbuffer + len , usart1_rx_len - len );
    usart1_rx_len -= len;
    return len;
}

bsp_error_e usart_rx_interrupt_enable(void)
{
    HAL_UART_Receive_IT( &huart1 , usart1_rx_sbuffer , 1 );
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if( usart1_rx_len < sizeof(usart1_rx_sbuffer) )
    {
        usart1_rx_len++;
    }
    HAL_UART_Receive_IT( &huart1 , usart1_rx_sbuffer + usart1_rx_len , 1 );
}
