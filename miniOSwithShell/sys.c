#include "glo.h"
int tmp[80];

void sys_driver(void)
{
	struct msg_type m;
	int pid, id,i,j,k,o,len;
	bool flag=FALSE;
	char disp[80];
	unsigned int tmem;
	while (TRUE)
	{
		receive(ANY, &m);
		pid=m.id;
		if (m.m[0]==FORK)
		{
			for (i=1;i<6;i++) if (!mem[i])
			{
				for (k=6;k<11;k++) if (!proc[k]) break;
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
				send(pid, &m); 
				break;
			}
			if (i>=6 || flag) 
			{
				prints("Cannot fork!\n\r");
				m.m[0]=-1;
				send(pid, &m);
			}
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
		else if (m.m[0]==EXIT)
		{
			id=m.m[1];
			mem[palloc[id]]=FALSE;
			palloc[id]=0;
			proc[id]=FALSE;	
			pcb[id].state=RUNNING;
		}
		else if (m.m[0]==PS)
		{
			pid=m.id;
			strcat(disp, 0, "PID  PROC_NAME    PROC_STATE        MEMORY_ALLOC\n");
			m.m[0]=(int)disp;
			m.m[1]=strlen(disp);
			send(DISPLAY, &m);
			receive(DISPLAY, &m);
			strcat(disp, 0, "--------------------------------------------------\n");
			m.m[0]=(int)disp;
			m.m[1]=strlen(disp);
			send(DISPLAY, &m);
			receive(DISPLAY, &m);
			for (i=0;i<PROC_NUM;i++)
			{
				if (!proc[i]) continue;
				disp[0]=i+'0';if (disp[0]>'9') disp[0]='A';
				disp[1]=disp[2]=disp[3]=disp[4]=' ';
				if (i==0) strcat(disp, 5, "idle         ");
				else if (i==KEYBOARD) strcat(disp, 5, "kb_driver    ");
				else if (i==DISPLAY) strcat(disp, 5, "disp_driver  ");
				else if (i==SYSCALL) strcat(disp, 5, "sys_driver   ");
				else if (i==MM) strcat(disp, 5, "mm           ");
				else if (i==SHELL) strcat(disp, 5, "shell        ");
				else if (i==USER_P1) strcat(disp, 5, "user proc1   ");
				else if (i==USER_P2) strcat(disp, 5, "user proc2   ");
				else if (i==USER_P3) strcat(disp, 5, "user proc3   ");
				else if (i==USER_P4) strcat(disp, 5, "user proc4   ");
				else if (i==USER_P5) strcat(disp, 5, "user proc5   ");
				len=strlen(disp);
				if (pcb[i].state==RUNNING) strcat(disp, len, "RUNNING           ");
				else if (pcb[i].state==BLOCKED) strcat(disp, len, "WAITING           ");
				else if (pcb[i].state==WAITING_S) strcat(disp, len, "BLOCK_ON_SEND     ");
				else if (pcb[i].state==WAITING_R) strcat(disp, len, "BLOCK_ON_RECEIVE  ");
				len=strlen(disp);
				disp[len++]=palloc[i]+'0';
				strcat(disp, len, "000 - ");
				len=strlen(disp);
				disp[len++]=palloc[i]+'0';
				strcat(disp, len, "FFF\n");
				m.m[0]=(int)disp;
				m.m[1]=strlen(disp);
				send(DISPLAY, &m);
				receive(DISPLAY, &m);
			}
			send(pid, &m);
		}
		else if (m.m[0]=MEM)
		{
			pid=m.id;
			for (i=1;i<9;i++) 
			{
				disp[0]=i+'0';
				strcat(disp, 1, "000 - ");
				len=strlen(disp);
				disp[len++]=i+'0';
				strcat(disp, len, "FFF :  ");
				len=strlen(disp);
				if (!mem[i]) strcat(disp, len, "Unused\n");
				else
				{
					for (j=0;j<PROC_NUM;j++) if (palloc[j]==i) break;
					strcat(disp, len, "PROCESS_");
					len=strlen(disp);
					disp[len++]=(j>9)?('A'):(j+'0');
					disp[len++]='\n';
					disp[len++]='\0';
				}			
				m.m[0]=(int)disp;
				m.m[1]=strlen(disp);
				send(DISPLAY, &m);
				receive(DISPLAY, &m);
			}
			send(pid, &m);
		}
	}
}
