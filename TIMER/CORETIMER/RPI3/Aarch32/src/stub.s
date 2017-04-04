.global _start
_start:
    MRC p15, 0, r0, c0, c0, 5
    AND r0, #0x000F
    CMP r0, #0x0
    BEQ master_boot
    B	slave_boot

slave_boot:
    B .

master_boot:
    /* Set up stack pointer and jtag */
    MOV sp, #0x3000
    BL main
    B .
