#include "../include/config.h"

/*******************************
*研发时间：2018-11-30
*研发工具：NotPad++
*项目名称：智能家居项目
*功能模块：
	    |--beep.h     蜂鸣器模块
        |--bmp.h      BMP图模块
        |--config.h   项目配置文件
        |--file.h     文件操作模块
        |--jpeg.h     JPG图模块
        |--led.h      LED模块
        |--mp3.h      音频模块
        |--mplayer.h  音频库模块
        |--res.h      资源配置文件
        |--tslib.h    触摸模块
        |--ui.h       UI模块
        |--vedio.h    视频模块
*项目研发人员：雷民用，覃家旺
*组长：覃家旺
*    BMP图模块(bmp.c),项目配置文件(config.h),
*    JPG图模块(jpeg.h),文件操作模块(file.c),
*    LED模块(led.c),音频模块(mp3.c),资源配置文件(res.h),
*	 触摸模块(tslib.c),UI模块(ui.c),视频模块(vedio.c)
*组员: 雷民用
*    蜂鸣器模块(beep.c),音频库模块(mplayer.c)
******************************/

struct ts_sample sam;//触摸屏数据结构体
int pos_index = WELCOM;//控制界面跳转变量
int is_login = LOGINOUT;//登录控制变量
char system_pass[5] = {"1234"};//默认密码
int ts;//触摸值

//时间线成
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
		time_array[24]='\0';
		if(pos_index==HOME && is_login!=LOGINOUT)
		{
			/**/
			Clean_Area(10,  //x坐标起始点
					   5,  //y坐标起始点
						800, //绘制的宽度
						20,//绘制的高度
						0x0); //往屏幕指定区域填充颜色
			Display_characterX(10,          //x坐标起始点
						   5,          //y坐标起始点
						   time_array,   //GB2312 中文字符串
						   0xFFFFFF,     //字体颜色值
						   1);	
						   
			printf("%s\n",time_array);

			//延时
			sleep(1);//秒级延时
		}
		
	}
	//退出子线程
	pthread_exit(NULL);
}
int main()
{
	int ret;
	pthread_t threadid;//创建线程号
	
	 ts = ts_open();
	 Init_Font();
	
	/**/
	Clean_Area(10,  //x坐标起始点
               5,  //y坐标起始点
				800, //绘制的宽度
				20,//绘制的高度
				0x0); //往屏幕指定区域填充颜色
				
		//创建线程
		ret=pthread_create(&threadid,NULL,pthread_time,NULL);
		if(ret != 0)
		{
			perror("pthread_create false!\n");
			return -1;//异常推出
		}
	
		
		
	
	while(1)
	{
		
		ts_read(ts,&sam);
		printf("(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
		show();
	
	}
	ts_close(ts);
	UnInit_Font();
	//回收线程
	pthread_join(threadid,NULL);
	return 0;
}