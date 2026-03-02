global gdt_load

gdt_load:
  mov eax, [esp + 4]  ; get pointer to gdt_descriptor from stack
  lgdt [eax]  ; load GDT

  ; reload segment registers with data segment selector (index 2 = offset 0x10)
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax

  ; reload code segment with a far jump (index 1 = offset 0x08)
  jmp 0x08:.flush

.flush:
  ret
