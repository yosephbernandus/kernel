#include "gdt.h"

static struct gdt_entry gdt[3];
static struct gdt_descriptor gdt_desc;
extern void gdt_load(struct gdt_descriptor *desc);

static void gdt_set_entry(int index, unsigned int base, unsigned int limit,
                          unsigned char access, unsigned char flags) {
  gdt[index].base_low = base & 0xFFFF;
  gdt[index].base_mid = (base >> 16) & 0xFF;
  gdt[index].base_high = (base >> 24) & 0xFF;
  gdt[index].limit_low = limit & 0xFFFF;
  gdt[index].flags = ((limit >> 16) & 0x0F) | (flags & 0xF0);

  gdt[index].access = access;
}

void gdt_init(void) {
  gdt_set_entry(0, 0, 0, 0, 0);                // null descriptor
  gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code segment
  gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data segment

  gdt_desc.size = sizeof(gdt) - 1;
  gdt_desc.offset = (unsigned int)&gdt;

  gdt_load(&gdt_desc);
}
