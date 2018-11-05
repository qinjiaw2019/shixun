#include "welcom.h"
#include "login.h"

//返回控制变量
int welcom_back = -1;


//7.时间控制
void show_time(int num,int index)
{
	
	char time_bmp[28]="../pic/ui/number/hour_0.bmp";
	time_bmp[22]=num;
	bmp_show_xy(528-48*(index-1),200,48,106,time_bmp);
}
//8.时间生成工具
void *pthread_welcom_time(void *arg)//子线程
{
//定义数组
	char time_array[25]={0};

	//时间格式空间
	time_t It;
	//获取时间
	while(1)
	{  
		//if(pos_index == WELCOM)
		{
			It=time(NULL);//清空
			//拼接时间
			sprintf(time_array,"%s",ctime(&It));
		
			//秒
			show_time(time_array[18],5);
			show_time(time_array[17],6);
			//显示冒号图片
			bmp_show_xy(528-48*(7-1),200,48,106,"../pic/ui/number/hour_a.bmp");
			//分
			show_time(time_array[15],8);
			show_time(time_array[14],9);
			//显示冒号图片
			bmp_show_xy(528-48*(10-1),200,48,106,"../pic/ui/number/hour_a.bmp");
			//时
			show_time(time_array[12],11);
			show_time(time_array[11],12);

			
			//延时
			sleep(1);//秒级延时
		}
		if(welcom_back ==BACK)break;
		
	}
	//退出子线程
	pthread_exit(NULL);
	
}


//按键控制
void welcome_play()
{
	if(sam.x>=525 && sam.x<=622 && sam.y>=220 && sam.y<=293)//解锁按键
	{
		welcom_back=BACK;	
	
	}
}

void welcom_show()
{
	pthread_t threadId;//线程号
	int ret;
	
	bmp_show(IMG_WELCOME_BG);	
	sam.x = sam.y = -1;
	welcom_back= -1;

	
	//线程
		//创建线程
		ret = pthread_create(&threadId,NULL,pthread_welcom_time,NULL);
		if(ret != 0)
		{
			perror("pathread_create false!\n");
		
		}
	
	while(welcom_back==-1)
	{
		ts_read(ts,&sam);
		welcome_play();
		printf("welcom--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
	}
	
	if(is_login==LOGINED)//如果已经登录
	{
		bmp_show(IMG_HOME_BG);//显示首页
		menu();//首页菜单
	}
	else
	{
		show_login();//登录界面
	}
	//回收线程
	pthread_join(threadId,NULL);
}