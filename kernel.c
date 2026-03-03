#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "vga.h"

void kmain(void) {
  vga_clear();
  gdt_init();
  idt_init();
  pic_init();
  __asm__ volatile("sti"); // enable interrupts AFTER PIC is ready
  vga_print("Hello from equil kernel\n");

  // make the kernel alive halt, wake on interrupt, repeat
  while (1) {
    __asm__ volatile("hlt");
  }
}
