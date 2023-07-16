#pragma once

#define WRITE_ENABLE_CMD            (0x06)
#define WRITE_DISABLE_CMD           (0x04)
#define JEDEC_ID_CMD                (0x9F)

#define READ_STATUS_REG1_CMD        (0x05)
#define WRITE_STATUS_REG1_CMD       (0x01)
#define READ_STATUS_REG2_CMD        (0x35)
#define WRITE_STATUS_REG2_CMD       (0x31)
#define READ_STATUS_REG3_CMD        (0x15)
#define WRITE_STATUS_REG3_CMD       (0x11)

#define ERASE_4K_SECTOR_CMD         (0x20)
#define ERASE_32K_BLOCK_CMD         (0x52)
#define ERASE_64K_BLOCK_CMD         (0xD8)
#define ERASE_ALL_CHIP_CMD          (0xC7)

#define PAGE_PROGRAM_CMD            (0x02)
#define READ_DATA_CMD               (0x03)

#define RESET_DEVICE_CMD            (0x99)

#define REG1_BUSY_MASK              (0x01<<0)
