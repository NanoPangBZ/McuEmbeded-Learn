#include "../ssd1306_hal.h"
#include <stdint.h>
#include <stddef.h>

#include "gpio.h"
#include "spi.h"
#include "FreeRTOS.h"
#include "task.h"

#define TAG             "ssd1306"
#define ERR_LOG(...)
#define INFO_LOG(...)

#define OLED_CMD    0
#define OLED_DATA   1

#define CS_LOW()
#define CS_HIGH()
#define DC_LOW()
#define DC_HIGH()
#define RES_LOW()
#define RES_HIGH()

//函数声明
void Init(void*);
void Deint(void*);
void sendCmd(uint8_t*cmd,uint8_t len,void*);
void sendDat(uint8_t*dat,uint16_t len,void*);

//静态内存
static uint8_t buf[1024];

Ssd1306_hal_handle_t oled_spi4_handle = {
    .buf = buf,
    .ctx = NULL,
    .deinit = Deint,
    .init = Init,
    .sendCmd = sendCmd,
    .sendDat = sendDat
};

static void ssd1306_spi_send(const uint8_t*dat,uint16_t len,uint8_t cmd)
{
    CS_LOW();
    
    CS_HIGH();
}

static void ssd1306_delay(uint16_t ms){
    if( xTaskGetSchedulerState() == taskSCHEDULER_RUNNING )
    {
        vTaskDelay( ms / portTICK_PERIOD_MS );
    }else{
        HAL_Delay(ms);
    }
}

void Init(void*ctx){
    CS_HIGH();
    RES_LOW();
    ssd1306_delay(300);
    RES_HIGH();
}

void Deint(void*ctx){
    (void)ctx;
}

void sendCmd(uint8_t* cmd,uint8_t len,void* ctx){
    ssd1306_spi_send(cmd,len,OLED_CMD);
}

void sendDat(uint8_t* dat,uint16_t len,void* ctx){
    ssd1306_spi_send(dat,len,OLED_DATA);
}

