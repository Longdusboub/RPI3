/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for raspberry pi 3 armv7 MMU
 */

#include "mmu.h"

/*void add_mmu_section(int paddr, int vaddr, int flags)
{
	int taddr = MMU_BASE | (vaddr >> 18) & 0xFFFFFFFC;
	*(int *)taddr = (paddr & 0x3000) | (flags) |0x2;
}*/

void set_mmu(void)
{
	int i = 0;
	int vaddr = 0;
	int flags = 1 << 10;
	for (i = 0; i < 4096; i++)
	{
		vaddr = i << 20;
		*(int *)(MMU_BASE + (i << 2)) = vaddr|flags|0x2;
	}
}

void enable_mmu(int addr, int lol)
{
	//TODO : Invalidate cache/TBL
	//asm("b .");
	asm("dsb");
	asm("mcr p15, 0, r0, c2, c0, 0");
	asm("mcr p15, 0, r0, c2, c0, 1");
	asm("mrc p15, 0, r2, c1, c0, 0");
	asm("orr r2, r2, r1");
	asm("mcr p15, 0, r2, c1, c0, 0");

	//Enable MMU
	//SHitsorm
}
