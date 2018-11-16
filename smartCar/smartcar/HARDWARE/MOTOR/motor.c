#include  "motor.h"
#include "sys.h"
#include "delay.h"

#define IN1 PEout(8)
#define IN2 PEout(9)
#define IN3 PEout(10)
#define IN4 PEout(11)
#define IN5 PEout(12)
#define IN6 PEout(13)
#define IN7 PEout(14)
#define IN8 PEout(15)

#define ENA1 PBout(0)
#define ENB2 PBout(13)

//电机初始化
void 	MotorChekInit()
{
	GPIO_InitTypeDef  GPIOE_InitStructure,GPIOB_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIOE_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|
																GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIOE_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出
    GPIOE_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIOE_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIOE_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOE, &GPIOE_InitStructure);//初始化
	
	GPIOB_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_13;
    GPIOB_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出功能
    GPIOB_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输入
    GPIOB_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIOB_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOB, &GPIOB_InitStructure);//初始化
	
	PEout(8)=0;
	PEout(9)=0;
	PEout(10)=0;
	PEout(11)=0;
	PEout(12)=0;
	PEout(13)=0;
	PEout(14)=0;
	PEout(15)=0;
	PBout(0)=0;
	PBout(13)=0;
	
	ENA1 = ENB2 = 1;
}



//左前轮驱动
void motor_left_wheel_front(int mode)
{
	if(mode==MOTOR_RUN_FRONT)
	{
		IN1 = 1;
		IN2 = 0;
	}else if(mode==MOTOR_RUN_BACK)
	{
		IN1 = 0;
		IN2 = 1;
	}else if(mode==MOTOR_STOP)
	{
		IN1 = 1;
		IN2 = 1;
	}

} 
//左后轮驱动
void motor_left_wheel_back(int mode)
{
	if(mode==MOTOR_RUN_FRONT)
	{
		IN3 = 0;
		IN4 = 1;
	}else if(mode==MOTOR_RUN_BACK)
	{
		IN3 = 1;
		IN4 = 0;
	}else if(mode==MOTOR_STOP)
	{
		IN3 = 1;
		IN4 = 1;
	}
}

//右前轮驱动
void motor_right_wheel_front(int mode)
{
	
	if(mode==MOTOR_RUN_FRONT)
	{
		IN5 = 1;
		IN6 = 0;
	}else if(mode==MOTOR_RUN_BACK)
	{
		IN5 = 0;
		IN6 = 1;
	}else if(mode==MOTOR_STOP)
	{
		IN5 = 1;
		IN6 = 1;
	}

} 
//右后轮驱动
void motor_right_wheel_back(int mode)
{
	if(mode==MOTOR_RUN_FRONT)
	{
		IN7 = 0;
		IN8 = 1;
	}else if(mode==MOTOR_RUN_BACK)
	{
		IN7 = 1;
		IN8 = 0;
	}else if(mode==MOTOR_STOP)
	{
		IN7 = 1;
		IN8 = 1;
	}
}

//左轮驱动
void motor_left_wheel(int mode)
{
	motor_left_wheel_front(mode);
	motor_left_wheel_back(mode);
}
void motor_right_wheel(int mode)
{
	motor_right_wheel_front(mode);
	motor_right_wheel_back(mode);
}
void motor_wheel(int wheel,int mode)
{
	if(wheel==WHEEL1)
	{
		motor_left_wheel_front(mode);
	}
	else if(wheel==WHEEL2)
	{
		motor_right_wheel_front(mode);
	}
	else if(wheel==WHEEL3)
	{
		motor_left_wheel_back(mode);
	}
	else if(wheel==WHEEL4)
	{
		motor_right_wheel_back(mode);
	}
	else if(wheel==WHEEL_LEFT)
	{
		motor_left_wheel(mode);
	}
	else if(wheel==WHEEL_RIGHT)
	{
		motor_right_wheel(mode);
	}
	else if(wheel==WHEEL_ALL)
	{
		motor_left_wheel(mode);
		motor_right_wheel(mode);
	}
}


void motor(int state)
{
	if(state==MOTOR_STATE_FRONT)
	{
			motor_left_wheel_front(MOTOR_RUN_FRONT);
		  motor_left_wheel_back(MOTOR_RUN_FRONT);
			motor_right_wheel_front(MOTOR_RUN_FRONT);
			motor_right_wheel_back(MOTOR_RUN_FRONT);
	}
	else if(state==MOTOR_STATE_BACK)
	{
			motor_left_wheel_front(MOTOR_RUN_BACK);
		  motor_left_wheel_back(MOTOR_RUN_BACK);
			motor_right_wheel_front(MOTOR_RUN_BACK);
			motor_right_wheel_back(MOTOR_RUN_BACK);
	}
	else if(state==MOTOR_STATE_LEFT)
	{
			motor_left_wheel_front(MOTOR_STOP);
		  motor_left_wheel_back(MOTOR_RUN_FRONT);
			motor_right_wheel_front(MOTOR_RUN_FRONT);
			motor_right_wheel_back(MOTOR_RUN_FRONT);
	}
	else if(state==MOTOR_STATE_RIGHT)
	{
			motor_left_wheel_front(MOTOR_RUN_BACK);
		  motor_left_wheel_back(MOTOR_RUN_BACK);
			motor_right_wheel_front(MOTOR_STOP);
			motor_right_wheel_back(MOTOR_RUN_BACK);
	}
	else if(state==MOTOR_STATE_LEFT_BACK)
	{
			motor_left_wheel_front(MOTOR_RUN_BACK);
		  motor_left_wheel_back(MOTOR_STOP);
			motor_right_wheel_front(MOTOR_RUN_BACK);
			motor_right_wheel_back(MOTOR_RUN_BACK);
	}
	else if(state==MOTOR_STATE_RIGHT_BACK)
	{
			motor_left_wheel_front(MOTOR_RUN_BACK);
		  motor_left_wheel_back(MOTOR_RUN_BACK);
			motor_right_wheel_front(MOTOR_RUN_BACK);
			motor_right_wheel_back(MOTOR_STOP);
	}
}











