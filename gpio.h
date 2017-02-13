/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Descriptions : Header for Raspberry pi 3 GPIO
 */
#ifndef _GPIO_H_
#define _GPIO_H_
#define GPIOBASEADDR	0x7E200000	    //GPIO register base address

/* GPIO function selector registers
000 : GPIO is an input
001 : GPIO is an output
100 : GPIO Alt0
101 : GPIO Alt1
110 : GPIO Alt2
111 : GPIO Alt3
011 : GPIO Alt4
010 : GPIO Alt5 */

#define	GPFSEL0		GPIOBASEADDR + 0x0  //GPIO function selector for GPIO 0-9
#define GPFSEL1		GPIOBASEADDR + 0x4  //GPIO function selector for GPIO 10-19
#define GPFSEL2		GPIOBASEADDR + 0x8  //GPIO function selector for GPIO 20-29
#define GPFSEL3		GPIOBASEADDR + 0xC  //GPIO function selector for GPIO 30-39
#define GPFSEL4     	GPIOBASEADDR + 0x10 //GPIO function selector for GPIO 40-49
#define GPFSEL5     	GPIOBASEADDR + 0x14 //GPIO function selector for GPIO 50-53

#define FSEL_GET_REG(X)   	    ((X == 0) ? GPFSEL0 : (X == 1) ? GPFSEL1 : (X == 2) ? GPFSEL2 : (X == 3) ? GPFSEL3 : (X == 4) ? GPFSEL4 : GPFSEL5)

#define FSEL_WRITE_VALUE(R, V)	    (*(int *)FSEL_GET_REG(R) = (V))
#define FSEL_GET_VALUE(R)	    ((*(int *)FSEL_GET_REG(R)))
#define FSEL_CLEAR_MODE(R, V)	    (FSEL_WRITE_VALUE(R, FSEL_GET_VALUE(R)& ~(V)))
#define FSEL_SET_MODE(R, V)	    (FSEL_WRITE_VALUE(R, FSEL_GET_VALUE(R)| (V)))

/* GPIO Output Set registers
   No effect is set as an input GPIO
   0 = No effect
   1 = Set GPIO pin (If Low goes High) */

#define GPSET1		GPIOBASEADDR + 0x1C //GPIO output set for GPIO 0-31
#define GPSET2		GPIOBASEADDR + 0x20 //GPIO output set for GPIO 32-53

#define SET_GET_REG(X)		    ((X == 1) ? GPSET1 : GPSET2)
#define SET_WRITE_VALUE(R, V)	    ((*(int *)SET_GET_REG(R)) = (V))
#define SET_GET_VALUE(R)	    (*(int *)SET_GET_REG(R))
#define SET_CLEAR_PIN(R, V)	    (SET_WRITE_VALUE(R, SET_GET_VALUE(R) & ~(V)))
#define SET_SET_PIN(R, V)	    (SET_WRITE_VALUE(R, SET_GET_VALUE(R) | (V)))

/* GPIO Output Clear registers
   No effect is set as an input GPIO
   0 = No effect
   1 = Clear GPIO pin (If High goes Low) */

#define GPCLR1		GPIOBASEADDR + 0x28 //GPIO output clear for GPIO 0-31
#define GPCLR2		GPIOBASEADDR + 0x2C //GPIO output clear for GPIO 32-53

#define CLR_GET_REG(X)  	    ((X == 1) ? GPCLR1 : GPCLR2)
#define CLR_WRITE_VALUE(R, V)	    ((*(int *)CLR_GET_REG(R)) = (V))
#define CLR_GET_VALUE(R)	    (*(int *)CLR_GET_REG(R))
#define CLR_CLEAR_PIN(R, V)	    (CLR_WRITE_VALUE(R, CLR_GET_VALUE(R) & ~(V)))
#define CLR_SET_PIN(R, V)	    (CLR_WRITE_VALUE(R, CLR_GET_VALUE(R) | (V)))

/* GPIO Pin Level registers
   0 = GPIO pin is low
   1 = GPIO pin is high */

#define GPLEV1		GPIOBASEADDR + 0x34 //GPIO Pin level for GPIO 0-31
#define GPLEV2		GPIOBASEADDR + 0x38 //GPIO Pin level for GPIO 32-53

#define LEV_GET_REG(X)   	    ((X == 1) ? GPLEV1 : GPLEV2)
#define LEV_GET_VALUE(R)	    (*(int *)LEV_GET_REG(R))

