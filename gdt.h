#ifndef GDT_H
#define GDT_H
struct gdt_entry {
	unsigned short limit_low; // bits 0-15 of limit
	unsigned short base_low; // bits 0-15 of base
	unsigned char base_mid; // bits 16-23 of base
	unsigned char access; // access byte
	unsigned char flags; // flags + limit high bits
	unsigned char base_high; // bits 24-31 of base
} __attribute__((packed));

struct gdt_descriptor {
	unsigned short size; // size of GDT minus 1
	unsigned int offset; // address of GDT
} __attribute__((packed));

void gdt_init(void);

#endif
