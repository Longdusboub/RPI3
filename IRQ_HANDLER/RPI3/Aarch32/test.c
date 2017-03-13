/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple jtag init for raspberry pi 3
 */

#include "gpio.c"
#include "coretimer.c"
#include "interrupt.c"
#include "localtimer.c"

void switchLED(void)
{
	ct_init_timer(0x8FFF);
	if (gpio_get_level(21) == 1)
		gpio_set_low(21);
	else
		gpio_set_high(21);
}

void switchOtherLED(void)
{
	local_timer_reset(0x038FFFF);
	static int level = 1;
	if (level == 1)
		gpio_set_low(6);
	else
		gpio_set_high(6);
	level = (level + 1) % 2;
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
	//Set up GPIO for interrupt handler
	gpio_set_mode(6, GPIO_FUNCTION_OUT);
	gpio_set_mode(21, GPIO_FUNCTION_OUT);

	//Add handler for bot interrupt
	add_handler(switchOtherLED, 11);
	add_handler(switchLED, 1);

	//Initialise both timer
	local_timer_set_routing(0);
	local_timer_init(0x0FFFFFF);
	ct_init_timer(0x8FFF);
	ct_set_increment(1);
	ct_set_source(CRY);
	ct_set_prescaler(0x000FFFFF);
	ct_set_ctrl_reg(0, CT_IRQ_CPNS);

	return(0);
}


