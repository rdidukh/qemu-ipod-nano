#include "hw/arm/pp5020-ata-ctrl.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_ata_ctrl_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_ata_ctrl_read: addr=%ld, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));

  PP5020AtaCtrlState *state = PP5020_ATA_CTRL(opaque);

  assert(addr == 0);

  return state->alternate_status;
}

static void pp5020_ata_ctrl_write(void *opaque, hwaddr addr, uint64_t data,
                                  unsigned size) {
  info_report("pp5020_ata_ctrl_write: addr=%ld, data=%ld, callee=%d, pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  assert(addr == 0);

  // TODO: Implement writing to Device control register.
}

static const MemoryRegionOps pp5020_ata_ctrl_ops = {
    .read = pp5020_ata_ctrl_read,
    .write = pp5020_ata_ctrl_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_ata_ctrl_init(Object *obj) {
  PP5020AtaCtrlState *state = PP5020_ATA_CTRL(obj);
  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_ata_ctrl_ops, state,
                        TYPE_PP5020_ATA_CTRL, PP5020_ATA_CTRL_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
  state->alternate_status = PP5020_ATA_STATUS_READY;
}

static void pp5020_ata_ctrl_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_ata_ctrl_type_info = {
    .name = TYPE_PP5020_ATA_CTRL,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020AtaCtrlState),
    .instance_init = pp5020_ata_ctrl_init,
    .class_init = pp5020_ata_ctrl_class_init,
};

static void pp5020_ata_ctrl_register_types(void) {
  type_register_static(&pp5020_ata_ctrl_type_info);
}

type_init(pp5020_ata_ctrl_register_types)
