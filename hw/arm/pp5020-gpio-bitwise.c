#include "hw/arm/pp5020-gpio-bitwise.h"

#include "cpu.h"
#include "hw/arm/pp5020-gpio.h"
#include "qemu/error-report.h"

static uint64_t pp5020_gpio_bitwise_read(void *opaque, hwaddr addr,
                                         unsigned size) {
  info_report("pp5020_gpio_bitwise_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));

  assert(false);
  return 0;
}

static uint32_t apply_masked_value(uint32_t current, uint32_t mask,
                                   uint32_t value) {
  current &= ~(mask & ~value);
  current |= (mask & value);
  return current;
}

static void pp5020_gpio_bitwise_write(void *opaque, hwaddr addr, uint64_t data,
                                      unsigned size) {
  info_report(
      "pp5020_gpio_bitwise_write: addr=0x%lx, data=0x%lx callee=%d, pc=0x%lx",
      addr, data, current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));

  uint32_t mask = (data >> 8) & 0xff;
  uint32_t value = data & 0xff;

  PP5020GpioBitwiseState *state = PP5020_GPIO_BITWISE(opaque);
  PP5020GpioState *gpio = state->gpio_state;

  int group = PP5020_GPIO_GROUP(addr);
  int operation = PP5020_GPIO_OPERATION(addr);
  int reg = PP5020_GPIO_REG(addr);

  info_report("  group=%d, operation=%d, reg=%d", group, operation, reg);

  switch (operation) {
    case PP5020_GPIO_OPERATION_ENABLE:
    case PP5020_GPIO_OPERATION_OUTPUT_ENABLE:
    case PP5020_GPIO_OPERATION_OUTPUT_VALUE:
      break;
    default:
      assert(false);
  }

  gpio->values[group][operation][reg] =
      apply_masked_value(gpio->values[group][operation][reg], mask, value);
}

static const MemoryRegionOps pp5020_gpio_bitwise_ops = {
    .read = pp5020_gpio_bitwise_read,
    .write = pp5020_gpio_bitwise_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void pp5020_gpio_bitwise_init(Object *obj) {
  PP5020GpioBitwiseState *state = PP5020_GPIO_BITWISE(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &pp5020_gpio_bitwise_ops, state,
                        TYPE_PP5020_GPIO_BITWISE, PP5020_GPIO_BITWISE_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void pp5020_gpio_bitwise_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo pp5020_gpio_bitwise_type_info = {
    .name = TYPE_PP5020_GPIO_BITWISE,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(PP5020GpioBitwiseState),
    .instance_init = pp5020_gpio_bitwise_init,
    .class_init = pp5020_gpio_bitwise_class_init,
};

static void pp5020_gpio_bitwise_register_types(void) {
  type_register_static(&pp5020_gpio_bitwise_type_info);
}

type_init(pp5020_gpio_bitwise_register_types)
