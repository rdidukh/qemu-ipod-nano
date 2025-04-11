#include "hw/arm/pp5020-ide-dma.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_ide_dma_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_ide_dma_read: addr=%ld, callee: %d pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));

  PP5020IdeDmaState *state = PP5020_IDE_DMA(opaque);

  switch (addr) {
    // TODO: constant.
    case PP5020_IDE_DMA_CONTROL:
      return state->control;
      break;
    default:
  }

  assert(false);
}

static void pp5020_ide_dma_write(void *opaque, hwaddr addr, uint64_t data,
                                 unsigned size) {
  info_report("pp5020_ide_dma_write: addr=%ld, data=%ld callee: %d pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  PP5020IdeDmaState *state = PP5020_IDE_DMA(opaque);

  switch (addr) {
    case PP5020_IDE_DMA_CONTROL:
      state->control = data;
      break;
    default:
      assert(false);
  }
}

static const MemoryRegionOps pp5020_ide_dma_ops = {
    .read = pp5020_ide_dma_read,
    .write = pp5020_ide_dma_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_ide_dma_init(Object *obj) {
  PP5020IdeDmaState *state = PP5020_IDE_DMA(obj);
  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_ide_dma_ops, state,
                        TYPE_PP5020_IDE_DMA, PP5020_IDE_DMA_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_ide_dma_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_ide_dma_type_info = {
    .name = TYPE_PP5020_IDE_DMA,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020IdeDmaState),
    .instance_init = pp5020_ide_dma_init,
    .class_init = pp5020_ide_dma_class_init,
};

static void pp5020_ide_dma_register_types(void) {
  type_register_static(&pp5020_ide_dma_type_info);
}

type_init(pp5020_ide_dma_register_types)
