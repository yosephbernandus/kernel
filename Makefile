ASM     = nasm
CC      = gcc
LD      = ld

ASMFLAGS = -f elf32
CFLAGS   = -m32 -c -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS  = -m elf_i386 -T link.ld

OBJ = kasm.o kernel.o vga.o gdt.o gdt_asm.o idt.o idt_asm.o pic.o keyboard.o keyboard_asm.o shell.o

all: kernel

kasm.o: bootloader.asm
	$(ASM) $(ASMFLAGS) $< -o $@

kernel.o: kernel.c
	$(CC) $(CFLAGS) $< -o $@

kernel: $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

vga.o: vga.c
	$(CC) $(CFLAGS) $< -o $@

gdt_asm.o: gdt.asm
	$(ASM) $(ASMFLAGS) $< -o $@

gdt.o: gdt.c
	$(CC) $(CFLAGS) $< -o $@

idt.o: idt.c
	$(CC) $(CFLAGS) $< -o $@

idt_asm.o: idt.asm
	$(ASM) $(ASMFLAGS) $< -o $@

pic.o: pic.c
	$(CC) $(CFLAGS) $< -o $@

keyboard.o: keyboard.c
	$(CC) $(CFLAGS) $< -o $@

keyboard_asm.o: keyboard_asm.asm
	$(ASM) $(ASMFLAGS) $< -o $@

shell.o: shell.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) kernel

.PHONY: all clean
