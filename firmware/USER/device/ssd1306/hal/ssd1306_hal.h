#ifndef _oled12864_hal_h
#define _oled12864_hal_h

// #include "esp_system.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    void *ctx;
    void (*init)(void*);
    void (*deinit)(void*);
    void (*sendCmd)(unsigned char*cmd,unsigned char len,void*);
    void (*sendDat)(unsigned char*dat,unsigned int len,void*);
    unsigned char *buf;
}Ssd1306_hal_handle_t;

extern Ssd1306_hal_handle_t oled_spi4_handle;

#ifdef __cplusplus
}
#endif

#endif  //_oled12864_hel_h


