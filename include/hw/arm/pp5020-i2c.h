#ifndef HW_ARM_PP5020_I2C_H
#define HW_ARM_PP5020_I2C_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_I2C "pp5020-i2c"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020I2cState, PP5020_I2C)

#define PP5020_I2C_BASE_ADDR 0x7000c000
#define PP5020_I2C_MEM_SIZE 0x144

#define PP5020_I2C_CLICKWHEEL_DATA 0x140

typedef struct PP5020I2cState {
  SysBusDevice busdev;
  MemoryRegion iomem;
} PP5020I2cState;

#endif
