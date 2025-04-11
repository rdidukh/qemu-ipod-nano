#include "hw/arm/ipod_nano_1g.h"

#include "exec/address-spaces.h"
#include "hw/arm/pp5020-cache-ctrl.h"
#include "hw/arm/pp5020-gpio-bitwise.h"
#include "hw/arm/pp5020-gpio.h"
#include "hw/arm/pp5020-i2c.h"
#include "hw/arm/pp5020-ide-dma.h"
#include "hw/arm/pp5020-ide.h"
#include "hw/arm/pp5020-proc-ctrl.h"
#include "hw/arm/pp5020-proc-id.h"
#include "hw/arm/pp5020-timer.h"
#include "hw/loader.h"
#include "qapi/error.h"
#include "qemu/datadir.h"
#include "qemu/error-report.h"
#include "qemu/units.h"
#include "target/arm/internals.h"

static void ipod_nano_1g_init(MachineState *machine) {
  info_report("ipod_nano_1g_init");

  // IPodNano1GMachineState *state = IPOD_NANO_1G_MACHINE(machine);

  for (int cpu = 0; cpu < machine->smp.cpus; cpu++) {
    Object *cpuobj = object_new(machine->cpu_type);
    ARMCPU *armcpu = ARM_CPU(cpuobj);

    // TODO: this causes Assertion `object_dynamic_cast(container,
    // TYPE_CONTAINER)' failed
    // state->cpu[cpu] = armcpu;

    if (!qdev_realize(DEVICE(armcpu), NULL, &error_abort)) {
      return;
    }

    cpu_set_pc(CPU(armcpu), IPOD_NANO_1G_RAM_BASE_ADDR);

    object_unref(cpuobj);
  }

  MemoryRegion *arm_vectors = g_new(MemoryRegion, 1);
  memory_region_init_ram(arm_vectors, NULL, "arm-vectors", 0x100, &error_fatal);
  memory_region_add_subregion(get_system_memory(), 0x0, arm_vectors);
  uint32_t *vectors_data = memory_region_get_ram_ptr(arm_vectors);

  for (int i = 0; i < 8; i++) {
    vectors_data[i] = 0xea000006 - i;  // b idle
  }
  // idle:
  vectors_data[8] = 0xe320f003;  // wfi
  vectors_data[9] = 0xeafffffd;  // b idle

  MemoryRegion *ipod_revision = g_new(MemoryRegion, 1);
  memory_region_init_ram(ipod_revision, NULL, "ipod-revision", 0x4,
                         &error_fatal);
  memory_region_add_subregion(get_system_memory(), IPOD_HW_REVISION_ADDR,
                              ipod_revision);
  uint32_t *ipod_revision_data = memory_region_get_ram_ptr(ipod_revision);
  // TODO: get it be retrieved from the firmware?
  ipod_revision_data[0] = IPOD_NANO_1G_HW_REVISION;

  MemoryRegion *ram = g_new(MemoryRegion, 1);
  memory_region_init_ram(ram, NULL, "ram", machine->ram_size, &error_fatal);
  memory_region_add_subregion(get_system_memory(), IPOD_NANO_1G_RAM_BASE_ADDR,
                              ram);

  MemoryRegion *fastram = g_new(MemoryRegion, 1);
  memory_region_init_ram(fastram, NULL, "fastram", IPOD_NANO_1G_FASTRAM_SIZE,
                         &error_fatal);
  memory_region_add_subregion(get_system_memory(),
                              IPOD_NANO_1G_FASTRAM_BASE_ADDR, fastram);

  // TODO: Don't care about cache control for now. Simply enable it as RAM
  // intead of an memory mapped device.
  MemoryRegion *mem_ctrl = g_new(MemoryRegion, 1);
  memory_region_init_ram(mem_ctrl, NULL, "mem-ctrl",
                         PP5020_MEMORY_CONTROL_MEM_SIZE, &error_fatal);
  memory_region_add_subregion(get_system_memory(),
                              PP5020_MEMORY_CONTROL_BASE_ADDR, mem_ctrl);

  DeviceState *dev = qdev_new(TYPE_PP5020_PROC_ID);
  PP5020ProcIdState *proc_id_state = PP5020_PROC_ID(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_PROC_ID_BASE_ADDR,
                              &proc_id_state->iomem);

  dev = qdev_new(TYPE_PP5020_PROC_CTRL);
  PP5020ProcCtrlState *proc_ctrl_state = PP5020_PROC_CTRL(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_PROC_CTRL_BASE_ADDR,
                              &proc_ctrl_state->iomem);

  dev = qdev_new(TYPE_PP5020_CACHE_CTRL);
  PP5020CacheCtrlState *cache_ctrl_state = PP5020_CACHE_CTRL(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_CACHE_CTRL_BASE_ADDR,
                              &cache_ctrl_state->iomem);

  dev = qdev_new(TYPE_PP5020_GPIO);
  PP5020GpioState *gpio_state = PP5020_GPIO(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_GPIO_BASE_ADDR,
                              &gpio_state->iomem);

  dev = qdev_new(TYPE_PP5020_GPIO_BITWISE);
  PP5020GpioBitwiseState *gpio_bitwise_state = PP5020_GPIO_BITWISE(dev);
  memory_region_add_subregion(get_system_memory(),
                              PP5020_GPIO_BITWISE_BASE_ADDR,
                              &gpio_bitwise_state->iomem);
  gpio_bitwise_state->gpio_state = gpio_state;

  dev = qdev_new(TYPE_PP5020_I2C);
  PP5020I2cState *i2c_state = PP5020_I2C(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_I2C_BASE_ADDR,
                              &i2c_state->iomem);

  dev = qdev_new(TYPE_PP5020_IDE);
  PP5020IdeState *ide_state = PP5020_IDE(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_IDE_BASE_ADDR,
                              &ide_state->iomem);

  dev = qdev_new(TYPE_PP5020_IDE_DMA);
  PP5020IdeDmaState *ide_dma_state = PP5020_IDE_DMA(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_IDE_DMA_BASE_ADDR,
                              &ide_dma_state->iomem);

  dev = qdev_new(TYPE_PP5020_TIMER);
  PP5020TimerState *timer_state = PP5020_TIMER(dev);
  memory_region_add_subregion(get_system_memory(), PP5020_TIMER_BASE_ADDR,
                              &timer_state->iomem);

  info_report("firmware=%s", machine->firmware);

  if (machine->firmware == NULL) {
    error_report("firmware is required");
    exit(1);
  }

  char *firmware_filename =
      qemu_find_file(QEMU_FILE_TYPE_BIOS, machine->firmware);

  if (!firmware_filename) {
    error_report("Could not find firmare file '%s'", firmware_filename);
    exit(1);
  }

  int image_size = load_image_mr(firmware_filename, ram);

  if (image_size < 0) {
    error_report("Could not load firmware image '%s'", firmware_filename);
    exit(1);
  }

  g_free(firmware_filename);
}

static void ipod_nano_1g_machine_init(MachineClass *mc) {
  info_report("ipod_nano_1g_machine_init");
  mc->desc = "iPod Nano 1G";
  mc->init = ipod_nano_1g_init;
  mc->min_cpus = 2;
  mc->max_cpus = 2;
  mc->default_cpus = 2;
  mc->default_ram_size = 32 * MiB;
  mc->default_cpu_type = ARM_CPU_TYPE_NAME("arm926");
}

DEFINE_MACHINE(IPOD_NANO_1G_NAME, ipod_nano_1g_machine_init)
