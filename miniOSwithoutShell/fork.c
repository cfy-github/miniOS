#include "glo.h"
struct msg_type m;

int fork(void)
{
	struct msg_type m;
/*	m.id=USER_P1;*/
	m.m[0]=FORK;
	send(MM, &m);
	receive(MM, &m);
	return m.m[1];
}

void exit(void)
{
	struct msg_type m;
	m.m[0]=EXIT;
	send(MM, &m);
	receive(MM, &m);
}

void exec(char* arg, void *f)
{
	int i;
	m.m[0]=EXEC;
	m.m[1]=(int)arg;
	for (i=0;arg[i]!='\0';i++);
	m.m[2]=i+1; 
	printc('{');printd((int)arg);printc('}');
	printc('{');printd((int)f);printc('}');
	m.m[3]=(int)f;
	send(MM, &m);
	receive(MM, &m);
}
