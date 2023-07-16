#pragma once

#include <stdint.h>

uint16_t w25qxx_get_id( void );
uint8_t w25qxx_write_enable(void);
uint8_t w25qxx_write_disable(void);
uint8_t w25qxx_read_status_regsiter1( void );
uint8_t w25qxx_erase_4k_sector( uint32_t addr );
uint8_t w25qxx_erase_32k_block( uint32_t addr );
uint8_t w25qxx_erase_64k_block( uint32_t addr );
uint8_t w25qxx_erase_all_chip( void );
uint8_t w25qxx_program_page( uint32_t addr , uint8_t* data , uint16_t len );
uint8_t w25qxx_program( uint32_t addr , uint8_t* data , uint16_t len );
uint8_t w25qxx_read( uint32_t addr , uint8_t* buf , uint16_t len );

uint8_t w25qxx_test( void );
