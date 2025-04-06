#ifndef QEMU_ARM_IPOD_NANO_1G_H
#define QEMU_ARM_IPOD_NANO_1G_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on
#include "cpu.h"
#include "hw/boards.h"

#define TYPE_IPOD_NANO_1G_MACHINE MACHINE_TYPE_NAME("ipod-nano-1g")

OBJECT_DECLARE_TYPE(IPodNano1GMachineState, IPodNano1GMachineClass,
                    IPOD_NANO_1G_MACHINE)

struct IPodNano1GMachineClass {
  MachineClass parent;
};

struct IPodNano1GMachineState {
  MachineState parent;
  ARMCPU *cpu;
};

#endif
