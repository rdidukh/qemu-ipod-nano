#include "hw/arm/pp5020-ide.h"

#include "cpu.h"
#include "hw/ide/ide-bus.h"
#include "hw/ide/ide-internal.h"
#include "qemu/error-report.h"
#include "system/blockdev.h"

static uint64_t pp5020_ide_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_ide_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  PP5020IdeState *state = PP5020_IDE(opaque);

  switch (addr) {
    case PP5020_IDE_IDE0_CFG:
      return state->ide0_cfg;
    default:
  }

  assert(false);
}

static void pp5020_ide_write(void *opaque, hwaddr addr, uint64_t data,
                             unsigned size) {
  info_report("pp5020_ide_write: addr=0x%lx, data=0x%lx callee=%d, pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  PP5020IdeState *state = PP5020_IDE(opaque);

  switch (addr) {
    case PP5020_IDE_IDE0_PRI_TIMING0:
    case PP5020_IDE_IDE0_PRI_TIMING1:
      state->ide0_pri_timing[(addr - PP5020_IDE_IDE0_PRI_TIMING0) / 4] = data;
      return;
    case PP5020_IDE_IDE0_CFG:
      state->ide0_cfg = data;
      return;
    default:
  }

  assert(false);
}

static uint64_t pp5020_ata_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_ata_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  PP5020IdeState *state = PP5020_IDE(opaque);

  return ide_ioport_read(&state->bus, addr / 4);
}

static void pp5020_ata_write(void *opaque, hwaddr addr, uint64_t data,
                             unsigned size) {
  info_report("pp5020_ata_write: addr=0x%lx, data=0x%lx callee=%d, pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  PP5020IdeState *state = PP5020_IDE(opaque);

  ide_ioport_write(&state->bus, addr / 4, data);
}

static const MemoryRegionOps pp5020_ide_ops = {
    .read = pp5020_ide_read,
    .write = pp5020_ide_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static const MemoryRegionOps pp5020_ata_ops = {
    .read = pp5020_ata_read,
    .write = pp5020_ata_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_ide_init(Object *obj) {
  PP5020IdeState *state = PP5020_IDE(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init(&state->iomem, obj, TYPE_PP5020_IDE, 0xfedc);

  memory_region_init_io(&state->timing_iomem, obj, &pp5020_ide_ops, state,
                        TYPE_PP5020_IDE "-timing", PP5020_IDE_TIMING_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->timing_iomem);
  memory_region_add_subregion(&state->iomem, PP5020_IDE_TIMING_OFFSET,
                              &state->timing_iomem);

  memory_region_init_io(&state->ata_iomem, obj, &pp5020_ata_ops, state,
                        TYPE_PP5020_IDE "-ata", PP5020_IDE_ATA_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->ata_iomem);
  memory_region_add_subregion(&state->iomem, PP5020_IDE_ATA_OFFSET,
                              &state->ata_iomem);

  ide_bus_init(&state->bus, sizeof(state->bus), DEVICE(obj), 0, 1);
  ide_bus_init_output_irq(&state->bus, NULL);

  DriveInfo *di = drive_get_by_index(IF_IDE, 0);

  assert(di != NULL);

  ide_bus_create_drive(&state->bus, 0, di);

  state->ide0_pri_timing[0] = 0;
  state->ide0_pri_timing[1] = 0;
  state->ide0_cfg = 0;
}

static void pp5020_ide_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_ide_type_info = {
    .name = TYPE_PP5020_IDE,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020IdeState),
    .instance_init = pp5020_ide_init,
    .class_init = pp5020_ide_class_init,
};

static void pp5020_ide_register_types(void) {
  type_register_static(&pp5020_ide_type_info);
}

type_init(pp5020_ide_register_types)
