#ifndef IDT_H
#define IDT_H

struct idt_entry {
	unsigned short offset_low; // bits 0-15 of handler address
	unsigned short selector; // GDT code segment selector
	unsigned char zero; // always 0
	unsigned char type_attr; // type and attributes
	unsigned short offset_high; // bits 16-31 of handler address
} __attribute__((packed));

struct idt_descriptor {
	unsigned short size;
	unsigned int offset;
} __attribute__((packed));

void idt_init(void);
void idt_set_entry(int index, unsigned int handler, unsigned short selector, unsigned char type_attr);

#endif
