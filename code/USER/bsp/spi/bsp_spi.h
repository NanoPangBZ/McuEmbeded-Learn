#pragma once

//向外声明bsp的功能全部由C函数实现
#ifdef __cplusplus
extern "C"{
#endif

void spi_write_read( uint8_t* buf , uint16_t len );

#ifdef __cplusplus
}
#endif
