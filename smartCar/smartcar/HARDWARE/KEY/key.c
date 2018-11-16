#include "key.h"
#include "sys.h"
#include "delay.h"

//按键端口定义
#define key3 PDin(10)
#define key2 PDin(9)
#define key1 PDin(8)

/**
*	函数名称:KeyInit
*   函数功能:按键初始化
*	输入参数:无
*	返回值:无
**/
void KeyInit()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
}

/**
*	函数名称:key_scan
*   函数功能:按键扫描
*	输入参数:无
*	返回值:
*		有效返回值:KEY1,KEY2,KEY3
*		无效返回值:KEY_ERROR
**/
int key_scan()
{
	u8 key1_flag=0,key2_flag=0,key3_flag=0;
	//key1扫描
	if(key1==0)
	{
		delay_ms(5);
		if(key1==0)
		{

				key1_flag=1;
				return KEY1;
			while(key1==0);
		}
	}
	
	//key2扫描
	if(key2==0)
	{
		delay_ms(5);
		if(key2==0)
		{
			 key2_flag=1;

			return KEY2;
			while(key2==0);
		}
	}
	//key3扫描
	if(key3==0)
	{
		delay_ms(5);
		if(key3==0)
		{
			key3_flag=1;
		
				return KEY3;
			while(key3==0);
		}
	}
	
	return KEY_ERROR;
}