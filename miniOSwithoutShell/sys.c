#include "glo.h"
int tmp[80];

void sys_driver(void)
{
	struct msg_type m;
	int pid, id,i,j,k,o;
	bool flag=FALSE;
	unsigned int tmem;
	while (TRUE)
	{
		receive(ANY, &m);
		pid=m.id;
		if (m.m[0]==FORK)
		{
			for (i=1;i<7;i++) if (!mem[i])
			{
				for (k=5;k<11;k++) if (!proc[k]) break;
				if (k==11) {flag=TRUE;break;}
				palloc[k]=i;
				proc[k]=TRUE;
				id=m.m[1];
				pcb[k].ss=pcb[id].ss;
				pcb[k].sp=pcb[id].sp;
				pcb[k].ax=pcb[id].ax;
				pcb[k].bx=pcb[id].bx;
				pcb[k].cx=pcb[id].cx;
				pcb[k].dx=pcb[id].dx;
				pcb[k].bp=pcb[id].bp;
				pcb[k].si=pcb[id].si;
				pcb[k].di=pcb[id].di;
				pcb[k].es=pcb[id].es;
				pcb[k].state=pcb[id].state;
				msg[k].id=msg[id].id;
				tmem=(unsigned)i<<12;
				for (j=0;j<MSG_LEN-1;j++) msg[k].m[j]=msg[id].m[j];
				pcb[k].ds=tmem;
				pcb[k].ss=tmem;
				phys_copy(pcb[id].ds, 0, pcb[k].ds, 0, 0x8000);
				phys_copy(pcb[id].ds, 0x8000, pcb[k].ds, 0x8000, 0x8000);
				mem[i]=TRUE;
				m.id=SYSCALL;
				m.m[0]=k;
				pnum++;
				printc('~');
				send(pid, &m); 
				break;
			}
			if (i==7 || flag) {printc('!');lock();}
		}
		else if (m.m[0]==EXEC)
		{
			pid=m.m[1];
			i=0xFFFF-m.m[3]+1;
			phys_copy(pcb[pid].ds, m.m[2], pcb[pid].ds, 0xFFFF-m.m[3]+1, m.m[3]);
			exec_stack(pcb[pid].ss, i, m.m[4]);
			pcb[pid].sp=0xFFFF-m.m[3]-9;
			id = m.id;
			m.id = SYSCALL;
			send(id, &m);
		}
		else if (m.m[0]=EXIT)
		{
			id=m.m[1];
			mem[palloc[id]]=FALSE;
			palloc[id]=0;
			proc[id]=FALSE;	
			pcb[id].state=RUNNING;
		}
	}
}
