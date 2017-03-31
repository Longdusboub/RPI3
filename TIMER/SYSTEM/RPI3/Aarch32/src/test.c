/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple system timer test for raspberry pi 2/3 Aarch 32
 */

#include "gpio.c"
#include "interrupt.c"
#include "systemtimer.c"

void switchLED(void)
{
	st_set_timer(100, ST_MS, 1);
	st_clear_irq(ST_IRQ1);
	if (gpio_get_level(21) == 1)
		gpio_set_low(21);
	else
		gpio_set_high(21);
}

int main(void)
{
	//Set up GPIO for interrupt handler
	gpio_set_mode(21, GPIO_FUNCTION_OUT);

	//Add handler for bot interrupt
	add_handler(gpu_irq_handler, IRQ_GPU);
	add_gpu_handler(switchLED, 1);
	st_set_timer(100, ST_MS, 1);
	//Enable MMU
	enable_gpu_irq(GPU_ST1_IRQ);
	asm("CPSIE I");
	return 0;
}

