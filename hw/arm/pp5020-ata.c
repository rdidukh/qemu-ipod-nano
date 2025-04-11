#include "hw/arm/pp5020-ata.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_ata_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_ata_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  PP5020AtaState *state = PP5020_ATA(opaque);

  switch (addr) {
    case PP5020_ATA_NSECTOR:
      return state->nsector;
    case PP5020_ATA_SECTOR:
      return state->sector;
    case PP5020_ATA_LCYL:
      return state->lcyl;
    case PP5020_ATA_HCYL:
      return state->hcyl;
    case PP5020_ATA_SELECT:
      return state->select;
    case PP5020_ATA_COMMAND:
      return state->status;
    default:
  }

  assert(false);
}

static void pp5020_ata_write(void *opaque, hwaddr addr, uint64_t data,
                             unsigned size) {
  info_report("pp5020_ata_write: addr=0x%lx, data=0x%lx callee=%d, pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  PP5020AtaState *state = PP5020_ATA(opaque);

  switch (addr) {
    case PP5020_ATA_NSECTOR:
      state->nsector = data;
      return;
    case PP5020_ATA_SECTOR:
      state->sector = data;
      return;
    case PP5020_ATA_LCYL:
      state->lcyl = data;
      return;
    case PP5020_ATA_HCYL:
      state->hcyl = data;
      return;
    case PP5020_ATA_SELECT:
      state->select = data;
      return;

    default:
  }

  assert(false);
}

static const MemoryRegionOps pp5020_ata_ops = {
    .read = pp5020_ata_read,
    .write = pp5020_ata_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_ata_init(Object *obj) {
  PP5020AtaState *state = PP5020_ATA(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_ata_ops, state,
                        TYPE_PP5020_ATA, PP5020_ATA_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);

  state->status = PP5020_ATA_STATUS_READY;
}

static void pp5020_ata_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_ata_type_info = {
    .name = TYPE_PP5020_ATA,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020AtaState),
    .instance_init = pp5020_ata_init,
    .class_init = pp5020_ata_class_init,
};

static void pp5020_ata_register_types(void) {
  type_register_static(&pp5020_ata_type_info);
}

type_init(pp5020_ata_register_types)
