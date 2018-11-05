#include "led_m.h"

int led_back = -1;
int led_index[6]={0,0,0,0};
//点亮LED灯
void led_lighting(char *s)
{
	bmp_show_xy(130,142,108,116,"../pic/ui/led_off.bmp");
	bmp_show_xy(130+108+3,142,108,116,"../pic/ui/led_off.bmp");
	bmp_show_xy(130+108*2+3*2,142,108,116,"../pic/ui/led_off.bmp");
	bmp_show_xy(130+108*3+3*3,142,108,116,"../pic/ui/led_off.bmp");	
	
	//蜂鸣器
	bmp_show_xy(606,346,60,60,"../pic/ui/silence.bmp");
	
}
//led控制
void led_play()
{
	char tmp[50];
	if(sam.x>=130 && sam.x<=130+108 && sam.y>=142 && sam.y<=142+116 && sam.pressure>0)//led1
	{
		
		
	
	
		
		if(led_index[0]==0)
		{
			bmp_show_xy(130,142,108,116,"../pic/ui/led_on.bmp");
			led(1,1);
			led_index[0] = 1;
			printf("led1-on\n");
		}else{
			led(1,0);
			bmp_show_xy(130,142,108,116,"../pic/ui/led_off.bmp");
			led_index[0] = 0;
			printf("led1-off\n");
		}/**/
	}
	else if(sam.x>=130+108+3 && sam.x<=130+108*2+3 && sam.y>=142 && sam.y<=142+116 && sam.pressure>0)//led2
	{
		if(led_index[1]==0)
		{
			led(2,1);
			bmp_show_xy(130+108+3,142,108,116,"../pic/ui/led_on.bmp");
			led_index[1] = 1;
		}else{
			led(2,0);
			bmp_show_xy(130+108+3,142,108,116,"../pic/ui/led_off.bmp");
			led_index[1] = 0;
		}
		printf("led2\n");
	}
	else if(sam.x>=130+108*2+3*2 && sam.x<=130+108*3+3*2 && sam.y>=142 && sam.y<=142+116 && sam.pressure>0)//led3
	{
		if(led_index[2]==0)
		{
			led(3,1);
			bmp_show_xy(130+108*2+3*2,142,108,116,"../pic/ui/led_on.bmp");
			led_index[2] = 1;
		}else{
			led(3,0);
			bmp_show_xy(130+108*2+3*2,142,108,116,"../pic/ui/led_off.bmp");
			led_index[2] = 0;
		}
		
	}
	else if(sam.x>=130+108*3+3*3 && sam.x<=130+108*4+3*3 && sam.y>=142 && sam.y<=142+116 && sam.pressure>0)//led4
	{
		if(led_index[3]==0)
		{
			led(4,1);
			bmp_show_xy(130+108*3+3*3,142,108,116,"../pic/ui/led_on.bmp");	
			led_index[3] = 1;
		}else{
			led(4,0);
			bmp_show_xy(130+108*3+3*3,142,108,116,"../pic/ui/led_off.bmp");	
			led_index[3] = 0;
		}
	}
	else if(sam.x>=606 && sam.x<=606+60 && sam.y>=346 && sam.y<=346+60 && sam.pressure>0)//蜂鸣器
	{
		
		if(led_index[3]==0)
		{
			beep_stop();
			bmp_show_xy(606,346,60,60,"../pic/ui/silence.bmp");	
			led_index[3] = 1;
		}else{
			beep_star();
			
			bmp_show_xy(606,346,60,60,"../pic/ui/silence_on.bmp");
			led_index[3] = 0;
		}
		
	}
	else if(sam.x>=0 && sam.x<=47 && sam.y<=19 && sam.y>=0)//退出
	{
		led_back=BACK;
	}
	/*
	Init_Font();
	sprintf(tmp,"x:%d  y:%d  pressure:%d",sam.x,sam.y,sam.pressure);
	
			Clean_Area(0,  //x坐标起始点
               480-20,  //y坐标起始点
				800, //绘制的宽度
				20,//绘制的高度
				0x0); //往屏幕指定区域填充颜色
			Display_characterX(5,          //x坐标起始点
						   480-15,          //y坐标起始点
						   tmp,   //GB2312 中文字符串
						   0xFFFFFF,     //字体颜色值
						   1);	
	UnInit_Font();*/
	printf("led--(%d,%d,%d)\n",sam.x,sam.y,sam.pressure);
}


void led_show()
{

				
	bmp_show(IMG_HOME_BG);
	sam.y = sam.x = -1;
	led_back = -1;
	led_open();
	led_all_off();
	//led_lighting();
	//bmp_show_xy(130,142,108,116,"../pic/ui/led_off.bmp");
	led_lighting(NULL);
	//监测led的状态
	led_index[0]=0;
	led_index[1]=0;
	led_index[2]=0;
	led_index[3]=0;
	led_index[4]=0;
	
	
	while(led_back==-1)
	{
		ts_read(ts,&sam);
		led_play();
	}
	beep_stop();
	led_all_off();
	
}