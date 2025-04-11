#ifndef HW_ARM_PP5020_IDE_DMA_H
#define HW_ARM_PP5020_IDE_DMA_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on

#include "hw/sysbus.h"

#define TYPE_PP5020_IDE_DMA "pp5020-ide-dma"
OBJECT_DECLARE_SIMPLE_TYPE(PP5020IdeDmaState, PP5020_IDE_DMA)

#define PP5020_IDE_DMA_BASE_ADDR 0xc3000400
#define PP5020_IDE_DMA_MEM_SIZE 0x10

#define PP5020_IDE_DMA_CONTROL 0

typedef struct PP5020IdeDmaState {
  SysBusDevice busdev;
  MemoryRegion iomem;
  uint32_t control;
} PP5020IdeDmaState;

#endif
