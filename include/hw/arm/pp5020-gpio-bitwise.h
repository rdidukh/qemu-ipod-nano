#ifndef HW_ARM_PP5020_GPIO_BITWISE_H
#define HW_ARM_PP5020_GPIO_BITWISE_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/arm/pp5020-gpio.h"
#include "hw/sysbus.h"

#define TYPE_PP5020_GPIO_BITWISE "pp5020-gpio-bitwise"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020GpioBitwiseState, PP5020_GPIO_BITWISE)

#define PP5020_GPIO_BITWISE_BASE_ADDR 0x6000d800
#define PP5020_GPIO_BITWISE_MEM_SIZE PP5020_GPIO_MEM_SIZE

#define HOLD_SWITCH 0x20

typedef struct PP5020GpioBitwiseState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  PP5020GpioState* gpio_state;
} PP5020GpioBitwiseState;

#endif
