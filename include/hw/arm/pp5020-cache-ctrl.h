#ifndef HW_ARM_PP5020_CACHE_CTRL_H
#define HW_ARM_PP5020_CACHE_CTRL_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_CACHE_CTRL "pp5020-cache-ctrl"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020CacheCtrlState, PP5020_CACHE_CTRL)

#define PP5020_CACHE_CTRL_BASE_ADDR 0x6000c000
#define PP5020_CACHE_CTRL_MEM_SIZE 0x4

typedef struct PP5020CacheCtrlState {
  SysBusDevice busdev;
  MemoryRegion iomem;
} PP5020CacheCtrlState;

#endif
