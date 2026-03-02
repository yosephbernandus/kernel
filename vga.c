#include "vga.h"

static unsigned int row = 0;
static unsigned int col = 0;
static char color = VGA_DEFAULT_COLOR;
static char *vidptr = (char *)VGA_ADDRESS;

void vga_clear(void) {
  unsigned int i = 0;
  while (i < VGA_ROWS * VGA_COLS * 2) {
    vidptr[i] = ' ';
    vidptr[i + 1] = color;
    i += 2;
  }
  row = 0;
  col = 0;
}

void vga_putchar(char c) {
  if (c == '\n') {
    row++;
    col = 0;
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
}

void vga_print(const char *str) {
  unsigned int i = 0;
  while (str[i] != '\0') {
    vga_putchar(str[i]);
    i++;
  }
}
