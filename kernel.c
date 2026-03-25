#include "gdt.h"
#include "idt.h"
#include "kprintf.h"
#include "pic.h"
#include "shell.h"
#include "timer.h"
#include "vga.h"

void kmain(unsigned int *mboot_info) {
  vga_clear();
  gdt_init();
  idt_init();
  pic_init();
  timer_init();
  __asm__ volatile("sti"); // enable interrupts AFTER PIC is ready
  kprintf("Memory map at: 0x%x\n", (unsigned int)mboot_info);
  vga_print("Hello from equil kernel\n");
  shell_init();

  // make the kernel alive halt, wake on interrupt, repeat
  while (1) {
    __asm__ volatile("hlt");
  }
}
