#ifndef QEMU_ARM_IPOD_NANO_1G_H
#define QEMU_ARM_IPOD_NANO_1G_H

// TODO: order matters.
#include "qemu/osdep.h"

#include "cpu.h"
#include "hw/arm/boot.h"
#include "hw/boards.h"
#include "exec/hwaddr.h"
#include "qemu/notify.h"
#include "hw/boards.h"
#include "hw/arm/boot.h"
#include "hw/arm/bsa.h"
#include "hw/block/flash.h"
#include "system/kvm.h"
#include "hw/intc/arm_gicv3_common.h"
#include "qom/object.h"

#define TYPE_IPOD_NANO_1G_MACHINE MACHINE_TYPE_NAME("ipod-nano-1g")

OBJECT_DECLARE_TYPE(IPodNano1GMachineState, IPodNano1GMachineClass,
    IPOD_NANO_1G_MACHINE)

struct IPodNano1GMachineClass {
  MachineClass parent;
};

struct IPodNano1GMachineState {
  MachineState parent;
  ARMCPU *cpu;
  char firmware_path[1024];
};

#endif
