#include "gfunc.h"
#include "glo.h"

int main(void)
{
	int i,j,t;
	struct msg_type m;
	char buf[80];
	while (1)
	{
		m.id=USER_P1;
		m.m[0]=0;
		m.m[1]=(int)buf;
		send(KEYBOARD, &m);
		receive(KEYBOARD, &m);
		m.id=USER_P1;
		m.m[0]=(int)buf;
		m.m[1]=strlen(buf);
		send(DISPLAY, &m);
		receive(DISPLAY, &m);
		buf[0]='\n';
		buf[1]='\0';
		m.m[1]=strlen(buf);
		m.id=USER_P1;
		m.m[0]=(int)(buf);
		send(DISPLAY, &m);
		receive(DISPLAY, &m);
	}
}
