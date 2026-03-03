global keyboard_isr
extern keyboard_handler

keyboard_isr:
  pusha       ; save all regisers
  call keyboard_handler
  popa        ; restore all registers
  iret        ; return from interrupt

