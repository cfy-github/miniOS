.extern _printc
.extern _out_byte
.extern _in_byte
.extern _lock
.extern _unlock
.extern _readsector
.extern _init_psw
.extern _jumpf
.extern _send_ask
.extern _receive_ask
.extern _phys_copy
.extern _init_t_psw
.extern _exec_stack
.define _kb_driver
.define _curr_pcb
_exec_stack:
	push bp
	mov bp, sp
	push ax
	push bx
	push dx
	push cx
	push si
	mov si, ss
	mov dx, sp
	mov ax, 4(bp)
	mov bx, 6(bp)
	mov cx, 8(bp)
	mov ss, ax
	mov sp, bx
	push bx
	push bx
	pushf
	push ax
	push cx
	mov ss, si
	mov sp ,dx
	pop si
	pop cx
	pop dx
	pop bx
	pop ax
	pop bp
	ret
_init_t_psw:
	push bp
	mov bp, sp
	push ax
	push bx
	push dx
	mov ax, 4(bp)
	mov bx, sp
	mov sp, ax
	pushf
	pop dx
	xor dx, #0x0200
	push dx
	push cs
	mov dx, 6(bp)
	push dx
	mov sp, bx
	pop dx
	pop bx
	pop ax
	pop bp
	ret
_phys_copy:
	push bp
	mov bp, sp
	push ax
	push bx
	push cx
	push dx
	push si
	push di
	push es
	mov bx, 4(bp)
	mov di, 6(bp)
	mov dx, 8(bp)
	mov si, 10(bp)
	mov cx, 12(bp)
lp:	
    	test cx, cx
	jz done
	mov es, bx
	eseg mov ax, (di)
	mov es, dx
	eseg mov (si), ax
	inc di
	inc si
	dec cx
	jmp lp
done:	pop es
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax	
	pop bp
	ret
_send_ask:
	cli
	push bp
	mov bp,sp
	push ax
	push bx
	push cx
	mov ax, #1
	mov bx, 4(bp)
	mov cx, 6(bp)
	int 0x80
	pop cx
	pop bx
	pop ax
	pop bp
	sti
	ret
_receive_ask:
	cli
	push bp
	mov bp, sp
	push ax
	push bx
	push cx
	mov ax, #2
	mov bx, 4(bp)
	mov cx, 6(bp)
	int 0x80
	pop cx
	pop bx
	pop ax
	pop bp
	sti
	ret
_jumpf:
	jmpf 0x0000, 0x1000
_init_psw:
	push bp
	mov bp, sp
	push ax
	push bx
	push cx
	push dx
	mov ax, 4(bp)
	mov bx, sp
	mov cx, ss
	mov sp, #0xFFFF
	mov ss, ax
	pushf
	pop dx
	xor dx, #0x0200
	push dx
	mov dx, ax
	push dx
	mov dx, #0x0000
	push dx
	mov ss, cx
	mov sp, bx
	pop dx
	pop cx 
	pop bx
	pop ax
	pop bp
	ret
_readsector:
	push bp
	mov bp, sp
	push ax
	push bx
	push cx
	push dx
	push es
	movb ah, #0x02
	movb al, 14(bp)
	movb dl, #0x00
	movb dh, 8(bp)
	movb ch, 10(bp)
	movb cl, 12(bp)
	mov bx, 4(bp)
	mov es, bx
	mov bx, 6(bp)
	int 0x13
	pop es
	pop dx
	pop cx
	pop bx
	pop ax
	pop bp
	ret
_printc:
	push bp
	mov bp, sp
	push ax
	push bx
	movb al, 4(bp)
	movb ah, #0x0E
	mov bx, #0x0001
	int 0x10
	pop bx
	pop ax
	pop bp
	ret
_out_byte:
	push bp
	mov bp, sp
	push dx
	push ax
	xor ax, ax
	movb al, 6(bp)
	mov dx, 4(bp)
	outb dx
	pop ax
	pop dx
	pop bp
	ret
_in_byte:
	push bp
	mov bp, sp
	push dx
	mov dx, 4(bp)
	inb dx
	pop dx
	pop bp
	ret
_lock:
	cli
	ret
_unlock:
	sti
	ret
