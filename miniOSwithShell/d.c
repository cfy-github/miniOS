#include "glo.h"

void main(void)
{
	int t2,t3,t4,t5;
	int t=fork();
	if (t==0) while (1) printc('b');
	else 
	{
		exit();
/*		t2=fork();
		if (t2==0) while(1) printc('c');
		else 
		{
			t3=fork();
			if (t3==0) while (1) printc('d');
			else 
			{
				while (1) printc('a');

			}
		}*/
	}

}
