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
#define PP5020_IDE_MEM_SIZE 0x200

#define PP5020_IDE_IDE0_PRI_TIMING0 0
#define PP5020_IDE_IDE0_PRI_TIMING1 4
#define PP5020_IDE_IDE0_CFG 0x28

#define PP5020_ATA_OFFSET 0x1e0
#define PP5020_ATA_MAX_OFFSET 0x1c
#define PP5020_ATA_DATA_OFFSET PP5020_ATA_OFFSET
#define PP5020_ATA_ERROR_OFFSET PP5020_ATA_OFFSET + 0x4
#define PP5020_ATA_NSECTOR_OFFSET PP5020_ATA_OFFSET + 0x8
#define PP5020_ATA_SECTOR_OFFSET PP5020_ATA_OFFSET + 0xc
#define PP5020_ATA_LCYL_OFFSET PP5020_ATA_OFFSET + 0x10
#define PP5020_ATA_HCYL_OFFSET PP5020_ATA_OFFSET + 0x14
#define PP5020_ATA_SELECT_OFFSET PP5020_ATA_OFFSET + 0x18
#define PP5020_ATA_COMMAND_OFFSET PP5020_ATA_OFFSET + 0x1c

//
typedef struct PP5020IdeState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t ide0_pri_timing[2];
  uint32_t ide0_cfg;
  IDEBus bus;
} PP5020IdeState;

#endif
