#include "gfunc.h"
#include "glo.h"

int main(void)
{
	int i,j,t;
	struct msg_type m;
	printc('c');
	while (1)
	{
		receive(ANY, &m);
		t = m.m[0];
		printc('<');
		printc('C');
		printc(t+'0');
		printc('>');
		for (i=0;i<30000;i++) for (j=0;j<200;j++);
		m.m[0] = 4;
		send(1, &m);
	}
}
