#include "kprintf.h"
#include "vga.h"

static void print_number(int n) {
  char buf[12];
  int i = 0;
  int negative = 0;

  if (n == 0) {
    vga_putchar('0');
    return;
  }

  if (n < 0) {
    negative = 1;
    n = -n;
  }

  while (n > 0) {
    buf[i++] = '0' + (n % 10);
    n /= 10;
  }

  if (negative)
    vga_putchar('-');

  while (i > 0) {
    vga_putchar(buf[--i]);
  }
}

static void print_hex(unsigned int n) {
  char buf[8];
  int i = 0;
  char hex_chars[] = "0123456789abcdef";

  if (n == 0) {
    vga_putchar('0');
    return;
  }

  while (n > 0) {
    buf[i++] = hex_chars[n & 0xF];
    n >>= 4;
  }

  while (i > 0) {
    vga_putchar(buf[--i]);
  }
}

void kprintf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  while (*fmt) {
    if (*fmt == '%' && *(fmt + 1)) {
      fmt++;
      switch (*fmt) {
      case 's':
        vga_print(va_arg(args, const char *));
        break;
      case 'd':
        print_number(va_arg(args, int));
        break;
      case 'x':
        print_hex(va_arg(args, unsigned int));
        break;
      case '%':
        vga_putchar('%');
        break;
      default:
        vga_putchar('%');
        vga_putchar(*fmt);
        break;
      }
    } else {
      vga_putchar(*fmt);
    }
    fmt++;
  }

  va_end(args);
}
