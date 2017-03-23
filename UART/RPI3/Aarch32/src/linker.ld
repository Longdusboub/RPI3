
MEMORY
{
	/* Trusted RAM */       ram      : org = 0x00008000, len = 0x00040000
}

ENTRY(_start)

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

