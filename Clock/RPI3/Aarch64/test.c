/*
 * Authors : Alexandre "Dargor" Meunier <alexandre.meunier@epita.fr>
 * Description : Simple led blinking bare metal exemple for raspberry pi 3
 */

#include "gpio.c"
#include "clock.h"

int init_clock(int clock, int mash, int divi, int divf, int src)
{
	gpio_set_mode(4 + clock, GPIO_FUNCTION_ALT0);
	(CAST_CMGPDIV(clock)) = CM_PASS | (divi << 12) | divf;
	(CAST_CMGPCTL(clock)) = CM_PASS | mash | src | (1 << 5);
	gpio_set_high(6);
	return 1;
}

int launch_clock(int clock)
{
	(CAST_CMGPCTL(clock)) |= (1 << 4);
	return 1;
}

int stop_clock(int clock)
{
	(CAST_CMGPCTL(clock)) &= ~(1 << 4);
	return 1;
}

int main( void )
{
	gpio_set_mode(6, 1);
	init_clock(0, MASH0, 10, 0, SRC_PLLD);
	launch_clock(0);
	return(0);
}
