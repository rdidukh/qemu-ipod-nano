#include "hw/arm/ipod_nano_1g.h"

#include "exec/address-spaces.h"
#include "hw/loader.h"
#include "qapi/error.h"
#include "qemu/datadir.h"
#include "qemu/error-report.h"
#include "qemu/units.h"

// TODO: init second CPU.
static void ipod_nano_1g_init(MachineState *machine) {
  info_report("ipod_nano_1g_init");

  IPodNano1GMachineState *state = IPOD_NANO_1G_MACHINE(machine);

  Object *cpuobj = object_new(machine->cpu_type);
  ARMCPU *armcpu = ARM_CPU(cpuobj);

  state->cpu = armcpu;

  if (!qdev_realize(DEVICE(armcpu), NULL, &error_abort)) {
    return;
  }

  object_unref(cpuobj);

  MemoryRegion *ram = g_new(MemoryRegion, 1);
  memory_region_init_ram(ram, NULL, "ram", machine->ram_size, &error_fatal);
  memory_region_add_subregion(get_system_memory(), 0x0, ram);

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
  mc->default_ram_size = 32 * MiB;
  mc->default_cpus = 2;
  mc->default_cpu_type = ARM_CPU_TYPE_NAME("arm926");
}

DEFINE_MACHINE("ipod-nano-1g", ipod_nano_1g_machine_init)
