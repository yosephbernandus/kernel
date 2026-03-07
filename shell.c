#include "shell.h"
#include "vga.h"

static char buffer[SHELL_BUFFER_SIZE];
static unsigned int buf_len = 0;

static void shell_prompt(void) { vga_print("> "); }

static void shell_execute(void) {
  // TODO
}

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
