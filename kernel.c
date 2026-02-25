void kmain(void) {
  const char *str = "Kernel learning equil";
  char *vidptr = (char *)0xb8000;
  unsigned int i = 0;
  unsigned int j = 0;

  // mode text vga 1 Char 2 byte memory
  // ascii character k = 0x40
  // 1. genap / ganjil index
  // 2. index + 1
  // attribute color letter and background
  // example display 80 and need 25 char 80 x 25 x 2 = 4000 byte

  while (j < 80 * 25 * 2) {
    vidptr[j] = ' '; // posisi char with space ascii 32
    vidptr[j + 1] =
        0x07; // set color 0000 -> hitam(bg) 0111 -> abu-abu (foreground)
    j = j + 2;
  }

  j = 0;
  while (str[j] != '\0') {
    // take first letter
    vidptr[i] = str[j];
    vidptr[i + 1] = 0x07;
    ++j;
    i = i + 2;
  }

  return;
}
