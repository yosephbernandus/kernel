#include "vga.h"

void kmain(void) {
  vga_clear();
  vga_print("Hello from equil kernel\n");
}
