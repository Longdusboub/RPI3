

.globl _start
_start:
    mov sp,#0x8000
    bl main
hang: b hang

.globl PUTREG
PUTREG:
  str r1,[r0]
  bx lr

.globl GETREG
GETREG:
    ldr r0,[r0]
    bx lr
