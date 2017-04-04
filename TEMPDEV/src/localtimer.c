/*
 * Authors : Alexandre "Dargor" Meunier
 * Descriptions : Function for BCM 2836-7 local timer management
 */

#include "localtimer.h"

void local_timer_set_routing(int mode)
{
    LT_SET_REG(LT_IRQ_ROUTING_REG, mode);
}

void local_timer_reset()
{
    LT_SET_REG(LT_RESET_REG, LT_RESET_IRQ);
}

void local_timer_reload(void)
{
	LT_SET_REG(LT_RESET_REG, LT_RELOAD);
}

void local_timer_change_counter(int value)
{
	int reg = LT_GET_REG(LT_CONTROL_REG);
	reg &= 0xF0000000;
	reg |= value;
	LT_SET_REG(LT_CONTROL_REG, reg);
}

void local_timer_init(int reload)
{
    LT_SET_REG(LT_CONTROL_REG, LT_ENABLE_IRQ | LT_ENABLE | reload);
    local_timer_reset();
}

int local_timer_interrupt(void)
{
    return (LT_GET_REG(LT_CONTROL_REG) << LT_IRQ) & 1;
}
