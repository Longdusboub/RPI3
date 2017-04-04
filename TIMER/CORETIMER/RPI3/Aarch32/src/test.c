/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple jtag init for raspberry pi 3
 */

#include "gpio.c"
#include "coretimer.c"

#define IRQ_CORE_0  0x40000060

void switchForEver(void)
{
	ct_init_timer(1000 * CT_MS_1);
	if (gpio_get_level(12) == 1)
		gpio_set_low(12);
	else
		gpio_set_high(12);
}

void init_jtag(void)
{
	gpio_set_mode(4, GPIO_FUNCTION_ALT5);
	gpio_set_mode(22, GPIO_FUNCTION_ALT4);
	gpio_set_mode(23, GPIO_FUNCTION_ALT4);
	gpio_set_mode(24, GPIO_FUNCTION_ALT4);
	gpio_set_mode(25, GPIO_FUNCTION_ALT4);
	gpio_set_mode(27, GPIO_FUNCTION_ALT4);
}

int main(void)
{
	gpio_set_mode(12, GPIO_FUNCTION_OUT);
	ct_set_increment(1);
	ct_set_source(CRY);
	ct_set_prescaler(CT_PRESCALER_1);
	ct_set_ctrl_reg(0, CT_IRQ_CPS);
	ct_init_timer(1000 * CT_MS_1);
	while (1)
		if (((*(int *)IRQ_CORE_0) & 1) == 1)
			switchForEver();
	return(0);
}

