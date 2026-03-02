#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xb8000
#define VGA_COLS 80
#define VGA_ROWS 25
#define VGA_DEFAULT_COLOR 0x07

void vga_clear(void);
void vga_putchar(char c);
void vga_print(const char * str);

#endif
