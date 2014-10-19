#include "glo.h"

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

int strlen(char *s)
{
	int i;
	for (i=0; s[i]!='\0';i++);
	return i;
}

bool strcmp(char *s1, char *s2)
{
	int i, n=strlen(s1);
	if (n!=strlen(s2)) return FALSE;
	for (i=0;i<n;i++) if (s1[i]!=s2[i]) return FALSE;
	return TRUE;
}

void prints(char *s)
{
	struct msg_type m;
	m.m[0]=(int)s;
	m.m[1]=strlen(s);
	send(DISPLAY, &m);
	receive(DISPLAY, &m);
}
