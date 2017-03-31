/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for raspberry pi 3 armv7 MMU
 */

#include "../include/mmu.h"


void mmu_add_page(unsigned int vaddr, unsigned int paddr, int flags)
{
	/* table entry = vaddr >> 18 */
	asm("LSR r0, #0x12");
	/* table entry += 0x4000(MMU_BASE_ADDR ) */
	asm("add r0, r0, #0x4000");
	/* paddr = paddr + flags */
	asm("orr r1, r2, r1");
	/* table entry register = paddr + flags */
	asm("str r1, [r0, #0]");
	//TODO : Modify to handle all paddr not only 1 => 1 mapping
}

void set_mmu(void)
{
	int i = 0;
	int vaddr = 0;
	int flags = AP_RW_NA;
	for (i = 0; i < 4096; i++)
	{
		vaddr = i << 20;
		if (i > 1007 && i < 1025)
			mmu_add_page(vaddr, vaddr, AP_RW_NA | 0x2 | MRT_SHA_DEV);
		else if (i == 2)
			mmu_add_page(vaddr, vaddr, flags | 0x2 | DOMAINS(2));
/*		else if (i > 943 && i < 1008)
			mmu_add_page(vaddr, vaddr, AP_NO_ACCESS | XN | DOMAINS(1)); //GPU MEMORY
		*/else
			mmu_add_page(vaddr, vaddr, flags | 0x2);
	}
}

void set_domain_permission(int domain, int flags)
{
	asm("mrc p15, 0, r2, c3, c0, 0");
	/* Read the current domain permission register */
	asm("add r3, r0, r0");
	/* r3 = 2 * domain */
	asm("lsl r1, r3");
	/* flags << r3 (2 * domain) */
	asm("mov r4, #0x3");
	asm("lsl r4, r3");
	asm("mvn r4, r4");
	/* r4 = ~(0b11 << 2 * domain) */
	asm("and r2, r4");
	/* Clear current domain permissions bits */
	asm("orr r2, r1");
	/* Set current domain permissions bits */
	asm("mcr p15, 0, r2, c3, c0, 0");
	/* Set the domain permission register */
}



void enable_mmu(int flags)
{
	asm("dsb");
	asm("push {r0, lr}");
	asm("mov r0, #0x10");
	asm("loop:");
	asm("sub r0, #0x1");
	asm("mov r1, #0x3");
	asm("bl set_domain_permission");
	asm("cmp r0, #0x0");
	asm("bne loop");
	asm("pop {r0, lr}");
	/* Set domain permission to full access */
	asm("mov r1, #0x4000");
	asm("mcr p15, 0, r1, c2, c0, 0");
	asm("mcr p15, 0, r1, c2, c0, 1");
	asm("mrc p15, 0, r2, c1, c0, 0");
	asm("orr r2, r2, r0");
	asm("mcr p15, 0, r2, c1, c0, 0");
}

