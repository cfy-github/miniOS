#include "gfunc.h"
#include "glo.h"

int main(void)
{
	int i,j,pid;
	struct msg_type m;
	while (1)
	{
		receive(ANY, &m);
		pid = m.id;
		if (m.m[0]==FORK)
		{
			m.id=MM;
			m.m[0]=FORK;
			m.m[1]=pid;	
			send(SYSCALL, &m);
			receive(SYSCALL, &m);
			j=m.m[0];
			if (j!=-1) 
			{
				m.id=MM;
				m.m[1]=0;
				send(j, &m);
			}
			m.id=MM;
			m.m[1]=j;
			send(pid, &m);
		}
		else if (m.m[0]==EXEC)
		{
			m.m[0]=EXEC;
			m.m[4]=m.m[3];
			m.m[3]=m.m[2];
			m.m[2]=m.m[1];
			m.m[1]=pid;
			m.id=MM;
			send(SYSCALL, &m);
			receive(SYSCALL, &m);
			m.id=MM;
			send(pid, &m);
		}
		else if (m.m[0]==EXIT)
		{
			m.m[0] = EXIT;
			m.m[1]=pid;
			m.id=MM;
			send(SYSCALL, &m);
		}

	}
}
