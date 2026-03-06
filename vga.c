#include "vga.h"
#include "port.h"

static unsigned int row = 0;
static unsigned int col = 0;
static char color = VGA_DEFAULT_COLOR;
static char *vidptr = (char *)VGA_ADDRESS;

static void vga_update_cursor(void) {
  unsigned short pos = row * VGA_COLS + col;
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char)(pos & 0xFF));
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void vga_clear(void) {
  unsigned int i = 0;
  while (i < VGA_ROWS * VGA_COLS * 2) {
    vidptr[i] = ' ';
    vidptr[i + 1] = color;
    i += 2;
  }
  row = 0;
  col = 0;
  vga_update_cursor();
}

void vga_putchar(char c) {
  if (c == '\n') {
    row++;
    col = 0;
    vga_update_cursor();
    return;
  }

  if (c == '\b') {
    if (col > 0) {
      col--;
    } else if (row > 0) {
      row--;
      col = VGA_COLS - 1;
    }

    unsigned int offset = (row * VGA_COLS + col) * 2;
    vidptr[offset] = ' ';
    vidptr[offset + 1] = color;
    vga_update_cursor();
    return;
  }

  unsigned int offset = (row * VGA_COLS + col) * 2;
  vidptr[offset] = c;
  vidptr[offset + 1] = color;
  col++;

  if (col >= VGA_COLS) {
    col = 0;
    row++;
  }
  vga_update_cursor();
}

void vga_print(const char *str) {
  unsigned int i = 0;
  while (str[i] != '\0') {
    vga_putchar(str[i]);
    i++;
  }
}
