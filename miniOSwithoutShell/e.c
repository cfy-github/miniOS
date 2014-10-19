#include "glo.h"

char str[] = "Hello, OS world!";

void printf(char *s)
{
	char a[30];
	int len,i;
	struct msg_type m;
	len = strlen(s);
	for (i=0;i<len;i++) a[i]=s[i];
	a[len]='\n';
	a[++len]='\0';
	while (1)
	{ 
		m.m[0]=(int)a;
		m.m[1]=len;
		send(DISPLAY, &m);
		receive(DISPLAY, &m);
	}
	exit();
}

void main(void)
{
	int t1;
	int t=fork();
	if (t==0) exec(str, (void *) printf);
	else
	{
		while (1) printc('b');
	}
}
