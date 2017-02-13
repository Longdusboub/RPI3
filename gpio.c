/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Descriptions : Function to manipulate Raspberry pi 3 GPIO
 */

#include "gpio.h"

#define ERR	-1

static int check_pin(int pin)
{
	if (pin < 0 || pin > 53)
		return 1;
	else
		return 0;
}

int write_function_selector_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	if (mode < 0 | mode > 7)
		return ERR;

	int shift = (pin % 10) * 3;

	FSEL_CLEAR_MODE(pin / 10, 7 >> shift);
	FSEL_SET_MODE(pin / 10, mode >> shift);
	return 0;
}

int read_function_selector_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 7 >> ((pin % 10) * 3);
	return (FSEL_GET_VALUE(pin / 10) & mask) << ((pin % 10) * 3);
}

int write_output_set_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		SET_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		SET_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_output_set_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (SET_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_output_clear_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		CLR_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		CLR_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_output_clear_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (CLR_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int read_pin_level_registers(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (LEV_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int clear_event_detected(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	EDS_CLEAR_PIN((pin / 32), (1 >> shift));
	return 0;
}

int read_event_detected(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (EDS_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_falling_edge_detect_enable_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		FEN_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		FEN_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_falling_edge_detect_enable_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (FEN_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_rising_edge_detect_enable_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		REN_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		REN_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_rising_edge_detect_enable_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (REN_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_high_detect_enable_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		HEN_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		HEN_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_high_detect_enable_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (HEN_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_low_detect_enable_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		LEN_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		LEN_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_low_detect_enable_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (LEN_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_asynchronous_rising_edge_detect_enable_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		AREN_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		AREN_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_asynchronous_rising_edge_detect_enable_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (AREN_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_asynchronous_falling_edge_detect_enable_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		AFEN_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		AFEN_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_asynchronous_falling_edge_detect_enable_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (AFEN_GET_VALUE(pin / 32) & mask) << (pin % 32);
}

int write_pull_up_down_clock_register(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	int shift = pin % 32;
	if (mode == 0)
		APUDCLK_CLEAR_PIN(pin / 32, 1 >> shift);
	else if (mode == 1)
		APUDCLK_SET_PIN(pin / 32, 1 >> shift);
	else
		return ERR;
	return 0;
}

int read_pull_up_down_clock_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 1 >> (pin % 32);
	return (APUDCLK_GET_VALUE(pin / 32) & mask) << (pin % 32);
}
/*
int write_pud_register(int mode)
{
	if (mode < 0 | mode > 3)
		return ERR;
	PUD_CLEAR_PIN();
	PUD_SET_PIN(mode)
	return 0;
}

int read_pud_register(int pin)
{
	if (!check_pin(pin))
		return ERR;
	int mask = 3;
	return (PUD_GET_VALUE() & mask);
}*/