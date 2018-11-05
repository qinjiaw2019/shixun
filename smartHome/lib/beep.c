#include "../include/beep.h"

int beed_fd;

void beep_star()
{
  //定义蜂鸣器的文件描述符
   int ret;
   //打开蜂鸣器的驱动
   beed_fd =open("/dev/beep",O_RDWR);
   if(beed_fd == -1)
   {
	   perror("beed_fd open false!\n");
	   return ;
   }
   //监管蜂鸣器
	//打开蜂鸣器
	ret=ioctl(beed_fd,BEEP_OFF,BEEP_GPIO);
	if(ret < 0)
	{
		perror("ioctl 111 fasle!\n");
		return ;
	}
}

void beep_stop()
{
	int ret;
	//关闭蜂鸣器
	ret=ioctl(beed_fd,BEEP_ON,BEEP_GPIO);
	if(ret < 0)
	{
		perror("ioctl 222 fasle!\n");
		return ;
	}
    close(beed_fd);//关闭文件
}
int beep(int lay)
{
	//定义蜂鸣器的文件描述符
   int beed_fd;
   int ret;
   //打开蜂鸣器的驱动
   beed_fd =open("/dev/beep",O_RDWR);
   if(beed_fd == -1)
   {
	   perror("beed_fd open false!\n");
	   return -1;
   }
   //监管蜂鸣器
	//打开蜂鸣器
	ret=ioctl(beed_fd,BEEP_OFF,BEEP_GPIO);
	if(ret < 0)
	{
		perror("ioctl 111 fasle!\n");
		return -1;
	}
	sleep(lay);	
	//关闭蜂鸣器
	ret=ioctl(beed_fd,BEEP_ON,BEEP_GPIO);
	if(ret < 0)
	{
		perror("ioctl 222 fasle!\n");
		return -1;
	}
	sleep(lay);
   close(beed_fd);//关闭文件
   return 0;
}

















