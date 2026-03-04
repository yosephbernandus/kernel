#include "keyboard.h"
#include "port.h"
#include "shell.h"

// US Keyboard scan code -> ASCII
static const char scancode_to_ascii[128] = {
    0,   0,   '1',  '2', '3',  '4', '5', '6',  '7', '8', '9', '0',
    '-', '=', '\b', 0,   'q',  'w', 'e', 'r',  't', 'y', 'u', 'i',
    'o', 'p', '[',  ']', '\n', 0,   'a', 's',  'd', 'f', 'g', 'h',
    'j', 'k', 'l',  ';', '\'', '`', 0,   '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm',  ',', '.',  '/', 0,   '*',  0,   ' '};

void keyboard_handler(void) {
  unsigned char scancode = inb(0x60);

  // only handle key press (bit 7 = 0), ignore key release (bit 7 = 1)
  if (scancode & 0x80) {
    // Send End of Interrupt to PIC
    outb(0x20, 0x20);
    return;
  }

  char c = scancode_to_ascii[scancode];
  if (c != 0) {
    shell_handle_key(c);
  }

  // Send End of Interrupt (EOI) to master PIC
  outb(0x20, 0x20);
}
