/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for raspberry pi 3 core timer.
 */

#include "coretimer.h"

int ct_set_increment(int inc)
{
    if (inc == 1)
	*(int *)CT_CTRL_REG &= 0xFFFFFDFF;
    else if (inc == 2)
	*(int *)CT_CTRL_REG |= 0x200;
    return 1;
}

int ct_set_source(int src)
{
    if (src == APB)
	*(int *)CT_CTRL_REG |= 0x300;
    else if (src == CRY)
	*(int *)CT_CTRL_REG &= 0x00;
    return 1;
}

int ct_set_prescaler(int prescaler)
{
	*(int *)CT_PRES_REG = prescaler;
	return 1;
}

int ct_set_ctrl_reg(int core, int mode)
{
    *(int *)GET_CT_INT_CTRL(core) |= mode;
    return 1;
}

int ct_clr_ctrl_reg(int core, int mode)
{
    *(int *)GET_CT_INT_CTRL(core) &= ~(mode);
    return 1;
}

int ct_init_timer(int value)
{
    /*asm("mov r1, #0x4B00");*/
    //asm("mul r0, r0, r1");
    asm("mov r5, #0x1");
    asm("MCR p15, 0, r0, c14, c2, 0");
    asm("MCR p15, 0, r5, c14, c2, 1");
    return 1;
}
