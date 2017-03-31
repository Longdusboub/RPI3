/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple jtag init for raspberry pi 3
 */

#include "gpio.c"
#include "../include/utils.h"
#include "coretimer.c"
#include "interrupt.c"
#include "localtimer.c"
#include "mmu.c"
#include "rpi_aux.c"
#include "mailbox.c"
#include "abort.c"
#include "console.c"
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

void init_jtag(void)
{
	gpio_set_mode(4, GPIO_FUNCTION_ALT5);
	gpio_set_mode(22, GPIO_FUNCTION_ALT4);
	gpio_set_mode(23, GPIO_FUNCTION_ALT4);
	gpio_set_mode(24, GPIO_FUNCTION_ALT4);
	gpio_set_mode(25, GPIO_FUNCTION_ALT4);
	gpio_set_mode(27, GPIO_FUNCTION_ALT4);
}

static int prempt = 0;

void cpu_printid(void)
{
	aux_mu_putchar((char)(cpu_id() + 0x30));
}

int main(void)
{
	//Set up GPIO for interrupt handler
	gpio_set_mode(21, GPIO_FUNCTION_OUT);

	//Add handler for bot interrupt
	add_handler(gpu_irq_handler, IRQ_GPU);
	add_gpu_handler(switchLED, 1);
	//Initialise both timer
	/*local_timer_set_routing(IRQ_CPU0);
	local_timer_init(1 * LT_FREQ_MS);*/
	st_set_timer(100, ST_MS, 1);
	//Enable MMU
	enable_gpu_irq(GPU_ST1_IRQ);
	set_mmu();
	enable_mmu(0x1001);

	/* uart console for some basic memory/gpio management */
	aux_mu_enable(3254);
	mailbox_write(1, 3, (int)(cpu_printid));
	mailbox_write(2, 3, (int)(cpu_printid));
	mailbox_write(3, 3, (int)(cpu_printid));
	asm("CPSIE I");
	console();
	return(0);
}

