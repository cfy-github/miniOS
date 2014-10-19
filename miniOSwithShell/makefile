kernel:	start2.o lib.o c_lib.o ex1.o kernel.o 
	cc -mi86 -.o -s -com -o game start2.o lib.o c_lib.o ex1.o kernel.o

start2.o:	start2.s
	cc -c -Was-ncc -mi86 -com -o start2.o start2.s
lib.o:	lib.s
	cc -c -Was-ncc -mi86 -com -o lib.o lib.s
ex1.o:	ex1.s
	cc -c -Was-ncc -mi86 -com -o ex1.o ex1.s
c_lib.o:	c_lib.c const.h glo.h type.h gfunc.h
	cc -c -mi86 -com -o c_lib.o c_lib.c 
kernel.o:	kernel.c const.h glo.h type.h gfunc.h
	cc -c -mi86 -com -o kernel.o kernel.c 

load:	
	exec cc -Was-ncc -mi86 -.o -s -com -o load load.s

writeboot2:	writeboot2.c
	cc -o writeboot2 writeboot2.c
clean:
	exec rm *.o
install:
	exec mtools format a:
	exec cc -o writeboot2 writeboot2.c
	exec ./writeboot2
cab:
	exec cc -mi86 -Was-ncc -.o -s -com -o a start2.s lib.s a.c
	exec cc -mi86 -Was-ncc -.o -s -com -o b start2.s lib.s b.c
kel:
	exec cc -mi86 -Was-ncc -.o -s -com -o kernel start2.s lib.s c_lib.c keyboard.c ex1.s message.c display.c sys.c kernel.c
mab:
	exec cc -mi86 -Was-ncc -.o -s -com -o a start2.s keyboard.c lib.s debug.c display.c message.c fork.c e.c
	exec cc -mi86 -Was-ncc -.o -s -com -o b start2.s keyboard.c lib.s debug.c display.c message.c fork.c mm.c
	exec cc -mi86 -Was-ncc -.o -s -com -o c start2.s keyboard.c lib.s debug.c display.c message.c fork.c shell.c

