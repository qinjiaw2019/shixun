#include "led.h"
#include "delay.h"


/**
*	函数名称:LEDInit
*   函数功能:LED初始化
*	输入参数:无
*	返回值:无
**/
void LEDInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//打开时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	
	
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化D端口
	
	delay_init(168);
}
/**
*	函数名称:led_all_off
*   函数功能:熄灭所有的灯
*	输入参数:无
*	返回值:无
**/
void led_all_off()
{
	LEDPD0 = 1;
	LEDPD1 = 1;
	LEDPD3 = 1;
}
/**
*	函数名称:led_all_on
*   函数功能:点亮所有的灯
*	输入参数:无
*	返回值:无
**/
void led_all_on()
{
	LEDPD0 = 0;
	LEDPD1 = 0;
	LEDPD3 = 0;
}

/**
*	函数名称:led
*   函数功能:改变第n个led灯的状态
*	输入参数:n(LED1,LED2,LED3)
*	返回值:无
**/

void led(int n,int state)
{
	if(n==LED1)
	{
		LEDPD0 = state;
		LEDPD3 = 1;
	}
	else if(n==LED2)
	{
		LEDPD0 = 1;
		LEDPD1 = 0;
		LEDPD3 = 1;	
	}
	else if(n==LED3)
	{
		LEDPD0 = 1;
		LEDPD1 = 1;
		LEDPD3 = state;
	}
	else if(n==LED_ALL_OFF){
		LEDPD0 = 1;
		LEDPD1 = 1;
		LEDPD3 = 1;	
	}
	else if(n==LED_ALL_ON)
	{
		LEDPD0 = 0;
		LEDPD1 = 0;
		LEDPD3 = 0;	
	}
	else if(n==LED_ALL)
	{
		LEDPD0 = state;
		LEDPD1 = state;
		LEDPD3 = state;
	}
}
