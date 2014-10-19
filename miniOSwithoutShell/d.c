#include "glo.h"

void main(void)
{
	int t2,t3,t4,t5;
	int i, j;
	int t=fork();
	if (t==0) while (1) printc('b');
	else 
	{
		t2=fork();
		if (t2==0) while(1) printc('c');
		else 
		{
			t3=fork();
			if (t3==0) while (1) printc('d');
			else 
			{
				for(i=0; i<30000; i++)
				{
					if(i == 25000) exit();
					printc('A');
				}	

			}
		}
	}

}
