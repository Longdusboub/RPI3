/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple uart console for raspberry pi 3 debug
 */

unsigned int ctoi(char tab[], int size)
{
    int res = 0;
    int shift = 4 * (size - 1);
    for (int i = 0; i < size; i++)
    {
	    if (tab[i] < 0x41)
		    res = res + ((tab[i] - 48) << shift);
	    else
		    res = res + ((tab[i] - 55) << shift);
	    shift -= 4;
    }
    return res;
}

void domain_call(void)
{
	int d, p;
	char reg[1];
	aux_mu_putstring("Domain :");
	while (!AUX_MU_FIFO_RX_READY)
		    continue;
	reg[0] = aux_mu_getchar();
	d = ctoi(reg, 1);
	aux_mu_putstring("\nPermission :");
	while (!AUX_MU_FIFO_RX_READY)
		continue;
	reg[0] = aux_mu_getchar();
	p = ctoi(reg, 1);
	aux_mu_putchar('\n');
	set_domain_permission(d, p);
}

void read_call(void)
{
	int r;
	char reg[9];
	reg[8] = '\0';
	aux_mu_putstring("Register : 0x");
	for (int i = 0; i < 8; i++)
	{
		while (!AUX_MU_FIFO_RX_READY)
			continue;
		reg[i] = aux_mu_getchar();
	}
	r = ctoi(reg, 8);
	int result = *(int *)(r);
	aux_mu_putstring("\nValue : ");
	aux_mu_puthex(result);
	aux_mu_putchar('\n');
}

void register_call(void)
{
	int r, v;
	char reg[9];
	reg[8] = '\0';
	aux_mu_putstring("Register : 0x");
	for (int i = 0; i < 8; i++)
	{
		while (!AUX_MU_FIFO_RX_READY)
			continue;
		reg[i] = aux_mu_getchar();
	}
	r = ctoi(reg, 8);
	aux_mu_putstring("\nValue : 0x");
	for (int i = 0; i < 8; i++)
	{
		while (!AUX_MU_FIFO_RX_READY)
			continue;
		reg[i] = aux_mu_getchar();
	}
	aux_mu_putchar('\n');
	v = ctoi(reg, 8);
	*(int *)r = v;
}

void gpio_call(void)
{
	int g, f;
	char reg[3];
	reg[2] = '\0';
	aux_mu_putstring("GPIO : 0x");
	for (int i = 0; i < 2; i++)
	{
		while (!AUX_MU_FIFO_RX_READY)
			continue;
		reg[i] = aux_mu_getchar();
	}
	g= ctoi(reg, 2);
	while (!AUX_MU_FIFO_RX_READY)
		continue;
	aux_mu_putstring("\nMode : ");
	reg[0] = aux_mu_getchar();
	f = ctoi(reg, 1);
	aux_mu_putchar('\n');
	gpio_set_mode(g, f);
}

void level_call(void)
{
	int g, l;
	char reg[3];
	reg[2] = '\0';
	aux_mu_putstring("GPIO : 0x");
	for (int i = 0; i < 2; i++)
	{
		while (!AUX_MU_FIFO_RX_READY)
			continue;
		reg[i] = aux_mu_getchar();
	}
	g = ctoi(reg, 2);
	gpio_set_mode(g, GPIO_FUNCTION_OUT);
	aux_mu_putstring("\nLevel : ");
	while (!AUX_MU_FIFO_RX_READY)
		continue;
	reg[0] = aux_mu_getchar();
	l = ctoi(reg, 1);
	aux_mu_putchar('\n');
	l == 0 ? gpio_set_low(g) : gpio_set_high(g);
}

void blinky(void)
{
blink:
	gpio_set_mode(12, GPIO_FUNCTION_OUT);
	if (gpio_get_level(12) == 1)
		gpio_set_low(12);
	else
		gpio_set_high(12);
	for (int i = 0; i < 1000000; i++) continue;
	goto blink;
}

int console(void)
{
	int fail = 0;
	int loop = 1;
	while (loop)
	{
		if (AUX_MU_FIFO_RX_READY)
		{
			char cmd = aux_mu_getchar();
			switch (cmd)
			{
				case 'v':
					aux_mu_putstring("\nRegister read function see help for more details\n");
					read_call();
					break;
				case 'r':
					aux_mu_putstring("\nRegiste set function see help for more details\n");
					register_call();
					break;
				case 'd':
					aux_mu_putstring("\nDomain permission set function see help for more details\n");
					domain_call();
					break;
				case 'l':
					aux_mu_putstring("\nGPIO level function see help for more deatil\n");
					level_call();
					break;
				case 'g':
					aux_mu_putstring("\nGPIO function set see help for more detail\n");
					gpio_call();
					break;
				case 'h':
					mailbox_write(1, 3, (int)(blinky));
					break;
				case 'i':
					if (fail < 10)
					    aux_mu_putstring("\nUnknow command, you just lost the game bro \n");
					else if (fail < 11)
						aux_mu_putstring("\nYou think this is a motherfucking game ?\n");
					else if (fail < 12)
						aux_mu_putstring("\nWhat the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit. If only you could have known what unholy retribution your little \"clever\" comment was about to bring down upon you, maybe you would have held your fucking tongue. But you couldn't, you didn't, and now you're paying the price, you goddamn idiot. I will shit fury all over you and you will drown in it. You're fucking dead, kiddo.\n");
					else
						loop = 0;
					fail++;
					break;
				default :
					break;
			}
		}
	}
	return(0);
}

