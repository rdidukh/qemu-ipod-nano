#ifndef HW_ARM_PP5020_PROC_ID_H
#define HW_ARM_PP5020_PROC_ID_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_PROC_ID "pp5020-proc-id"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020ProcIdState, PP5020_PROC_ID)

#define PP5020_PROC_ID_CPU 0x55
#define PP5020_PROC_ID_COP 0xaa

#define PP5020_PROC_ID_BASE_ADDR 0x60000000
#define PP5020_PROC_ID_MEM_SIZE 0x4

typedef struct PP5020ProcIdState {
  SysBusDevice busdev;
  MemoryRegion iomem;
} PP5020ProcIdState;

#endif
