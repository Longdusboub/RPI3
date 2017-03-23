.global _start
_start:
    MOV sp, #0x3000
    BL main
    /* Wait */
    B .
