#include "shell.h"
#include "kprintf.h"
#include "timer.h"
#include "vga.h"

static char buffer[SHELL_BUFFER_SIZE];
static unsigned int buf_len = 0;

static void shell_prompt(void) { vga_print("> "); }

static int kstrcmp(const char *a, const char *b) {
  while (*a && *b && *a == *b) {
    a++;
    b++;
  }
  return *a - *b;
}

static int kstrncmp(const char *a, const char *b, unsigned int n) {
  while (n-- && *a && *b && *a == *b) {
    a++;
    b++;
  }
  return n == (unsigned int)-1 ? 0 : *a - *b;
}

static unsigned int kstrlen(const char *s) {
  unsigned int len = 0;
  while (s[len])
    len++;
  return len;
}

static void print_number(unsigned int n) {
  char buf[10];
  int i = 0;

  if (n == 0) {
    vga_putchar('0');
    return;
  }

  while (n > 0) {
    buf[i++] = '0' + (n % 10);
    n /= 10;
  }

  while (i > 0) {
    vga_putchar(buf[--i]);
  }
}

static void shell_execute(void) {
  if (buf_len == 0)
    return;

  if (kstrcmp(buffer, "uptime") == 0) {
    kprintf("%d seconds\n", timer_get_ticks() / 100);
    return;
  }

  if (kstrcmp(buffer, "clear") == 0) {
    vga_clear();
    return;
  }

  if (kstrcmp(buffer, "help") == 0) {
    vga_print("Commands:\n");
    vga_print("  clear  - clear the screen\n");
    vga_print("  help   - show this message\n");
    vga_print("  echo   - print text\n");
    return;
  }

  if (kstrncmp(buffer, "echo ", 5) == 0) {
    vga_print(buffer + 5);
    vga_putchar('\n');
    return;
  }

  vga_print("Unknown command: ");
  vga_print(buffer);
  vga_putchar('\n');
}

void shell_init(void) { shell_prompt(); }

void shell_handle_key(char c) {
  if (c == '\b') {
    if (buf_len > 0) {
      buf_len--;
      vga_putchar('\b');
    }
    return;
  }

  if (c == '\n') {
    buffer[buf_len] = '\0';
    vga_putchar('\n');
    shell_execute();
    buf_len = 0;
    shell_prompt();
    return;
  }

  if (buf_len < SHELL_BUFFER_SIZE - 1) {
    buffer[buf_len++] = c;
    vga_putchar(c);
  }
}
