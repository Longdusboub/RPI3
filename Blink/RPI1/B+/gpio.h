/*
 * : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Descriptions : Header for Raspberry pi 3 GPIO
 */
 
#ifndef _GPIO_H_
#define _GPIO_H_
#define GPIOBASEADDR	0x20200000	    //GPIO register base address


/* GPIO function selector registers */

#define GPIO_FUNCTION_IN	0b000
#define GPIO_FUNCTION_OUT	0b001
#define GPIO_FUNCTION_ALT0	0b100
#define GPIO_FUNCTION_ALT1	0b101
#define GPIO_FUNCTION_ALT2	0b110
#define GPIO_FUNCTION_ALT3	0b111
#define GPIO_FUNCTION_ALT4	0b011
#define GPIO_FUNCTION_ALT5	0b010

#define	GPFSEL0		GPIOBASEADDR + 0x0  //GPIO function selector for GPIO 0-9
#define GPFSEL1		GPIOBASEADDR + 0x4  //GPIO function selector for GPIO 10-19
#define GPFSEL2		GPIOBASEADDR + 0x8  //GPIO function selector for GPIO 20-29
#define GPFSEL3		GPIOBASEADDR + 0xC  //GPIO function selector for GPIO 30-39
#define GPFSEL4     	GPIOBASEADDR + 0x10 //GPIO function selector for GPIO 40-49
#define GPFSEL5     	GPIOBASEADDR + 0x14 //GPIO function selector for GPIO 50-53

#define FSEL_GET_REG(X)   	    ((X == 0) ? GPFSEL0 : (X == 1) ? GPFSEL1 : (X == 2) ? GPFSEL2 : (X == 3) ? GPFSEL3 : (X == 4) ? GPFSEL4 : GPFSEL5)

/* GPIO Output Set registers
   No effect is set as an input GPIO
   0 = No effect
   1 = Set GPIO pin (If Low goes High) */

#define GPSET0		GPIOBASEADDR + 0x1C //GPIO output set for GPIO 0-31
#define GPSET1		GPIOBASEADDR + 0x20 //GPIO output set for GPIO 32-53

#define SET_GET_REG(X)		    ((X == 0) ? GPSET0 : GPSET1)

/* GPIO Output Clear registers
   No effect is set as an input GPIO
   0 = No effect
   1 = Clear GPIO pin (If High goes Low) */

#define GPCLR0		GPIOBASEADDR + 0x28 //GPIO output clear for GPIO 0-31
#define GPCLR1		GPIOBASEADDR + 0x2C //GPIO output clear for GPIO 32-53

#define CLR_GET_REG(X)  	    ((X == 0) ? GPCLR0 : GPCLR1)

/* GPIO Pin Level registers
   0 = GPIO pin is low
   1 = GPIO pin is high */

#define GPLEV0		GPIOBASEADDR + 0x34 //GPIO Pin level for GPIO 0-31
#define GPLEV1		GPIOBASEADDR + 0x38 //GPIO Pin level for GPIO 32-53

#define LEV_GET_REG(X)   	    ((X == 0) ? GPLEV0 : GPLEV1)

/* GPIO event detect status registers
   0 = event not detected
   1 = event detected */

#define	GPEDS0		GPIOBASEADDR + 0x40 //GPIO Pin event detect status for gpio 0-31
#define	GPEDS1		GPIOBASEADDR + 0x44 //GPIO Pin event detect status for gpio 32-53

#define EDS_GET_REG(X)   	    ((X == 0) ? GPEDS0 : GPEDS1)

/* GPIO pin rising edge detect enable registers
   0 = rising edge detect is disable
   1 = rising edge on corresponding pin set corresponding bit in GPEDS */

#define	GPREN0		GPIOBASEADDR + 0x4C //GPIO rising edge detect enable for gpio 0-31
#define	GPREN1		GPIOBASEADDR + 0x50 //GPIO rising edge detect enable for gpio 32-53

#define REN_GET_REG(X)   	    ((X == 0) ? GPREN0 : GPREN1)

/* GPIO pin falling edge detect enable registers
   0 = falling edge detect is disable
   1 = falling edge on corresponding pin set corresponding bit in GPEDS */

#define	GPFEN0		GPIOBASEADDR + 0x58 //GPIO falling edge detect enable for gpio 0-31
#define	GPFEN1		GPIOBASEADDR + 0x5C //GPIO falling edge detect enable for gpio 32-53

#define FEN_GET_REG(X)   	    ((X == 0) ? GPFEN0 : GPFEN1)

/* GPIO pin High detect enable registers
   0 = High detect is disable
   1 = High on corresponding pin set corresponding bit in GPEDS */

#define	GPHEN0 		GPIOBASEADDR + 0x64 //GPIO High detect enable for gpio 0-31
#define	GPHEN1		GPIOBASEADDR + 0x68 //GPIO High detect enable for gpio 32-53

#define HEN_GET_REG(X)   	    ((X == 0) ? GPHEN0 : GPHEN1)

/* GPIO pin Low detect enable registers
   0 = Low detect is disable
   1 = Low on corresponding pin set corresponding bit in GPEDS */

#define	GPLEN0		GPIOBASEADDR + 0x70 //GPIO Low detect enable for gpio 0-31
#define	GPLEN1		GPIOBASEADDR + 0x74 //GPIO Low detect enable for gpio 32-53

#define LEN_GET_REG(X)   	    ((X == 0) ? GPLEN0 : GPLEN1)


/* GPIO pin async rising edge detect enable registers
   0 = async rising edge detect is disable
   1 = async rising edge on corresponding pin set corresponding bit in GPEDS */

#define	GPAREN0		GPIOBASEADDR + 0x7C //GPIO async rising edge detect enable for gpio 0-31
#define	GPAREN1		GPIOBASEADDR + 0x80 //GPIO async rising edge detect enable for gpio 32-53

#define AREN_GET_REG(X)   	    ((X == 0) ? GPAREN0 : GPAREN1)

/* GPIO pin async falling edge detect enable registers
   0 = async falling edge detect is disable
   1 = async falling edge on corresponding pin set corresponding bit in GPEDS */

#define	GPAFEN0		GPIOBASEADDR + 0x88 //GPIO async falling edge detect enable for gpio 0-31
#define	GPAFEN1		GPIOBASEADDR + 0x8C //GPIO async falling edge detect enable for gpio 32-53

#define AFEN_GET_REG(X)   	    ((X == 0) ? GPAFEN0 : GPAFEN1)


/* GPIO pull up/down registers
   only bits 1-0 are used.
   00 = Diasble pull up/down
   01 = Enable pull down control
   10 = Enable pull up control
   11 = Reserved */

#define	GPPUD		GPIOBASEADDR + 0x94 //GPIO pull up/down registers
 

/* GPIO pull up/down clock registers
   0 = No Effect
   1 = Assert Clock on line */

#define	GPAPUDCLK0	GPIOBASEADDR + 0x98 //GPIO pull up/down clock for gpio 0-31
#define	GPAPUDCLK1	GPIOBASEADDR + 0x9C //GPIO pull up/down clock for gpio 32-53

#define APUDCLK_GET_REG(X)   	    ((X == 0) ? GPAPUDCLK0 : GPAPUDCLK1)



#endif /*GPIO_H_ */
