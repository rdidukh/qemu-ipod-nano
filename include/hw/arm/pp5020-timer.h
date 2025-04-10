#ifndef HW_ARM_PP5020_TIMER_H
#define HW_ARM_PP5020_TIMER_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_TIMER "pp5020-timer-ctrl"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020TimerState, PP5020_TIMER)

#define PP5020_TIMER_BASE_ADDR 0x60005000
#define PP5020_TIMER_MEM_SIZE 0x18

#define PP5020_TIMER_USEC_OFFSET 0x10

typedef struct PP5020TimerState {
  SysBusDevice busdev;
  MemoryRegion iomem;
} PP5020TimerState;

#endif
