#include "type.h"
#include "gfunc.h"
#include "glo.h"

int temp, tmp_add1, tmp_add2;
void send(int pid, struct msg_type* m)
{
	send_ask(pid, m);
}

void receive(int pid, struct msg_type* m)
{
	receive_ask(pid, m);
}

void sys_handle(int type, int pid, struct msg_type* m)
{
	int i;
	if(type == 1)
	{
		if (pcb[pid].state==WAITING_R && (msg[pid].id==cur_pid || msg[pid].id == ANY)) 
		{	
			tmp_add1 = (int)m;
			tmp_add2 = msg[pid].m[0];
			phys_copy(0x8000, (int)(&(cur_pid)), pcb[cur_pid].ds, (int)(&(m->id)), 1);
			phys_copy(pcb[cur_pid].ds, tmp_add1, pcb[pid].ds, tmp_add2, 2*(MSG_LEN -1)); 
			pcb[pid].state=BLOCKED;
			ff = FALSE;
		}
		else /*if (pcb[pid].state!=WAITING_R || (pcb[pid].state == WAITING_R && msg[pid].id!=cur_pid)) */
		{
			pcb[cur_pid].state=WAITING_S;
			msg[cur_pid].id = pid;
			msg[cur_pid].m[0] = (int)m;
			ff = TRUE;
		}
	}
	else
	{
		if (pid == ANY)
		{	
			for(i=0; i<MSG_LEN-1; i++)
			{
				if(pcb[i].state == WAITING_S && msg[i].id == cur_pid)
				{
					tmp_add1 = msg[i].m[0];
					tmp_add2 = (int)m;
					phys_copy(pcb[i].ds, tmp_add1, pcb[cur_pid].ds, tmp_add2, 2*(MSG_LEN-1)); 
					pcb[i].state=BLOCKED;
					ff = FALSE;
					break;
				}
			}
			if(i == MSG_LEN-1)
			{
				pcb[cur_pid].state = WAITING_R;
				msg[cur_pid].id = ANY;
				msg[cur_pid].m[0] = (int)m;
				ff =TRUE;
			}
		}
		else if (pcb[pid].state!=WAITING_S || (pcb[pid].state == WAITING_S && msg[pid].id!=cur_pid)) 
		{
			pcb[cur_pid].state = WAITING_R;
			msg[cur_pid].id = pid;
			msg[cur_pid].m[0] = (int)m;
			ff = TRUE;
		}
		else if (pcb[pid].state==WAITING_S && msg[pid].id==cur_pid) 
		{
			tmp_add1 = msg[pid].m[0];
			tmp_add2 = (int)m;
			phys_copy(pcb[pid].ds, tmp_add1, pcb[cur_pid].ds, tmp_add2, 2*(MSG_LEN-1)); 
			pcb[pid].state=BLOCKED;
			ff = FALSE;
		}
	}
}
