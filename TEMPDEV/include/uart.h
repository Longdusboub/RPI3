/*
 * Authors : Alexandre "Dargor" Meunier
 * Description : header for a simple uart0 manager for raspberry pi 3
 */

#ifndef _UART_H_
 #define _UART_H_

#define UART_BASE   0x3F201000

#define UART_DR	    (UART_BASE + 0x0)
#define UART_RSRECR (UART_BASE + 0x4)
#define UART_FR	    (UART_BASE + 0x18)
#define UART_ILPR   (UART_BASE + 0x20)
#define UART_IBRD   (UART_BASE + 0x24)
#define UART_FBRD   (UART_BASE + 0x28)
#define UART_LCRH   (UART_BASE + 0x2C)
#define UART_CR	    (UART_BASE + 0x30)
#define UART_IFLS   (UART_BASE + 0x34)
#define UART_IMSC   (UART_BASE + 0x38)
#define UART_RIS    (UART_BASE + 0x3C)
#define UART_MIS    (UART_BASE + 0x40)
#define UART_ICR    (UART_BASE + 0x44)
#define UART_DMACR  (UART_BASE + 0x48)
#define UART_ITCR   (UART_BASE + 0x80)
#define UART_ITIP   (UART_BASE + 0x84)
#define UART_ITOP   (UART_BASE + 0x88)
#define UART_TDR    (UART_BASE + 0x8C)

#endif /* _UART_H_ */
