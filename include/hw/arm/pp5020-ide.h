#ifndef HW_ARM_PP5020_IDE_H
#define HW_ARM_PP5020_IDE_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/ide/ide-bus.h"
#include "hw/sysbus.h"

#define TYPE_PP5020_IDE "pp5020-ide"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020IdeState, PP5020_IDE)

#define PP5020_IDE_BASE_ADDR 0xc3000000
#define PP5020_IDE_TIMING_OFFSET 0
#define PP5020_IDE_TIMING_MEM_SIZE 0x30

#define PP5020_IDE_ATA_OFFSET 0x1e0
#define PP5020_IDE_ATA_MEM_SIZE 0x20

#define PP5020_IDE_IDE0_PRI_TIMING0 0
#define PP5020_IDE_IDE0_PRI_TIMING1 4
#define PP5020_IDE_IDE0_CFG 0x28

typedef struct PP5020IdeState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  MemoryRegion timing_iomem;
  MemoryRegion ata_iomem;
  uint32_t ide0_pri_timing[2];
  uint32_t ide0_cfg;
  IDEBus bus;
} PP5020IdeState;

#endif
