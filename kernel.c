#include "gdt.h"
#include "idt.h"
#include "vga.h"

void kmain(void) {
  vga_clear();
  gdt_init();
  idt_init();
  vga_print("Hello from equil kernel\n");
}
