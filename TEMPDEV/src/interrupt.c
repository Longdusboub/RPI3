/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for interrupt sources register for raspberry pi 3
 */

#include "../include/interrupt.h"

int ct_int(int core, int inte)
{
	return (*(int *)IRQ_SRC_COREN(core) >> inte) & 1;
}

// ct_int(0,i) => Replace 0 by core ID
extern void interrupts_handler(void)
{
	for (int i = 0; i < 12; i++)
	{
		if (ct_int(0, i) == 1)
			(*interrupt_handler[i])();
	}
	return;
}

void add_handler(void (*hand)(void), int irqnum)
{
	interrupt_handler[irqnum] = hand;
}

void gpu_irq_handler(void)
{
		if (((*(int *)IRQ_BASIC_PENDING) >> 8) & 1)
			gpu_irq_1_handler();
		if (((*(int *)IRQ_BASIC_PENDING) >> 9) & 1)
			gpu_irq_2_handler();
}

void gpu_irq_1_handler(void)
{
	int i = 0;
	int reg = *(int *)IRQ_PENDING_1;
	for (i = 0; i < 32; i++)
	{
		if (reg & 1)
			(*gpu_interrupt_handler[i])();
		reg = reg >> 1;
	}
}

void gpu_irq_2_handler(void)
{
	int i = 0;
	int reg = *(int *)IRQ_PENDING_2;
	for (i = 0; i < 32; i++)
	{
		if (reg & 1)
			(*gpu_interrupt_handler[i + 32])();
		reg = reg >> 1;
	}
}

void add_gpu_handler(void (*hand)(void), int irqnum)
{
	gpu_interrupt_handler[irqnum] = hand;
}

void enable_gpu_irq(int irqnum)
{
	int reg = IRQ_GET_REG(GET_ENABLE_REG(irqnum));
	reg |= (1 << (irqnum % 32));
	IRQ_SET_REG(GET_ENABLE_REG(irqnum), reg);
}
