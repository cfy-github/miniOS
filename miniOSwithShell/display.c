#include "glo.h"

void disp_driver(void)
{
	struct msg_type m;
	char s[80];
	int i,pid;
	while(TRUE)
	{
		receive(ANY, &m);
		pid=m.id;
		phys_copy(pcb[pid].ds, m.m[0], pcb[cur_pid].ds, (int)s, m.m[1]);
		for (i=0;i<m.m[1];i++)
			if (s[i]=='\n') {printc('\n');printc('\r');} 
			else if (s[i]=='\t') {printc(' ');}
			else printc(s[i]);
		m.id=DISPLAY;
		send(pid, &m);
	}
}
