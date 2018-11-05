#include "../include/timer.h"

void show(int num,int index)
{
	Display_characterX(10,          //x坐标起始点
						   20,          //y坐标起始点
						   "9:41",   //GB2312 中文字符串
						   0xFFFFFF,     //字体颜色值
						   1);	

}

void *pthread_time(void *arg)//子线程
{
	//定义数组
	char time_array[25]={0};
	//时间格式空间
	time_t It;
	
	//获取时间
	while(1)
	{
		It=time(NULL);//清空

		sprintf(time_array,"%s",ctime(&It));

		show(time_array[23],1);
		show(time_array[22],2);
		show(time_array[21],3);
		show(time_array[20],4);
		
		show(time_array[18],6);
		show(time_array[17],7);
		
		
		show(time_array[15],9);
		show(time_array[14],10);
		
		show(time_array[12],12);
		show(time_array[11],13);
		
		show(time_array[9],15);

		//延时
		sleep(1);//秒级延时
	}
	//退出子线程
	pthread_exit(NULL);
}
