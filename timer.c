#include "timer.h"
#include "port.h"

#define PIT_FREQ 1193180
#define TARGET_HZ 100
#define DIVISOR (PIT_FREQ / TARGET_HZ)

static unsigned int ticks = 0;

void timer_handler(void) {
  ticks++;
  outb(0x20, 0x20); // EOI to PIC
}

unsigned int timer_get_ticks(void) { return ticks; }

void timer_init(void) {
  unsigned short div = DIVISOR;

  outb(0x43, 0x36); // channel 0, lobyte/hibyte, rate generator
  outb(0x40, (unsigned char)(div & 0xFF));        // low byte
  outb(0x40, (unsigned char)((div >> 8) & 0xFF)); // high byte
}
