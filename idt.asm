global idt_load
global isr_default

idt_load:
  mov eax, [esp + 4]
  lidt [eax]
  sti       ; enable interrupts
  ret

isr_default:
  iret      ; return from interrupt, do nothing
