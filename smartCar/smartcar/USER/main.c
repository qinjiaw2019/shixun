#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "uart1.h"
#include "hcsr04.h"
#include <string.h>
#include "wifi.h"
#include "path.h"
#include "motor.h"
#include "uart2.h"
#include "timer.h"
#include "led.h"

CAR_InitStructure carinfo;

static unsigned int cpu_counter = 0; 
char s[100];
//超声波测量处理
void sonic_measure_handler()
{
	//获得超声波的数据
	carinfo.sonic_legnth = hcsr04_measure();
	path_handler(&carinfo);
}
void test_print()
{
	char s[1000];
	
	//old sonic_length state
	sprintf(s,"%f,%f,%d|",carinfo.pre_sonic_length ,carinfo.sonic_legnth,carinfo.state);
	uart2_sendstr(s);
	//uart1_sendstr(s);
}

//初始化处理
void init_handler()
{
	delay_init(168);//延时初始化
	hcsr04_Init();//超声波模块初始化
	MotorChekInit();//电机驱动初始化
	WifiChek_Init(115200);//WIFI初始化
	
	//小车信息初始化
	carinfo.sonic_legnth = 0;
	carinfo.pre_sonic_length = carinfo.sonic_legnth;
	carinfo.state = CAR_STOP;
}
int main(void)
{
	uart1_init(115200);



	init_handler();
	led(LED_ALL,1);
	
	
	while(1)
	{
		cpu_counter++;
		if(cpu_counter>=3)
		{
			carinfo.pre_sonic_length = carinfo.sonic_legnth;
			cpu_counter=0;
		}
		sprintf(s,"old len:%f new len:%f  %f  cpu_counter:%d========\r\n",carinfo.pre_sonic_length,carinfo.sonic_legnth,(carinfo.pre_sonic_length-carinfo.sonic_legnth),cpu_counter);
			uart1_sendstr(s);
		test_print();
		sonic_measure_handler();
		
	}
	return 0;
}

void timer2_handler(int state)
{

	
}

