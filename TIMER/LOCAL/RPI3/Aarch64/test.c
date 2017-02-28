/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple local timer init and test for raspberry pi 3
 */

#include "gpio.c"
#include "localtimer.c"

void switchLED(void)
{
	if (gpio_get_level(21) == 1)
		gpio_set_low(21);
	else
		gpio_set_high(21);
}

int main( void )
{
	gpio_set_mode(21, GPIO_FUNCTION_OUT);
	local_timer_init(0x0FFFFFF);
	while (1) if (local_timer_interrupt() == 1)
	{
		local_timer_reset(2);
		switchLED();
	}
	return(0);
}


