#include "../include/led.h"


int led_fd;//led灯的文件描述符
 
int led_open()
{
	//打开led灯的驱动
   led_fd=open("/dev/Led",O_RDWR);
   if(led_fd == -1)
   {
	   perror("led_fd open false!\n");
	   return -1;
   }
}

void led_all_off()
{
	ioctl(led_fd,LED1,LED_OFF);
	ioctl(led_fd,LED2,LED_OFF);
	ioctl(led_fd,LED3,LED_OFF);
	ioctl(led_fd,LED4,LED_OFF);
}
void led_all_on()
{
	ioctl(led_fd,LED1,LED_ON);
	ioctl(led_fd,LED2,LED_ON);
	ioctl(led_fd,LED3,LED_ON);
	ioctl(led_fd,LED4,LED_ON);
}
void led(int index,int mode)
{
	
	if(index==1)
	{
		if(mode==1)ioctl(led_fd,LED1,LED_ON);
		else ioctl(led_fd,LED1,LED_OFF);
	}
	else if(index==2)
	{
		if(mode==1)ioctl(led_fd,LED2,LED_ON);
		else ioctl(led_fd,LED2,LED_OFF);
	}
	else if(index==3)
	{
		if(mode==1)ioctl(led_fd,LED3,LED_ON);
		else ioctl(led_fd,LED3,LED_OFF);
	}
	else if(index==4)
	{
		if(mode==1)ioctl(led_fd,LED4,LED_ON);
		else ioctl(led_fd,LED4,LED_OFF);
	}
			

}