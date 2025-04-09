#include "hw/arm/pp5020-proc-ctrl.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_proc_ctrl_read(void *opaque, hwaddr addr,
                                      unsigned size) {
  info_report("pp5020_proc_ctrl_read: addr=%ld, callee: %d pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));

  // PP5020ProcCtrlState *state = PP5020_PROC_CTRL(opaque);

  int cpu_num = addr / 4;

  bool is_stopped = cpu_is_stopped(qemu_get_cpu(cpu_num));

  info_report("  cpu %d stopped=%d callee: %d", cpu_num, is_stopped,
              current_cpu->cpu_index);

  return is_stopped ? 0x80000000 : 0;
}

static void pp5020_proc_ctrl_write(void *opaque, hwaddr addr, uint64_t data,
                                   unsigned size) {
  info_report("pp5020_proc_ctrl_write: addr=%ld, data=%ld callee: %d pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));
  assert(data == 0 || data == 0x80000000);

  // PP5020ProcCtrlState *state = PP5020_PROC_CTRL(opaque);

  int cpu_num = addr / 4;

  bool sleep = data & 0x80000000;

  CPUState *cpu = qemu_get_cpu(cpu_num);
  if (sleep) {
    cpu_pause(cpu);
  } else {
    cpu_resume(cpu);
  }

  // TODO: synchronize
  // state->sleep[cpu_num] = sleep;
}

static const MemoryRegionOps pp5020_proc_ctrl_ops = {
    .read = pp5020_proc_ctrl_read,
    .write = pp5020_proc_ctrl_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_proc_ctrl_init(Object *obj) {
  PP5020ProcCtrlState *state = PP5020_PROC_CTRL(obj);
  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_proc_ctrl_ops, state,
                        TYPE_PP5020_PROC_CTRL, PP5020_PROC_CTRL_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_proc_ctrl_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_proc_ctrl_type_info = {
    .name = TYPE_PP5020_PROC_CTRL,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020ProcCtrlState),
    .instance_init = pp5020_proc_ctrl_init,
    .class_init = pp5020_proc_ctrl_class_init,
};

static void pp5020_proc_ctrl_register_types(void) {
  type_register_static(&pp5020_proc_ctrl_type_info);
}

type_init(pp5020_proc_ctrl_register_types)
