#include "idt.h"
#define IDT_ENTRIES 256

static struct idt_entry idt[IDT_ENTRIES];
static struct idt_descriptor idt_desc;

void idt_set_entry(int index, unsigned int handler, unsigned short selector,
                   unsigned char type_attr) {
  idt[index].offset_low = handler & 0xFFFF;
  idt[index].offset_high = (handler >> 16) & 0xFFFF;
  idt[index].selector = selector;
  idt[index].zero = 0;
  idt[index].type_attr = type_attr;
}

extern void idt_load(struct idt_descriptor *desc);
extern void isr_default(void);

void idt_init(void) {
  unsigned int i;
  for (i = 0; i < IDT_ENTRIES; i++) {
    idt_set_entry(i, (unsigned int)isr_default, 0x08, 0x8E);
  }

  idt_desc.size = sizeof(idt) - 1;
  idt_desc.offset = (unsigned int)&idt;

  idt_load(&idt_desc);
}