/* GPIO event detect status registers
   0 = event not detected
   1 = event detected */

#define	GPEDS1		GPIOBASEADDR + 0x40 //GPIO Pin event detect status for gpio 0-31
#define	GPEDS2		GPIOBASEADDR + 0x44 //GPIO Pin event detect status for gpio 32-53

#define EDS_GET_REG(X)   	    ((X == 1) ? GPEDS1 : GPEDS2)
#define EDS_WRITE_VALUE(R, V)	    ((*(int *)EDS_GET_REG(R)) = (V))
#define EDS_GET_VALUE(R)	    ((*(int *)EDS_GET_REG(R)))
#define EDS_CLEAR_PIN(R, V)	    (EDS_WRITE_VALUE(R, EDS_GET_VALUE(R) & ~(V)))
#define EDS_SET_PIN(R, V)	    (EDS_WRITE_VALUE(R, EDS_GET_VALUE(R) | (V)))

/* GPIO pin rising edge detect enable registers
   0 = rising edge detect is disable
   1 = rising edge on corresponding pin set corresponding bit in GPEDS */

#define	GPREN1		GPIOBASEADDR + 0x4C //GPIO rising edge detect enable for gpio 0-31
#define	GPREN2		GPIOBASEADDR + 0x50 //GPIO rising edge detect enable for gpio 32-53

#define REN_GET_REG(X)   	    ((X == 1) ? GPREN1 : GPREN2)
#define REN_WRITE_VALUE(R, V)	    ((*(int *)REN_GET_REG(R)) = (V))
#define REN_GET_VALUE(R)	    ((*(int *)REN_GET_REG(R)))
#define REN_CLEAR_PIN(R, V)	    (REN_WRITE_VALUE(R, REN_GET_VALUE(R) & ~(V)))
#define REN_SET_PIN(R, V)	    (REN_WRITE_VALUE(R, REN_GET_VALUE(R) | (V)))

/* GPIO pin falling edge detect enable registers
   0 = falling edge detect is disable
   1 = falling edge on corresponding pin set corresponding bit in GPEDS */

#define	GPFEN1		GPIOBASEADDR + 0x58 //GPIO falling edge detect enable for gpio 0-31
#define	GPFEN2		GPIOBASEADDR + 0x5C //GPIO falling edge detect enable for gpio 32-53

#define FEN_GET_REG(X)   	    ((X == 1) ? GPFEN1 : GPFEN2)
#define FEN_WRITE_VALUE(R, V)	    ((*(int *)FEN_GET_REG(R)) = (V))
#define FEN_GET_VALUE(R)	   	((*(int *)FEN_GET_REG(R)))
#define FEN_CLEAR_PIN(R, V)	    (FEN_WRITE_VALUE(R, FEN_GET_VALUE(R) & ~(V)))
#define FEN_SET_PIN(R, V)	    (FEN_WRITE_VALUE(R, FEN_GET_VALUE(R) | (V)))

/* GPIO pin High detect enable registers
   0 = High detect is disable
   1 = High on corresponding pin set corresponding bit in GPEDS */

#define	GPHEN1 		GPIOBASEADDR + 0x64 //GPIO High detect enable for gpio 0-31
#define	GPHEN2		GPIOBASEADDR + 0x68 //GPIO High detect enable for gpio 32-53

#define HEN_GET_REG(X)   	    ((X == 1) ? GPHEN1 : GPHEN2)
#define HEN_WRITE_VALUE(R, V)	    ((*(int *)HEN_GET_REG(R)) = (V))
#define HEN_GET_VALUE(R)	    ((*(int *)HEN_GET_REG(R)))
#define HEN_CLEAR_PIN(R, V)	    (HEN_WRITE_VALUE(R, HEN_GET_VALUE(R) & ~(V)))
#define HEN_SET_PIN(R, V)	    (HEN_WRITE_VALUE(R, HEN_GET_VALUE(R) | (V)))

/* GPIO pin Low detect enable registers
   0 = Low detect is disable
   1 = Low on corresponding pin set corresponding bit in GPEDS */

#define	GPLEN1		GPIOBASEADDR + 0x70 //GPIO Low detect enable for gpio 0-31
#define	GPLEN2		GPIOBASEADDR + 0x74 //GPIO Low detect enable for gpio 32-53

