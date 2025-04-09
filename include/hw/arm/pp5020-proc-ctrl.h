#ifndef HW_ARM_PP5020_PROC_CTRL_H
#define HW_ARM_PP5020_PROC_CTRL_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_PROC_CTRL "pp5020-proc-ctrl"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020ProcCtrlState, PP5020_PROC_CTRL)

#define PP5020_PROC_CTRL_BASE_ADDR 0x60007000
#define PP5020_PROC_CTRL_MEM_SIZE 0x8

typedef struct PP5020ProcCtrlState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  bool sleep[2];
} PP5020ProcCtrlState;

#endif
