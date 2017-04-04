/*
 * Authors : Alexandre "Dargor" Meunier
 * Descriptions : C file for the BCM 2836/7 mailbox management
 */

#include "mailbox.h"

void mailbox_write(int core, int mailbox, int message)
{
	MB_SET_REG(MB_GET_WRITEO(core, mailbox), message);
}

void mail_clear_bit(int mailbox, int bit)
{
	MB_SET_REG(MB_GET_READO(cpu_id(), mailbox), (1 << bit));
}

void mailbox_full_clear(int mailbox)
{
	MB_SET_REG(MB_GET_READO(cpu_id(), mailbox), 0xFFFFFFFF);
}

int mailbox_read(int mailbox)
{
	return MB_GET_REG(MB_GET_READO(cpu_id(), mailbox));
}

int mailbox_read_bit(int mailbox, int bit)
{
	int reg = MB_GET_REG(MB_GET_READO(cpu_id(), mailbox));
	reg = reg >> bit;
	reg &= 1;
	return reg;
}
