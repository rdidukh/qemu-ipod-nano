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

#define PP5020_GPIO_GROUP_COUNT 3
#define PP5020_GPIO_OPERATION_COUNT 8
#define PP5020_GPIO_REGISTERS_PER_GROUP 4

#define PP5020_GPIO_OPERATION_ENABLE 0
#define PP5020_GPIO_OPERATION_OUTPUT_ENABLE 1
#define PP5020_GPIO_OPERATION_OUTPUT_VALUE 2
#define PP5020_GPIO_OPERATION_INPUT_VALUE 3

#define PP5020_GPIO_REG_A 0
#define PP5020_GPIO_REG_B 1
#define PP5020_GPIO_REG_D 3
#define PP5020_GPIO_REG_L 3

#define HOLD_SWITCH 0x20
//

typedef struct PP5020GpioState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t values[PP5020_GPIO_GROUP_COUNT][PP5020_GPIO_OPERATION_COUNT]
                 [PP5020_GPIO_REGISTERS_PER_GROUP];
} PP5020GpioState;

#define PP5020_GPIO_MEM_SIZE sizeof(((PP5020GpioState *)0)->values)

#define PP5020_GPIO_SIZEOF_GROUP sizeof(((PP5020GpioState *)0)->values[0])
#define PP5020_GPIO_GROUP(addr) ((addr) / PP5020_GPIO_SIZEOF_GROUP)
#define PP5020_GPIO_GROUP_BASE_ADDR(addr) \
  PP5020_GPIO_GROUP(addr) * PP5020_GPIO_SIZEOF_GROUP

#define PP5020_GPIO_SIZEOF_OPERATION \
  sizeof(((PP5020GpioState *)0)->values[0][0])
#define PP5020_GPIO_OPERATION(addr) \
  (addr - PP5020_GPIO_GROUP_BASE_ADDR(addr)) / PP5020_GPIO_SIZEOF_OPERATION
#define PP5020_GPIO_OPERATION_BASE_ADDR(addr) \
  (PP5020_GPIO_GROUP_BASE_ADDR(addr) +        \
   PP5020_GPIO_OPERATION(addr) * PP5020_GPIO_SIZEOF_OPERATION)

#define PP5020_GPIO_SIZEOF_REG sizeof(((PP5020GpioState *)0)->values[0][0][0])
#define PP5020_GPIO_REG(addr) \
  ((addr - PP5020_GPIO_OPERATION_BASE_ADDR(addr)) / PP5020_GPIO_SIZEOF_REG)

#endif
