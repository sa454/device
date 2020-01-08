#include<stdio.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
 #include <unistd.h>
#define NUM 10
unsigned buff[NUM]="hello"; 
unsigned char bbuff[6];
int main()
{       int i;
	int fd;
	fd = open("/dev/test0",O_RDWR);

	if(fd<0)
	{
		printf("device not found");
		return fd;
	}
	write(fd,buff,sizeof(buff);
	read(fd,bbuff,6);
        for(i=0;i<6;i++)
	      printf("USERSIDE:%c\n",bbuff[i]);
             return 0;
	
}

