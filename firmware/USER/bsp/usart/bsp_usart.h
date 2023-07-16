#pragma once

#include <stdint.h>
#include "bsp.h"

bsp_error_e usart_send_asyn( uint8_t* data , uint16_t len );
bsp_error_e usart_send_sync( uint8_t* data , uint16_t len );

bsp_error_e usart_recive_sync( uint8_t*buf , uint16_t len );

bsp_error_e usart_recive(  );
