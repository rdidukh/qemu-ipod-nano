#include "hw/arm/hd66789r-lcd.h"

#include "cpu.h"
#include "qemu/error-report.h"

static uint64_t hd66789r_lcd_read(void *opaque, hwaddr addr, unsigned size) {
  info_report("hd66789r_lcd_read: addr=0x%lx, callee=%d, pc=0x%lx", addr,
              current_cpu->cpu_index, current_cpu->cc->get_pc(current_cpu));
  // TODO: Hd66789rLcdState *state = HD66789R_LCD(opaque);

  switch (addr) {
    case HD66789R_LCD_PORT_OFFSET:
      // 0x8000_0000 - busy.
      return 0;
    default:
  }

  assert(false);
}

static void hd66789r_lcd_write(void *opaque, hwaddr addr, uint64_t data,
                               unsigned size) {
  info_report("hd66789r_lcd_write: addr=0x%lx, data=0x%lx callee=%d, pc=0x%lx",
              addr, data, current_cpu->cpu_index,
              current_cpu->cc->get_pc(current_cpu));

  Hd66789rLcdState *state = HD66789R_LCD(opaque);

  switch (addr) {
    case HD66789R_LCD_PORT_OFFSET:
      // TODO: trigger actual commands.
      if ((data & HD66789R_LCD_DATA_MASK) == HD66789R_LCD_DATA_MASK) {
        state->data = (state->data << 8) | (data & 0xff);
      } else if ((data & HD66789R_LCD_CMD_MASK) != 0) {
        uint32_t command = data & 0xff;
        if (command == 0) {
          state->command = 0;
          state->data = 0;
        } else {
          state->command = (state->command << 8) | command;
        }
      } else {
        assert(false);
      }
      return;
    default:
  }

  assert(false);
}

static const MemoryRegionOps hd66789r_lcd_ops = {
    .read = hd66789r_lcd_read,
    .write = hd66789r_lcd_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void hd66789r_lcd_init(Object *obj) {
  Hd66789rLcdState *state = HD66789R_LCD(obj);

  SysBusDevice *sbd = SYS_BUS_DEVICE(obj);

  memory_region_init_io(&state->iomem, obj, &hd66789r_lcd_ops, state,
                        TYPE_HD66789R_LCD, HD66789R_LCD_MEM_SIZE);
  sysbus_init_mmio(sbd, &state->iomem);
}

static void hd66789r_lcd_class_init(ObjectClass *klass, void *data) {}

static const TypeInfo hd66789r_lcd_type_info = {
    .name = TYPE_HD66789R_LCD,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(Hd66789rLcdState),
    .instance_init = hd66789r_lcd_init,
    .class_init = hd66789r_lcd_class_init,
};

static void hd66789r_lcd_register_types(void) {
  type_register_static(&hd66789r_lcd_type_info);
}

type_init(hd66789r_lcd_register_types)
