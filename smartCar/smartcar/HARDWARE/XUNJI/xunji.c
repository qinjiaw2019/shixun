
#include "sys.h"   
#include "delay.h"	
#include "xunji.h"
#include "motor.h"

#define IN1 PEout(8)
#define IN2 PEout(9)
#define IN3 PEout(10)
#define IN4 PEout(11)
#define IN5 PEout(12)
#define IN6 PEout(13)
#define IN7 PEout(14)
#define IN8 PEout(15)

#define xunji1 PCin(0)
#define xunji2 PCin(1)
#define xunji3 PCin(2)
#define xunji4 PCin(3)
#define xunji5 PCin(4)
#define xunji6 PCin(5)

#define ENA1 PBout(0)
#define ENB2 PBout(13)

void XUNJI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    ENA1 = 0;
    IN1 = 0;
    IN2 = 0;
    IN3 = 0;
    IN4 = 0;
    
    ENB2 = 0;
    IN5 = 0;
    IN6 = 0;
    IN7 = 0;
    IN8 = 0;
    
    RCC->AHB1ENR|=1<<2;//使能PORTC时钟 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure); //初始化PA9，PA10
	//GPIO_Set(GPIOC,PIN0|PIN1|PIN2|PIN3|PIN4|PIN5,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PC0--PC5设置,上拉输入
}

void xunji(void)
{
		
}
