#include "gdt.h"
#include "vga.h"

void kmain(void) {
  vga_clear();
  gdt_init();
  vga_print("Hello from equil kernel\n");
}
