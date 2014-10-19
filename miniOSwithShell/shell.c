#include "gfunc.h"
#include "glo.h"

char str[]="Successful Exec!\n#";

void printf(char * s)
{
	struct msg_type m;
	prints(str);
	receive(ANY, &m);
	prints("Successful exit!\n#");
	exit();
}

int main(void)
{
	int i,j,t=0;
	int stack[5];
	struct msg_type m;
	char buf[80];
	while (1)
	{
		printc('#');
		m.m[0]=PROC_TO_KB;
		m.m[1]=(int)buf;
		send(KEYBOARD, &m);
		receive(KEYBOARD, &m);
		prints(buf);
		prints("\n");
		if (strcmp(buf, "ps"))
		{
			m.m[0]=PS;
			send(SYSCALL, &m);
			receive(SYSCALL, &m);
		}
		else if (strcmp(buf, "fork"))
		{
			stack[t]=fork();
			if (stack[t]==0) {prints("Successful Fork!\n");exec(str, (void *)printf);}
			if (stack[t]==-1) prints("Fork unsuccessful!\n"); else t++; 
		}
		else if (strcmp(buf, "kill"))
		{
			if (t==0) prints("Not fork yet...\n");
			else {send(stack[--t], &m);}
		}
		else if (strcmp(buf, "help"))
		{
			prints("Following command(s) are supported by this simple shell:\n");
			prints("[help]  : List all the commands and explain them.\n");
			prints("[ps]    : List all the processes.\n");
			prints("[fork]  : First, the shell fork itself, "); 
			prints("then the child process excecute exec() and replace itself ");
			prints("with a function that print \"Successful exec\" on the screen, ");
			prints("following with a receive() that make it blocked.\n");
			prints("[kill]  : If one or more fork has been typed in, this command ");
			prints("send a message to one blocked child and destroy it by exit().\n");
			prints("[mem]   : List the allocation of memory.\n");
			prints("[copyright] : Do as the name says.\n");
		}
		else if (strcmp(buf, "mem"))
		{
			m.m[0]=MEM;
			send(SYSCALL, &m);
			receive(SYSCALL, &m);
		}
		else if (strcmp(buf, "chenjia"))
		{
			prints("Yeah! ChenJia!\n");
		}
		else if (strcmp(buf, "chenkang"))
		{
			prints("ChenKang is SX\n");
		}
		else if (strcmp(buf, "copyright"))
		{
			prints("COPYRIGHT @ Feiyu & Grieve\n");
		}
		else
		{
			prints("Illegal command...\n");
		}
	}
}
