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
    asm("mov x4, %[in]"::[in]"r"(value));
    asm("mov x5, #0x1");
    asm("MSR CNTP_CTL_EL0, x5");
    asm("MSR CNTP_TVAL_EL0, x4");
    return 1;
}
