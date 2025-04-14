#ifndef HW_ARM_HD66789R_LCD_H
#define HW_ARM_HD66789R_LCD_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_HD66789R_LCD "hd66789r-lcd"
OBJECT_DECLARE_SIMPLE_TYPE(Hd66789rLcdState, HD66789R_LCD)

#define HD66789R_LCD_BASE_ADDR 0x70008a00
#define HD66789R_LCD_MEM_SIZE 0x10

#define HD66789R_LCD_PORT_OFFSET 0xc

#define HD66789R_LCD_CMD_MASK 0x80000000
#define HD66789R_LCD_DATA_MASK 0x81000000

typedef struct Hd66789rLcdState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t command;
  uint32_t data;
} Hd66789rLcdState;

#endif
