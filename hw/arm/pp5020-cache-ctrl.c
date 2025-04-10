#include "hw/arm/pp5020-cache-ctrl.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_cache_ctrl_read(void *opaque, hwaddr addr,
                                       unsigned size) {
  info_report("pp5020_cache_ctrl_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  // TODO: PP5020CacheCtrlState *state = PP5020_CACHE_CTRL(opaque);

  if (addr == 0) {
    // Always report cache as disabled.
    // TODO: implement if ever needed.
    return 0;
  }

  assert(false);
  return 0;
}

static void pp5020_cache_ctrl_write(void *opaque, hwaddr addr, uint64_t data,
                                    unsigned size) {
  info_report(
      "pp5020_cache_ctrl_write: addr=0x%lx, data=0x%lx callee: %d pc=0x%lx",
      addr, data, current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));

  if (addr == 0) {
    // Ignore any cache control commands.
    // TODO: implement if ever needed.
    return;
  }

  assert(false);
}

static const MemoryRegionOps pp5020_cache_ctrl_ops = {
    .read = pp5020_cache_ctrl_read,
    .write = pp5020_cache_ctrl_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_cache_ctrl_init(Object *obj) {
  PP5020CacheCtrlState *state = PP5020_CACHE_CTRL(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_cache_ctrl_ops, state,
                        TYPE_PP5020_CACHE_CTRL, PP5020_CACHE_CTRL_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_cache_ctrl_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_cache_ctrl_type_info = {
    .name = TYPE_PP5020_CACHE_CTRL,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020CacheCtrlState),
    .instance_init = pp5020_cache_ctrl_init,
    .class_init = pp5020_cache_ctrl_class_init,
};

static void pp5020_cache_ctrl_register_types(void) {
  type_register_static(&pp5020_cache_ctrl_type_info);
}

type_init(pp5020_cache_ctrl_register_types)
