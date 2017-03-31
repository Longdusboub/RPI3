char *abort_type[16] = {
	"Alignement fault (Err 1)",
	"Debug event (Err 2)",
	"Access flag fault level 1 (Err 3)",
	"Fault on instruction cache maintenance (Err 4)",
	"Translation fault level 1 (Err 5)",
	"Access flag fault level 2 (Err 6)",
	"Translation fault level 2 (Err 7)",
	"Synchronous external abort (Err 8)",
	"Domain fault level 1 (Err 9)",
	"No fault here sir (Err 10)",
	"Domain fault level 2 (Err 11)",
	"Synchronous external abort (Err 12)",
	"Permission fault level 1 (Err 13)",
	"Synchronous external abort (Err 14)",
	"Permision fault level 2 (Err 15)",
	"TBL conflict abort (Err 16)" };

void abort_print(void)
{
	register int addr asm ("r0");
	int temp = addr;
	register int error asm("r1");
	int errornum = (error & 0xF) | ((error >> 6) & 0x10);
	aux_mu_putstring("Data Abort error :\n");
	aux_mu_putstring(abort_type[errornum - 1]);
	aux_mu_putstring(" occured at address : ");
	aux_mu_puthex(temp);
	aux_mu_putstring("\n");

	aux_mu_putstring(".------..------..------.        .------..------..------..------.\n");
	aux_mu_putstring("|T.--. ||H.--. ||E.--. | .-.    |G.--. ||A.--. ||M.--. ||E.--. |\n");
	aux_mu_putstring("| :/\\: || :/\\: || (\\/) |((5))   | :/\\: || (\\/) || (\\/) || (\\/) |\n");
	aux_mu_putstring("| (__) || (__) || :\\/: | '-.-.  | :\\/: || :\\/: || :\\/: || :\\/: |\n");
	aux_mu_putstring("| '--'T|| '--'H|| '--'E|  ((1)) | '--'G|| '--'A|| '--'M|| '--'E|\n");
	aux_mu_putstring("`------'`------'`------'   '-'  `------'`------'`------'`------'\n");
}
