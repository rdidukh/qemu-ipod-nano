#ifndef HW_ARM_PP5020_ATA_CTRL_H
#define HW_ARM_PP5020_ATA_CTRL_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/arm/pp5020-ide.h"
#include "hw/sysbus.h"

#define TYPE_PP5020_ATA_CTRL "pp5020-ata-ctrl"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020AtaCtrlState, PP5020_ATA_CTRL)

#define PP5020_ATA_CTRL_BASE_ADDR PP5020_IDE_BASE_ADDR + 0x3f8
#define PP5020_ATA_CTRL_MEM_SIZE 0x4

typedef struct PP5020AtaCtrlState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t data;
} PP5020AtaCtrlState;

#endif
