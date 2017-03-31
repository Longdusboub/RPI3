/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Header file for raspberry pi 3 core timer.
 */

#ifndef _CORETIMER_H_
 #define _CORETIMER_H_

#define CT_BASE_ADDR	0x40000000

#define CT_CTRL_REG	0x40000000
#define CT_PRES_REG	0x40000008
#define CT_INT_CTRL0	0x40000040
#define CT_INT_CTRL1	0x40000044
#define CT_INT_CTRL2	0x40000048
#define CT_INT_CTRL3	0x4000004C

#define CT_IRQ_CPS  (1 << 0)
#define CT_IRQ_CPNS (1 << 1)
#define CT_IRQ_CHP  (1 << 2)
#define CT_IRQ_CV   (1 << 3)
#define CT_FIQ_CPS  (1 << 4)
#define CT_FIQ_CPNS (1 << 5)
#define CT_FIQ_CHP  (1 << 6)
#define CT_FIQ_CV   (1 << 7)

#define GET_CT_INT_CTRL(X)  ((X == 0) ? CT_INT_CTRL0 : (X == 1) ? CT_INT_CTRL1 : (X == 2) ? CT_INT_CTRL2 : CT_INT_CTRL3)

#endif /* _CORETIMER_H_ */
