#ifndef QEMU_ARM_IPOD_NANO_1G_H
#define QEMU_ARM_IPOD_NANO_1G_H

// Must be included before "hw/boards.h"
// clang-format off
#include "qemu/osdep.h"
// clang-format on
#include "cpu.h"
#include "hw/boards.h"
#include "qemu/units.h"

#define IPOD_NANO_1G_NAME "ipod-nano-1g"
#define TYPE_IPOD_NANO_1G_MACHINE MACHINE_TYPE_NAME(IPOD_NANO_1G_NAME)

#define IPOD_NANO_1G_RAM_BASE_ADDR 0x0

#define IPOD_NANO_1G_FASTRAM_BASE_ADDR 0x40000000
#define IPOD_NANO_1G_FASTRAM_SIZE 96 * KiB

#define PP5020_MEMORY_CONTROL_BASE_ADDR 0xf0000000
#define PP5020_MEMORY_CONTROL_MEM_SIZE 0x10000

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
