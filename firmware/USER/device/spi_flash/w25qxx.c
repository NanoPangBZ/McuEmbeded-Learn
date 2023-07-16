#include "w25qxx.h"
#include "w25qxx_cmd.h"

/**************************************移植接口***********************************************/

#define SPI_WRITE_READ(buf,len)     spi_write_read(buf,len)
#define CS_HIGH()                   (GPIOB->ODR |= GPIO_PIN_12)
#define CS_LOW()                    (GPIOB->ODR &= ~GPIO_PIN_12)
#define DELAY( ms )                 delay_wrape(ms)
#define TAG                         //"w25qxx"
#define INFO_LOG(...)               //elog_i( TAG ,  __VA_ARGS__ )
#define ERROR_LOG(...)              //elog_i( TAG ,  __VA_ARGS__ )

/**************************************移植实现***********************************************/
#include "stm32f1xx.h"
#include "bsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "elog.h"

static inline void delay_wrape( uint16_t ms )
{
    if( xTaskGetSchedulerState() != taskSCHEDULER_RUNNING )
    {
        HAL_Delay( ms );
    }else
    {
        vTaskDelay( ms / portTICK_PERIOD_MS );
    }
}

/*********************************************************************************************/

static inline void _wait_busy( uint16_t cycle )
{
    while( w25qxx_read_status_regsiter1() & REG1_BUSY_MASK )
    {
        DELAY( cycle );
    }
}

uint16_t w25qxx_get_id( void )
{
    uint8_t buf[6];
    uint16_t id;
    buf[0] = JEDEC_ID_CMD;
    buf[3] = 0;
    CS_LOW();
    SPI_WRITE_READ( buf , 6 );
    CS_HIGH();
    id = buf[2];
    id <<= 8;
    id |= buf[3];
    INFO_LOG( "get jedec id: 0x%04X" , id );
    return id;
}

uint8_t w25qxx_read_status_regsiter1()
{
    uint8_t buf[2];
    buf[0] =  READ_STATUS_REG1_CMD;
    CS_LOW();
    SPI_WRITE_READ( buf , 2 );
    CS_HIGH();
    INFO_LOG( "read status reg1 : 0x%02X" , buf[1] );
    return buf[1];
}

uint8_t w25qxx_write_enable(void)
{
    uint8_t buf[1];
    _wait_busy( 20 );
    buf[0] = WRITE_ENABLE_CMD;
    CS_LOW();
    SPI_WRITE_READ( buf , 1 );
    CS_HIGH();
    _wait_busy( 20 );
    INFO_LOG( "write enable" );
    return 0;
}

uint8_t w25qxx_write_disable(void)
{
    uint8_t buf[1];
    _wait_busy( 10 );
    buf[0] = WRITE_DISABLE_CMD;
    CS_LOW();
    SPI_WRITE_READ( buf , 1 );
    CS_HIGH();
    _wait_busy( 10 );
    INFO_LOG( "write disable" );
    return 0;
}

uint8_t w25qxx_erase_4k_sector( uint32_t addr )
{
    uint8_t buf[4];
    //计算扇区起始地址
    addr &= ~(0xFFF);
    addr &= 0x00FFFFFF;
    //准备指令
    buf[0] = ERASE_4K_SECTOR_CMD;
    buf[1] = (addr & 0xFF0000) >> 16;
    buf[2] = (addr & 0x00FF00) >> 8;
    buf[3] = (addr & 0x0000FF);

    //等待上一条指令结束
    _wait_busy( 10 );

    //使能写入
    w25qxx_write_enable();

    //开始擦除
    CS_LOW();
    INFO_LOG( "ready erase sector , sector start addr : 0x%08X" , addr );
    SPI_WRITE_READ( buf , 4 );
    CS_HIGH();

    //失能写入
    w25qxx_write_disable();
    return 0;
}

uint8_t w25qxx_erase_32k_block( uint32_t addr )
{
    return 0;
}

uint8_t w25qxx_erase_64k_block( uint32_t addr )
{
    return 0;
}

uint8_t w25qxx_erase_all_chip()
{
    return 0;
}

uint8_t w25qxx_program_page( uint32_t addr , uint8_t* data , uint16_t len )
{
    uint8_t buf[4];
    buf[0] = PAGE_PROGRAM_CMD;
    buf[1] = (addr & 0xFF0000) >> 16;
    buf[2] = (addr & 0x00FF00) >> 8;
    buf[3] = (addr & 0x0000FF);
    _wait_busy( 10 );

    w25qxx_write_enable();

    CS_LOW();
    SPI_WRITE_READ( buf , 4 );
    SPI_WRITE_READ( data , len );
    CS_HIGH();
    
    w25qxx_write_disable();

    return 0;
}

uint8_t w25qxx_program( uint32_t addr , uint8_t* data , uint16_t len )
{
    return 0;
}

uint8_t w25qxx_read( uint32_t addr , uint8_t* r_buf , uint16_t len )
{
    uint8_t buf[4];
    buf[0] = READ_DATA_CMD;
    buf[1] = (addr & 0xFF0000) >> 16;
    buf[2] = (addr & 0x00FF00) >> 8;
    buf[3] = (addr & 0x0000FF);
    _wait_busy( 10 );

    CS_LOW();

    SPI_WRITE_READ( buf , 4 );
    SPI_WRITE_READ( r_buf , len );

    CS_HIGH();

    return 0;
}

uint8_t w25qxx_test( void )
{
    uint8_t buf[64];
    w25qxx_get_id();

    w25qxx_write_enable();
    w25qxx_read_status_regsiter1();
    w25qxx_write_disable();   
    w25qxx_read_status_regsiter1();

    w25qxx_erase_4k_sector( 0x00FFFF );
    w25qxx_read( 0x00F000 , buf , 64 );
    for( uint8_t temp = 0 ; temp < 64 ; temp++ )
    {
        if( buf[temp] != 0xff )
        {
            ERROR_LOG( "erase error , index : 0x%02X , value : 0x%02X" , temp , buf[temp] );
            return 1;
        }
    }

    for( uint8_t temp = 0 ; temp < 64 ; temp++ )
    {
        buf[temp] = temp;
    }

    w25qxx_program_page( 0x00F007 , buf , 64 );

    for( uint8_t temp = 0 ; temp < 64 ; temp++ )
    {
        buf[temp] = 0;
    }

    w25qxx_read(  0x00F007 , buf , 64 );

    for( uint8_t temp = 0 ; temp < 64 ; temp++ )
    {
        if( buf[temp] != temp )
        {
            ERROR_LOG( "program error , index : 0x%02X , value : 0x%02X" , temp , buf[temp] );
            return 1;
        }
    }

    return 0;
}
