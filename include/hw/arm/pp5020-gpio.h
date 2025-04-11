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

#define PP5020_GPIO_B_ENABLE 0x4
#define PP5020_GPIO_D_ENABLE 0xc
#define PP5020_GPIO_B_OUTPUT_ENABLE 0x14
#define PP5020_GPIO_D_OUTPUT_ENABLE 0x1c
#define PP5020_GPIO_B_OUTPUT_VALUE 0x24
#define PP5020_GPIO_D_OUTPUT_VALUE 0x2c
#define PP5020_GPIO_A_INPUT_VALUE 0x30

#define HOLD_SWITCH 0x20

typedef struct PP5020GpioState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t b_enabled;
  uint32_t d_enabled;
  uint32_t b_output_enabled;
  uint32_t d_output_enabled;
  uint32_t b_output_value;
  uint32_t d_output_value;
  uint32_t a_input_value;
} PP5020GpioState;

#endif
