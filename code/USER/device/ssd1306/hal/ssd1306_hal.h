#ifndef _oled12864_hal_h
#define _oled12864_hal_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct{
    void *ctx;
    void (*init)(void*);
    void (*deinit)(void*);
    void (*sendCmd)(uint8_t* cmd,uint8_t len,void*);
    void (*sendDat)(uint8_t* dat,uint16_t len,void*);
    unsigned char *buf;
}Ssd1306_hal_handle_t;

extern Ssd1306_hal_handle_t oled_spi4_handle;

#ifdef __cplusplus
}
#endif

#endif  //_oled12864_hel_h


