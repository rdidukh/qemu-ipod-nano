#ifndef HW_ARM_PP5020_GPIO_H
#define HW_ARM_PP5020_GPIO_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_GPIO "pp5020-gpio"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020GpioState, PP5020_GPIO)

#define PP5020_GPIO_BASE_ADDR 0x6000d000
#define PP5020_GPIO_MEM_SIZE 0x34

#define GPIOA_INPUT_OFFSET 0x30

#define HOLD_SWITCH 0x20

typedef struct PP5020GpioState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t gpioa;
  uint32_t gpiob;
} PP5020GpioState;

#endif
