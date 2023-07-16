#include "spi.h"

void spi_write_read( uint8_t* buf , uint16_t len )
{
    HAL_SPI_TransmitReceive( &hspi2 , buf , buf , len , 100 );
}
