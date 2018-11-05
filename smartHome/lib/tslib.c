/*******************************************
代码功能：触摸子系统
编写者：覃家旺
2018-09-26
********************************************/
#include "../include/tslib.h"

//int ts_fd;//触摸文件描述符
//打开触摸屏
int ts_open()
{
	//打开触摸屏的驱动
	int ts_fd=open("/dev/input/event0",O_RDWR);
	//int ts_fd = open(dev,mode);
	if(ts_fd == -1)
	{
		perror("open ts_fd false!\n");
		return -1;//异常退出
	}
	return ts_fd;
}

int ts_read(int ts,struct ts_sample *sam)
{
	struct input_event tsevent;//初始化结构体
	int count=0;//计数
	while(1)
	{
		//读取坐标值
		read(ts,&tsevent,sizeof(tsevent));
		if(tsevent.type==EV_ABS)
		{
			if(tsevent.code==ABS_X)
			{
				sam->x=tsevent.value;
				count++;
			}
			if(tsevent.code == ABS_Y)
			{
				sam->y=tsevent.value;
				count++;
			}
			if(tsevent.code == ABS_PRESSURE)
			{
				sam->pressure=tsevent.value;
				count++;
			}
			if(count == 2)
			{
				break;
			}
		}
	}
}
//关闭触摸屏
int ts_close(int ts_fd)
{
	close(ts_fd);
	return 0;
}