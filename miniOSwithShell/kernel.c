#include "const.h"
#include "gfunc.h"
#include "type.h"
#include "glo.h"

int main(void)
{
	int i,j;
	struct msg_type m;
	char boot_msg[]="Welcome to our miniOS!\n\rCopyright by Feiyu & Grieve\n\r\n\rType \"help\" to learn more\n\rHave Fun \1!\n\r";
	init();
	lock();
	read_sector(0x1000, 0x0000, 18,8);
	read_sector(0x7000,0x0000, 26,8);
	read_sector(0x6000,0x0000,34,16);
	pnum=1;
	for (i=0;i<9;i++) {mem[i]=FALSE;}
	for (i=0;i<PROC_NUM;i++) proc[i]=FALSE;
	mem[8]=TRUE;
	proc[0]=TRUE;
	for (i=0;i<9;i++) palloc[i]=0;
	palloc[0]=8;
/*	proc_init(USER_P1,0x1000,1);*/
	proc_init(MM,0x7000,7);
	thread_init(KEYBOARD,0xCFFF);
	thread_init(DISPLAY,0xAFFF);
	thread_init(SYSCALL,0x8FFF);
	pcb[0].state = RUNNING;
	cur_pid=0;
	curr_pcb = &(pcb[0]);
	for (i=0;i<PROC_NUM;i++) msg[i].id=NONE;

	prints(boot_msg);

	proc_init(SHELL,0x6000,6);
	unlock();
	while (1) {}
}
