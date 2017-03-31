/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : simple uart0 manager for raspberry pi 3
 */

#include "../include/uart.h"

void uart_send_char(char c)
{
	while ((*(int *)(UART_FR) & 0x20) != 0)
		continue;
	*(int *)(UART_DR) = (int)c;
}

void uart_init(void)
{
	*(int *)(UART_CR)   = 0;
	gpio_set_mode(14, GPIO_FUNCTION_ALT0);
	gpio_set_mode(15, GPIO_FUNCTION_ALT0);
	*(int *)(UART_ICR)  = 0x7FE;
	*(int *)(UART_FBRD) = 40;
	*(int *)(UART_IBRD) = 0x1;
	*(int *)(UART_LCRH) = 0;
	*(int *)(UART_LCRH) = 0x70;
	*(int *)(UART_CR)   = 0x101;



}
