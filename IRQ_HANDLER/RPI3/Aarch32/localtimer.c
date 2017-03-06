/*
 * Authors : Alexandre "Dargor" Meunier
 * Descriptions : Function for BCM 2836-7 local timer management
 */

#include "localtimer.h"

void local_timer_set_routing(int mode)
{
    LT_ROUTING_IRQ(mode);
}

void local_timer_reset(int reload)
{
    LT_DISABLE;
    LT_DISABLE_IRQ;
    LT_RESET_FLAGS;
    LT_ENABLE;
    LT_ENABLE_IRQ;
    LT_SET_RELOAD(reload);
}

void local_timer_init(int reload)
{
    LT_ENABLE_IRQ;
    LT_ENABLE;
    LT_CLR_RELOAD;
    LT_SET_RELOAD(reload);
}

int local_timer_interrupt(void)
{
    return INT_LT_CONTROL;
}
