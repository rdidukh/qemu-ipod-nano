#include "hw/arm/ipod_nano_1g.h"

// #include "hw/arm/boot.h"

static void ipod_nano_1g_init(MachineState *machine) {
  // IPodNano1GMachineState *state = IPOD_NANO_1G_MACHINE(machine);
}

static void ipod_nano_1g_machine_init(MachineClass *mc) {
  mc->desc = "iPod Nano 1G";
  mc->init = ipod_nano_1g_init;
  mc->min_cpus = 2;
  mc->max_cpus = 2;
  mc->default_cpus = 2;
  mc->default_cpu_type = ARM_CPU_TYPE_NAME("arm926");
}

DEFINE_MACHINE("ipod-nano-1g", ipod_nano_1g_machine_init)
