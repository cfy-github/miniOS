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
