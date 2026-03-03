#include "pic.h"
#include "port.h"

void pic_init(void) {
  // ICW1: start initialization sequence
  outb(0x20, 0x11); // master command
  outb(0xA0, 0x11); // slave command

  // ICW2: set interrupt offset
  outb(0x21, 0x20); // master: IRQ 0-7 -> INT 32-39
  outb(0xA1, 0x28); // slave: IRQ 8-15 -> INT 40-47

  // ICW3: tell PICs about each other
  outb(0x21, 0x04); // master: slave is on IRQ 2 (bit2 2)
  outb(0xA1, 0x02); // slave: connected to master IRQ 2

  // ICW4: 8086 mode
  outb(0x21, 0x01);
  outb(0xA1, 0x01);

  // Mask all IRQs except IRQ 1 (keyboard)
  outb(0x21, 0xFD); // 1111 1101 - only IRQ 1 enabled
  outb(0xA1, 0xFF); // all slave IRQs disabled
}
