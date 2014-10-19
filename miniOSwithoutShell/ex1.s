.extern _init
.define _task_switch
.define _curr_pcb
.define _printd
.define _printc
.define _sys_handle
.define _kb_int
.define _ff
_init:
	cli
	xor ax, ax
	mov es, ax
	eseg mov (8*4), #int8
	eseg mov (9*4), #int9
	eseg mov (128*4), #int80
	mov ax, cs
	eseg mov (8*4+2), ax
	eseg mov (9*4+2), ax
	eseg mov (128*4+2), ax
	sti
	ret
int80:
	cli
	push ds
	push cx
	push bx
	push ax
	mov ax, cs
	mov ds, ax
	call _sys_handle
	mov ax, (_ff)
	test ax, ax
	pop ax
	pop bx
	pop cx
	pop ds
	jz jump
	int 0x08
jump:
	sti
	iret
int8:
	cli
	push bx
	cseg mov bx, (_curr_pcb)
	cseg mov (bx), ss
	cseg mov bx, (_curr_pcb)
	cseg mov 4(bx), ax
	cseg mov bx, (_curr_pcb)
	cseg mov 8(bx), cx
	cseg mov bx, (_curr_pcb)
	cseg mov 10(bx), dx
	cseg mov bx, (_curr_pcb)
	cseg mov 12(bx), bp
	cseg mov bx, (_curr_pcb)
	cseg mov 14(bx), si
	cseg mov bx, (_curr_pcb)
	cseg mov 16(bx), di
	cseg mov bx, (_curr_pcb)
	cseg mov 18(bx), ds
	cseg mov bx, (_curr_pcb)
	cseg mov 20(bx), es
	cseg mov di, (_curr_pcb)
	pop bx
	cseg mov 6(di), bx
	cseg mov bx, (_curr_pcb)
	cseg mov 2(bx), sp 
	mov ax, cs
	mov ds, ax
	call _task_switch
	cseg mov bx, (_curr_pcb)
	cseg mov es, 20(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov ds, 18(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov si, 14(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov bp, 12(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov dx, 10(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov cx, 8(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov ax, 4(bx)
	cseg mov bx, (_curr_pcb)
	cseg mov ss, (bx)
	cseg mov di, (_curr_pcb)
	cseg mov bx, 6(di)
	cseg mov di, (_curr_pcb)
	cseg mov sp, 2(di)
	cseg mov di, (_curr_pcb)
	cseg mov di, 16(di)
	sti
	iret
int9:
	cli
	push ax
	push bx
	push cx
	push dx
	push bp
	push si
	push di
	push es
	call _kb_int
	pop es
	pop di
	pop si
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	sti
	iret
