/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for interrupt sources register for raspberry pi 3
 */

#define INT_SRC_CORE0	0x40000060
#define INT_SRC_CORE1	0x40000064
#define INT_SRC_CORE2	0x40000068
#define INT_SRC_CORE3	0x4000006C

#define IRQ_PER(X)  (11 + X)
#define IRQ_LC	    (11)
#define IRQ_AXI	    (10)
#define IRQ_PMU	    (9)
#define IRQ_GPU	    (8)
#define IRQ_MB3	    (7)
#define IRQ_MB2	    (6)
#define IRQ_MB1	    (5)
#define IRQ_MB0	    (4)
#define IRQ_CV	    (3)
#define IRQ_CHP	    (2)
#define IRQ_CPNS    (1)
#define IRQ_CPS	    (0)

#define INT_SRC_COREN(X)    ((X == 0) ? INT_SRC_CORE0 : (X == 1) ? INT_SRC_CORE1 : (X == 2) ? INT_SRC_CORE2 : INT_SRC_CORE3)

void (*interrupt_handler[16])();


int ct_int(int core, int inte)
{
    return (*(int *)INT_SRC_CORE0 >> inte) & 1;
}

int get_irq_num(int core)
{
    int i = 0;
    while (i < 12)
    {
	if (ct_int(0, i) == 1)
		return i;
	i++;
    }
    return -1;
}

extern void interrupts_handler(void)
{
    int irq_num = get_irq_num(0);
    if (irq_num > 0)
	(*interrupt_handler[irq_num])();
}

void add_handler(void (*hand)(void), int irqnum)
{
    interrupt_handler[irqnum] = hand;
}
