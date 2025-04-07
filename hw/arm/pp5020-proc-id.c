#include "hw/arm/pp5020-proc-id.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_proc_id_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_proc_id_read: %ld", addr);

  CPUState *cpu = current_cpu;

  info_report("pp5020_proc_id_read: addr=%ld, cpu=%d", addr, cpu->cpu_index);

  switch (addr) {
    case 0x0:
      return cpu->cpu_index == 0 ? PP5020_PROC_ID_CPU : PP5020_PROC_ID_COP;
    default:
      break;
  }

  return 0;
}

static const MemoryRegionOps pp5020_proc_id_ops = {
    .read = pp5020_proc_id_read,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_proc_id_init(Object *obj) {
  PP5020ProcIdState *state = PP5020_PROC_ID(obj);
  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_proc_id_ops, state,
                        TYPE_PP5020_PROC_ID, PP5020_PROC_ID_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_proc_id_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_proc_id_type_info = {
    .name = TYPE_PP5020_PROC_ID,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020ProcIdState),
    .instance_init = pp5020_proc_id_init,
    .class_init = pp5020_proc_id_class_init,
};

static void pp5020_proc_id_register_types(void) {
  type_register_static(&pp5020_proc_id_type_info);
}

type_init(pp5020_proc_id_register_types)
