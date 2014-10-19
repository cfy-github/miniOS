#include "glo.h"
#include "us-std.src"
#define ROW_NUM 3

bool shift=FALSE, ctrl=FALSE, alt=FALSE, caplock=FALSE, ext=FALSE;
char capcount=0;


int map_key(int code)
{
	int offset;
	int temp=code;
	bool flag;
	flag=(code>0x80)?1:0;
	if (flag) code-=0x80;
	code = keymap[code * MAP_COLS];
	if (ext) {ext=FALSE; if (temp<30) return 0;}
	if(code==SHIFT && !flag)
	{
		shift=TRUE;
		return 0;
	}
	if (code==SHIFT && flag)
	{
		shift=FALSE;
		return 0;
	}
	else if(code==CTRL && !flag)
	{
		ctrl=TRUE;
		return 0;
	}
	else if (code==CTRL && flag)
	{
		ctrl=FALSE;
		return 0;
	}
	else if(code==CALOCK && !flag) {
		capcount = (capcount + 1) % 2;
		if (capcount) caplock=1-caplock;
		return 0;
	}
	else if(code==ALT && !flag)
	{
		alt=TRUE;
		return 0;
	}
	else if (code==ALT && flag)
	{
		alt=FALSE;
		return 0;
	}
	else if (code==UP)
	{
	}
	else if (code==DOWN)
	{
	}
	else if (code==RIGHT)
	{
	}
	else if (!flag)
	{
		if (alt) offset=2;
		if (ctrl) offset=5;
		if (shift == caplock) offset=0;
		else offset=1;
		return keymap[temp*6+offset];
	}
	return 0;
}

void kb_driver(void)
{
	struct msg_type m;
	char row_buf[ROW_NUM][80];
	int asc, row_ptr=0, buf_num=0;
	int proc_queue[PROC_NUM], proc_addr[PROC_NUM];
	int proc_head=0, proc_tail=0;
	int i,pid, paddr;
	raw_head=0; raw_tail=0;
	while(TRUE)
	{
		receive(ANY, &m);
		if (m.m[0]==INT_TO_KB)
		{
			asc=map_key(raw_buffer[raw_tail]);
			raw_tail = (raw_tail + 1) % RAW_SIZE;
			if (asc==0) {}
			else if (asc==ENTER) {if (buf_num<ROW_NUM) {row_buf[buf_num][row_ptr]='\0';buf_num++;row_ptr=0;}}
			else if (asc==BS || asc==LEFT || asc==DEL) {if (row_ptr>0) row_ptr--;}
			else {if (row_ptr<79) row_buf[buf_num][row_ptr]=asc; row_ptr++;}
		}
		else if (m.m[0]==PROC_TO_KB)
		{
			proc_queue[proc_head]=m.id;
			proc_addr[proc_head]=m.m[1];
			proc_head=(proc_head+1)%PROC_NUM;
		}
		while (buf_num>0 && proc_tail!=proc_head)
		{
			pid=proc_queue[proc_tail];
			paddr=proc_addr[proc_tail];
			proc_tail=(proc_tail+1)%PROC_NUM;
			buf_num--;
			phys_copy(pcb[cur_pid].ds, (int)(row_buf[buf_num]), pcb[pid].ds, paddr, 80);
			m.id=KEYBOARD;
			send(pid, &m);
		}
	} 
}

void kb_int(void)
{
	unsigned char val, code;
	struct msg_type m;
	code = in_byte(0x60);
	val = in_byte(0x61);
	out_byte(0x61, val | 0x80);
	out_byte(0x61, val);
	out_byte(0x20, 0x20);
	if (code == 224 || code==225) {ext=TRUE;return;}
	raw_buffer[raw_head] = code;
	raw_head = (raw_head + 1) % RAW_SIZE;
	if(pcb[KEYBOARD].state == WAITING_R)
	{
		m.m[0]=1;
		send(KEYBOARD, &m);
	}
}

