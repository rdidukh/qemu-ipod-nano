#include "hw/arm/ipod_nano_1g.h"

#include "exec/address-spaces.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "qemu/units.h"

// TODO: init second CPU.
static void ipod_nano_1g_init(MachineState *machine) {
  info_report("ipod_nano_1g_init");

  IPodNano1GMachineState *state = IPOD_NANO_1G_MACHINE(machine);

  Object *cpuobj;
  ARMCPU *armcpu;

  cpuobj = object_new(machine->cpu_type);
  armcpu = ARM_CPU(cpuobj);

  state->cpu = armcpu;

  if (!qdev_realize(DEVICE(armcpu), NULL, &error_abort)) {
    return;
  }

  object_unref(cpuobj);

  MemoryRegion *sec = g_new(MemoryRegion, 1);
  memory_region_init_ram(sec, NULL, "ram", machine->ram_size, &error_fatal);
  memory_region_add_subregion(get_system_memory(), 0x0, sec);
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
