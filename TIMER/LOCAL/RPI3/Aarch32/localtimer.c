/*
 * Authors : Alexandre "Dargor" Meunier
 * Descriptions : Function for BCM 2836-7 local timer management
 */

#include "localtimer.h"

int local_timer_set_routing(int mode)
{
    if(mode < 0 || mode > 8)
	return -1;
    LT_ROUTING_IRQ(mode);
    return 1;
}

/* 0 = Reset interrupt flags
   1 = Reload timer
   2 = Reset and reload */

int local_timer_reset(int mode)
{
    if (mode < 0 || mode > 2)
	return -1;
    mode == 0 ? LT_RESET_FLAGS : mode == 1 ? LT_RELOAD_TIMER : LT_RESET_ALL;
    return 1;
}

int local_timer_init(int reload)
{
    LT_ENABLE_IRQ;
    LT_ENABLE;
    LT_CLR_RELOAD;
    LT_SET_RELOAD(reload);
    return 1;
}

int local_timer_interrupt(void)
{
    return INT_LT_CONTROL;
}