#define LEN_GET_REG(X)   	    ((X == 1) ? GPLEN1 : GPLEN2)
#define LEN_WRITE_VALUE(R, V)	    ((*(int *)LEN_GET_REG(R)) = (V))
#define LEN_GET_VALUE(R)	    ((*(int *)LEN_GET_REG(R)))
#define LEN_CLEAR_PIN(R, V)	    (LEN_WRITE_VALUE(R, LEN_GET_VALUE(R) & ~(V)))
#define LEN_SET_PIN(R, V)	    (LEN_WRITE_VALUE(R, LEN_GET_VALUE(R) | (V)))

/* GPIO pin async rising edge detect enable registers
   0 = async rising edge detect is disable
   1 = async rising edge on corresponding pin set corresponding bit in GPEDS */

#define	GPAREN1		GPIOBASEADDR + 0x7C //GPIO async rising edge detect enable for gpio 0-31
#define	GPAREN2		GPIOBASEADDR + 0x80 //GPIO async rising edge detect enable for gpio 32-53

#define AREN_GET_REG(X)   	    ((X == 1) ? GPAREN1 : GPAREN2)
#define AREN_WRITE_VALUE(R, V)	    ((*(int *)AREN_GET_REG(R)) = (V))
#define AREN_GET_VALUE(R)	    ((*(int *)AREN_GET_REG(R)))
#define AREN_CLEAR_PIN(R, V)	    (AREN_WRITE_VALUE(R, AREN_GET_VALUE(R) & ~(V)))
#define AREN_SET_PIN(R, V)	    (AREN_WRITE_VALUE(R, AREN_GET_VALUE(R) | (V)))

/* GPIO pin async falling edge detect enable registers
   0 = async falling edge detect is disable
   1 = async falling edge on corresponding pin set corresponding bit in GPEDS */

#define	GPAFEN1		GPIOBASEADDR + 0x88 //GPIO async falling edge detect enable for gpio 0-31
#define	GPAFEN2		GPIOBASEADDR + 0x8C //GPIO async falling edge detect enable for gpio 32-53

#define AFEN_GET_REG(X)   	    ((X == 1) ? GPAFEN1 : GPAFEN2)
#define AFEN_WRITE_VALUE(R, V)	    ((*(int *)AFEN_GET_REG(R)) = (V))
#define AFEN_GET_VALUE(R)	    ((*(int *)AFEN_GET_REG(R)))
#define AFEN_CLEAR_PIN(R, V)	    (AFEN_WRITE_VALUE(R, AFEN_GET_VALUE(R) & ~(V)))
#define AFEN_SET_PIN(R, V)	    (AFEN_WRITE_VALUE(R, AFEN_GET_VALUE(R) | (V)))

/* GPIO pull up/down registers
   only bits 1-0 are used.
   00 = Diasble pull up/down
   01 = Enable pull down control
   10 = Enable pull up control
   11 = Reserved */

#define	GPPUD		GPIOBASEADDR + 0x94 //GPIO pull up/down registers

#define PUD_WRITE_VALUE(V)	    ((*(int *)GPPUD) = (V))
#define PUD_GET_VALUE()		    ((*(int *)GPPUD))
#define PUD_CLEAR_PIN()	    	    (PUD_WRITE_VALUE(PUD_GET_VALUE() & ~(3)))
#define PUD_SET_PIN(V)	    	    (PUD_WRITE_VALUE(PUD_GET_VALUE() | (V))) 

/* GPIO pull up/down clock registers
   0 = No Effect
   1 = Assert Clock on line */

#define	GPAPUDCLK1	GPIOBASEADDR + 0x98 //GPIO pull up/down clock for gpio 0-31
#define	GPAPUDCLK2	GPIOBASEADDR + 0x9C //GPIO pull up/down clock for gpio 32-53

#define APUDCLK_GET_REG(X)   	    ((X == 1) ? GPAPUDCLK1 : GPAPUDCLK2)
#define APUDCLK_WRITE_VALUE(R, V)   ((*(int *)APUDCLK_GET_REG(R)) = (V))
#define APUDCLK_GET_VALUE(R)	    ((*(int *)APUDCLK_GET_REG(R)))
#define APUDCLK_CLEAR_PIN(R, V)	    (APUDCLK_WRITE_VALUE(R, APUDCLK_GET_VALUE(R) & ~(V)))
#define APUDCLK_SET_PIN(R, V)	    (APUDCLK_WRITE_VALUE(R, APUDCLK_GET_VALUE(R) | (V)))


#endif /*GPIO_H_ */