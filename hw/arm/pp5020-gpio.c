#include "hw/arm/pp5020-gpio.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t pp5020_gpio_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("pp5020_gpio_read: addr=0x%lx, callee: %d pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  PP5020GpioState *state = PP5020_GPIO(opaque);

  switch (addr) {
    case GPIOA_INPUT_OFFSET:
      return state->gpioa;
  }

  assert(false);
  return 0;
}

static void pp5020_gpio_write(void *opaque, hwaddr addr, uint64_t data,
                              unsigned size) {
  info_report("pp5020_gpio_write: addr=0x%lx, data=0x%lx callee: %d pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));
  assert(false);
}

static const MemoryRegionOps pp5020_gpio_ops = {
    .read = pp5020_gpio_read,
    .write = pp5020_gpio_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_gpio_init(Object *obj) {
  PP5020GpioState *state = PP5020_GPIO(obj);

  state->gpioa = 0xffffffff;

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_gpio_ops, state,
                        TYPE_PP5020_GPIO, PP5020_GPIO_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_gpio_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_gpio_type_info = {
    .name = TYPE_PP5020_GPIO,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020GpioState),
    .instance_init = pp5020_gpio_init,
    .class_init = pp5020_gpio_class_init,
};

static void pp5020_gpio_register_types(void) {
  type_register_static(&pp5020_gpio_type_info);
}

type_init(pp5020_gpio_register_types)
