#include "hw/arm/pp5020-i2c.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_i2c_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_i2c_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  // TODO: PP5020I2cState *state = PP5020_I2C(opaque);

  switch (addr) {
    case 0x100:
    case 0x104:
    case 0x120:
      return 0;
    default:
  }

  assert(false);
}

static void pp5020_i2c_write(void *opaque, hwaddr addr, uint64_t data,
                             unsigned size) {
  info_report("pp5020_i2c_write: addr=0x%lx, data=0x%lx callee=%d, pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  switch (addr) {
    case 0x100:
    case 0x104:
    case 0x120:
      return;
    default:
  }

  assert(false);
}

static const MemoryRegionOps pp5020_i2c_ops = {
    .read = pp5020_i2c_read,
    .write = pp5020_i2c_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_i2c_init(Object *obj) {
  PP5020I2cState *state = PP5020_I2C(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_i2c_ops, state,
                        TYPE_PP5020_I2C, PP5020_I2C_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_i2c_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_i2c_type_info = {
    .name = TYPE_PP5020_I2C,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020I2cState),
    .instance_init = pp5020_i2c_init,
    .class_init = pp5020_i2c_class_init,
};

static void pp5020_i2c_register_types(void) {
  type_register_static(&pp5020_i2c_type_info);
}

type_init(pp5020_i2c_register_types)
