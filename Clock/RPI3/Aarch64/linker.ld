OUTPUT_ARCH(arm)

MEMORY
{
	/* Trusted BOOT ROM  */ boot_rom : org = 0x00000000, len = 0x00000100
	/* Trusted RAM */       ram      : org = 0x00008000, len = 0x00040000
}


SECTIONS
{
    .text :
    {
	. = ALIGN(4);
	*(.text*)
	. = ALIGN(4);
    } > ram

    .bss :
    {
	. = ALIGN(4);
	*(.bss*)
	. = ALIGN(4);
    } > ram
}

