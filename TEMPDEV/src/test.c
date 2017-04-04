/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple jtag init for raspberry pi 3
 */

#include "gpio.c"
#include "utils.h"
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
	st_set_timer(1000, ST_MS, 1);
	st_clear_irq(ST_IRQ1);
	if (gpio_get_level(21) == 1)
		gpio_set_low(21);
	else
		gpio_set_high(21);
}

void switchAgain(void)
{
	local_timer_reset();
	if (gpio_get_level(16) == 1)
		gpio_set_low(16);
	else
		gpio_set_high(16);
}

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

void cpu_printid(void)
{
	aux_mu_putchar((char)(cpu_id() + 0x30));
	asm("b .");
}

int main(void)
{
	aux_mu_enable(3254);
	//Set up GPIO for interrupt handler
	gpio_set_mode(21, GPIO_FUNCTION_OUT);
	gpio_set_mode(12, GPIO_FUNCTION_OUT);
	gpio_set_mode(16, GPIO_FUNCTION_OUT);
	//Add handler for bot interrupt
	add_handler(gpu_irq_handler, IRQ_GPU);
	add_handler(switchAgain, IRQ_LT);
	add_handler(switchForEver, IRQ_CPS);
	add_gpu_handler(switchLED, 1);
	//Initialise both timer
	local_timer_set_routing(IRQ_CPU0);
	local_timer_init(1000 * LT_FREQ_MS);
	ct_set_increment(1);
	ct_set_source(CRY);
	ct_set_prescaler(CT_PRESCALER_1);
	ct_set_ctrl_reg(0, CT_IRQ_CPS);
	ct_init_timer(1000 * CT_MS_1);
	st_set_timer(1000, ST_MS, 1);
	//Enable MMU
	mailbox_write(1, 3, (int)cpu_printid);
	mailbox_write(2, 3, (int)console);
	enable_gpu_irq(GPU_ST1_IRQ);
	set_mmu();
	enable_mmu(0x1001);
	/* uart console for some basic memory/gpio management */
	asm("CPSIE I");
	return(0);
}

