/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for interrupt sources register for raspberry pi 3
 */

#define INT_SRC_CORE0	0x40000060
#define INT_SRC_CORE1	0x40000064
#define INT_SRC_CORE2	0x40000068
#define INT_SRC_CORE3	0x4000006C

#define INT_SRC_COREN(X)    ((X == 0) ? INT_SRC_CORE0 : (X == 1) ? INT_SRC_CORE1 : (X == 2) ? INT_SRC_CORE2 : INT_SRC_CORE3)

int ct_int(int core, int inte)
{
    if (core < 0 || core > 3 ||inte < 0 ||inte > 31)
	return -1;
    return (*(int *)INT_SRC_COREN(core) >> inte) & 1;
}
