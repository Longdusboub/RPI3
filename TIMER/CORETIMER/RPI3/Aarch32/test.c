/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple core timer init and blink for raspberry pi 3 Aarch32
 */

#include "gpio.c"
#include "coretimer.c"
#include "interrupt.c"

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
	ct_init_timer(0x8FFF);
	ct_set_increment(1);
	ct_set_source(CRY);
	ct_set_prescaler(0x00FFFFFF);
	ct_set_ctrl_reg(0, 1);
	while (1) if (ct_int(0, 1) == 1)
	{
		ct_init_timer(0x8FFF);
		switchLED();
	}
	return(0);
}


