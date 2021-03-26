#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    char i=0;
    int fd = open("/dev/gpio_led0",O_RDWR);
	if(fd<0)
	{
		printf("open gpio_led0 error\n");
		return -1;
	}
	//2. 控制蜂鸣器状态
	while(1)
	{
		write(fd,&i,1);
        i++;  
		sleep(1);
		write(fd,&i,1);  
        i--;
		sleep(1);
	}
	
	close(fd);
	return 0;
}




