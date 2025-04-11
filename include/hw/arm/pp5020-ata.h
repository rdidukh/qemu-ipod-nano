#ifndef HW_ARM_PP5020_ATA_H
#define HW_ARM_PP5020_ATA_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/arm/pp5020-ide.h"
#include "hw/sysbus.h"

#define TYPE_PP5020_ATA "pp5020-ata"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020AtaState, PP5020_ATA)

#define PP5020_ATA_BASE_ADDR PP5020_IDE_BASE_ADDR + 0x1e0
#define PP5020_ATA_MEM_SIZE 0x20

#define PP5020_ATA_DATA 0
#define PP5020_ATA_ERROR 4
#define PP5020_ATA_NSECTOR 8
#define PP5020_ATA_SECTOR 0xc
#define PP5020_ATA_LCYL 0x10
#define PP5020_ATA_HCYL 0x14
#define PP5020_ATA_SELECT 0x18
#define PP5020_ATA_COMMAND 0x1c

#define PP5020_ATA_STATUS_READY 0x40
#define PP5020_ATA_STATUS_BUSY 0x80
#define PP5020_ATA_STATUS_DRQ 0x08  // Ready to transfer data

typedef struct PP5020AtaState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t status;
  uint32_t nsector;
  uint32_t sector;
  uint32_t select;
  uint32_t lcyl;
  uint32_t hcyl;
} PP5020AtaState;

#endif
