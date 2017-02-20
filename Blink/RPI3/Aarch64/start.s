

.globl _start
_start:
    mov sp,#0x8000
    bl main
hang: b hang

.globl PUTREG
PUTREG:
  str w1,[x0]
  ret

.globl GETREG
GETREG:
    ldr w0,[x0]
    ret
