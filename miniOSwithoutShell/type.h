#include "const.h"
#ifndef TYPEDEF
#define TYPEDEF
struct msg_type
{
	int id;
	int m[MSG_LEN-1];
};
struct pcb_type
{
	int ss, sp,ax, bx, cx, dx, bp, si, di, ds, es;
	char state;
};
#endif
