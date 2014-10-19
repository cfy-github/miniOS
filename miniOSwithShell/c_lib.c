#include "const.h"
#include "glo.h"
#include "gfunc.h"

void prints(char *s)
{
	int i, n=strlen(s);
	for (i=0;i<n;i++) printc(s[i]);
}

int strlen(char * s)
{
	int i;
	for (i=0; s[i]!='\0';i++);
	return i;
}

bool strcmp(char *s1, char *s2)
{
	int i;
	int n=strlen(s1);
	if (n!=strlen(s2)) return FALSE;
	for (i=0;i<n;i++) if (s1[i]!=s2[i]) return FALSE;
	return TRUE;
}

void strcat(char *s1, int x, char *s2)
{
	int i=0;
	while (s2[i]!='\0')
	{
		s1[x]=s2[i];
		x++;
		i++;
	}
	s1[x++]='\0';
}

void printhex(unsigned int x)
{
	if (x >= 0 && x <= 9)
	printc(x + '0');
	else
	printc(x-10+'A');
}
void printd(unsigned int x)
{
	if(x >= 0x1000)
	{
		printhex(x/0x1000);
		x = x%0x1000;
	}else {printhex(0); x = x%0x1000;}
	if(x >= 0x0100)
	{
		printhex(x/0x0100);
		x = x%0x0100;
	}else {printhex(0); x = x%0x0100;}
	if(x >= 0x0010)
	{
		printhex(x/0x0010);
		x = x%0x0010;
	}else {printhex(0); x = x%0x0010;}
	if(x < 0x0010)
	{
		printhex(x);		
	}
}
void read_sector(int a, int b, int start, int len)
{
	int p=(start-1)/18, q=(start-1)%18;
	readsector(a,b,p%2,p/2,q+1,len);
}
void proc_init(int x, int addr, int m)
{
	pcb[x].ds=pcb[x].ss=addr;
	pcb[x].sp=0xFFF9;
	pcb[x].es=pcb[x].ax=pcb[x].bx=pcb[x].cx=pcb[x].dx=pcb[x].bp=pcb[x].si=pcb[x].di=0;
	pcb[x].state=BLOCKED;
	pnum++;
	palloc[x]=m;
	mem[m]=TRUE;
	proc[x]=TRUE;
	init_psw(addr);
}
void thread_init(int x, unsigned int addr)
{
	pcb[x].ds = pcb[x].ss = 0x8000;
	pcb[x].sp = addr-6;
	pcb[x].es=pcb[x].ax=pcb[x].bx=pcb[x].cx=pcb[x].dx=pcb[x].bp=pcb[x].si=pcb[x].di=0;
	pcb[x].state=BLOCKED;
	pnum++;
	palloc[x]=8;
	proc[x]=TRUE;
	if (x==KEYBOARD) init_t_psw(addr, (int)kb_driver);
	else if (x==DISPLAY) init_t_psw(addr, (int)disp_driver);
	else init_t_psw(addr, (int)sys_driver);
}
void task_switch(void)
{
	int i, j;
	struct msg_type m;
/*	printc('<');
	for (i=0; i<pnum+1; i++)
	{	
		printc('|');
		printc(i+'0');
		if(pcb[i].state == BLOCKED) printc('B');
		if(pcb[i].state == WAITING_S) printc('S'); 
		if(pcb[i].state == WAITING_R) printc('R');
		if(pcb[i].state == RUNNING) printc('I');
	}
	printc('>');*/
	if (raw_head != raw_tail && pcb[KEYBOARD].state == WAITING_R)
	{
		m.m[0]=1;
		send(KEYBOARD, &m);
	}
	if (pcb[cur_pid].state != WAITING_S && pcb[cur_pid].state != WAITING_R)
		pcb[cur_pid].state = BLOCKED;
	cur_pid = (cur_pid+1)%PROC_NUM;
	while (pcb[cur_pid].state!=BLOCKED || !proc[cur_pid]) cur_pid = (cur_pid+1)%PROC_NUM;
	pcb[cur_pid].state = RUNNING;
	curr_pcb = &(pcb[cur_pid]);
/*	printc(cur_pid+'0');
	printd(*((int*)(curr_pcb)));
	printc('\n');
	printd(curr_pcb->bx);
	printc('\n');
	printd(curr_pcb->cx);
	printc('\n');
	printd(curr_pcb->dx);
	printc('\n');
	printd(curr_pcb->di);
	printc('\n');
	printd(curr_pcb->si);
	printc('\n');
	printd(curr_pcb->ss);
	printc('\n');
	printd(curr_pcb->sp);
	printc('\n');
	printd(curr_pcb->bp);
	printc('\n');
	printd(curr_pcb->ds);
	printc('\n');
	printd(curr_pcb->es);
	printc('>');
	printc('>');*/
	out_byte(0x20, 0x20);
}

