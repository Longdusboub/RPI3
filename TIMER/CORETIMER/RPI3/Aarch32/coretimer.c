/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for raspberry pi 3 core timer.
 */

#include "coretimer.h"

#define APB 2
#define CRY 1

int ct_set_increment(int inc)
{
    if (inc == 1)
	*(int *)CT_CTRL_REG &= 0xFFFFFDFF;
    else if (inc == 2)
	*(int *)CT_CTRL_REG |= 0x200;
    else
	return -1;
    return 1;
}

int ct_set_source(int src)
{
    if (src == APB)
	*(int *)CT_CTRL_REG &= 0xFFFFFEFF;
    else if (src == CRY)
	*(int *)CT_CTRL_REG |= 0x100;
    else
	return -1;
    return 1;
}

int ct_set_prescaler(int prescaler)
{
	if (prescaler < 0)
	    return -1;
	else
	    *(int *)CT_PRES_REG = prescaler;
	return 1;
}

int ct_set_ctrl_reg(int core, int mode)
{
    if (core < 0 || core > 3 || mode < 0 || mode > 7)
	return -1;
    *(int *)GET_CT_INT_CTRL(core) |= (1 << mode);
    return 1;
}

int ct_clr_ctrl_reg(int core, int mode)
{
    if (core < 0 || core > 3 ||mode < 0 || mode > 7)
	return -1;
    *(int *)GET_CT_INT_CTRL(core) &= ~(1 << mode);
    return 1;
}

int ct_init_timer(int value)
{
    if (value < 0)
	return -1;
    asm("mov r4, %[in]"::[in]"r"(value));
    asm("mov r5, #0x1");
    asm("MCR p15, 0, r4, c14, c2, 0");
    asm("MCR p15, 0, r5, c14, c2, 1");
    return 1;
}
