#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
	int r,w,r2,r3,r4,r5;
	char buf[550], buf2[4200], buf3[4200], buf4[8300], buf5[4200];
	r=open("load",O_RDONLY);
	r2=open("a",O_RDONLY);
	r3=open("b",O_RDONLY);
	r4=open("kernel", O_RDONLY);
	r5=open("c", O_RDONLY);
	w=open("/dev/fd0",O_RDWR);
	read(r,buf,446+32);
	read(r4,buf4,8192+32);
	buf[510+32]=0x55;buf[511+32]=0xAA;
	write(w,(buf+32),512);
	write(w,(buf4+32),8192);
	read(r2, buf2, 4096+32);
	write(w,(buf2+32),4096);
	read(r3, buf3, 4096+32);
	write(w, buf3+32, 4096);
	read(r5, buf5, 4096+32);
	write(w, buf5+32, 4096);
	close(r);
	close(r2);
	close(r3);
	close(r4);
	close(w);
	return 0;
}
