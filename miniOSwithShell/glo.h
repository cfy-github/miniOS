#include "const.h"
#include "type.h"
#include "gfunc.h"
#ifndef GLODEF
#define GLODEF
struct pcb_type pcb[PROC_NUM];
struct pcb_type *curr_pcb;
int cur_pid;
struct msg_type msg[PROC_NUM];
int raw_buffer[RAW_SIZE];
int raw_head, raw_tail;
int ff;
int pnum;
bool mem[9];
int palloc[PROC_NUM];
bool proc[PROC_NUM];
#endif
