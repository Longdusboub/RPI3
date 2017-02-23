/*
 * Authors : Alexandre "Dargor" Meunier <alexandre.meunier@epita.fr>
 * Description : Header for raspberry pi 3 GPIO clock
 */

//Control manager register
#define CM_GP0CTL   0x3F101070
#define	CM_GP1CTL   0x3F101078
#define CM_GP2CTL   0x3F101080

//Divider register
#define CM_GP0DIV   0x3F101074
#define CM_GP1DIV   0x3F10107C
#define CM_GP2DIV   0x3F101084

//Clock manager password
#define CM_PASS	    (0x5A << 24)


//MASH value
#define MASH0	    (0x0 << 9)
#define MASH1	    (0x1 << 9)
#define MASH2	    (0x2 << 9)
#define MASH3	    (0x3 << 9)

//Sources
#define SRC_CRY	    0x1 //19.2 MHz
#define SRC_PLLC    0x5 //1000 MHz
#define SRC_PLLD    0x6 //500 MHz
#define SRC_HDMI    0x7 //216 MHz

typedef union clock_control
{
	int val;
	struct ccbitfields
	{
		unsigned pswd : 8;
		unsigned osef : 13;
		unsigned mash : 2;
		unsigned flip : 1;
		unsigned busy : 1;
		unsigned yolo : 1;
		unsigned kill : 1;
		unsigned enab : 1;
		unsigned srcs : 4;
	} CCBF;
}clock_control_t;

typedef union clock_divider
{
	int val;
	struct cdbitfields
	{
		unsigned pswd : 8;
		unsigned divi : 12;
		unsigned divf : 12;
	} CDBF;
}clock_divider_t;

#define GET_CMGPCTL(X)	(X == 0 ? CM_GP0CTL : X == 1 ? CM_GP1CTL : CM_GP2CTL)
#define CAST_CMGPCTL(X)	(*(int *)GET_CMGPCTL(X))

#define GET_CMGPDIV(X)	(X == 0 ? CM_GP0DIV : X == 1 ? CM_GP1DIV : CM_GP2DIV)
#define CAST_CMGPDIV(X)	(*(int *)GET_CMGPCTL(X))
