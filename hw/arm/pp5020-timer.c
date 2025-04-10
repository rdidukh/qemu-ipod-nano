#include "hw/arm/pp5020-timer.h"

#include "cpu.h"
#include "qemu/error-report.h"
#include "qemu/timer.h"

static uint64_t pp5020_timer_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_timer_read: addr=0x%lx, callee: %d pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  // TODO: PP5020TimerState *state = PP5020_TIMER(opaque);

  switch (addr) {
    case PP5020_TIMER_USEC_OFFSET:
      return qemu_clock_get_us(QEMU_CLOCK_VIRTUAL);
    default:
      break;
  }

  assert(false);
  return 0;
}

static void pp5020_timer_write(void *opaque, hwaddr addr, uint64_t data,
                               unsigned size) {
  info_report("pp5020_timer_write: addr=0x%lx, data=0x%lx callee: %d pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));
  assert(false);
}

static const MemoryRegionOps pp5020_timer_ops = {
    .read = pp5020_timer_read,
    .write = pp5020_timer_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_timer_init(Object *obj) {
  PP5020TimerState *state = PP5020_TIMER(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_timer_ops, state,
                        TYPE_PP5020_TIMER, PP5020_TIMER_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_timer_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_timer_type_info = {
    .name = TYPE_PP5020_TIMER,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020TimerState),
    .instance_init = pp5020_timer_init,
    .class_init = pp5020_timer_class_init,
};

static void pp5020_timer_register_types(void) {
  type_register_static(&pp5020_timer_type_info);
}

type_init(pp5020_timer_register_types)
