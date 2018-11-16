#include "path.h"
#include "delay.h"
#include "motor.h"
#include "hcsr04.h"
#include "uart1.h"
#include<stdio.h>

int turn_to = 0;//转动方向  0:向右转,1.向左转
//直行
void turn_to_straight(CAR_InitStructure *carinfo)
{
	carinfo->state = CAR_STRIGHT;
	motor_wheel(WHEEL_ALL,MOTOR_RUN_FRONT);
}



//向右转
void turn_to_right(CAR_InitStructure *carinfo)
{
	carinfo->state = CAR_TURN_RIGHT;
	motor_wheel(WHEEL1,MOTOR_RUN_FRONT);
	motor_wheel(WHEEL2,MOTOR_RUN_BACK);
	motor_wheel(WHEEL3,MOTOR_RUN_FRONT);
	motor_wheel(WHEEL4,MOTOR_RUN_BACK);

}

//向左转
void turn_to_left(CAR_InitStructure *carinfo)
{
	carinfo->state = CAR_TURN_LEFT;
	motor_wheel(WHEEL1,MOTOR_RUN_BACK);
	motor_wheel(WHEEL2,MOTOR_RUN_FRONT);
	motor_wheel(WHEEL3,MOTOR_RUN_BACK);
	motor_wheel(WHEEL4,MOTOR_RUN_FRONT);
}
//后退
void turn_to_back(CAR_InitStructure *carinfo)
{
	//后退一定的距离
	carinfo->state = CAR_BACK;
	motor_wheel(WHEEL_ALL,MOTOR_RUN_BACK);
}

//停止
void turn_stop(CAR_InitStructure *carinfo)
{
	carinfo->state = CAR_STOP;
	motor_wheel(WHEEL_ALL,MOTOR_STOP);
}

//安全距离内处理
void handler_save_len(CAR_InitStructure *carinfo)
{
	int i = 0;
	if(carinfo->pre_sonic_length > carinfo->sonic_legnth)
	{
		turn_to_right(carinfo);
	}
	else
	{
		turn_to_left(carinfo);
	
	}
}

//路径控制
void path_handler(CAR_InitStructure *carinfo)
{
	
	turn_to = 0;
	if(carinfo->sonic_legnth > SAVE_LENGTH_MAX || carinfo->sonic_legnth > SAVE_LENGTH_MAX)//行径上无障碍  | 安全距离外
	{
		turn_to_straight(carinfo);// 直行
	}
	else if(carinfo->sonic_legnth <= SAVE_LENGTH_MAX)//在安全距离内
	{
		if(carinfo->sonic_legnth <=SAVE_LENGTH_MIN)
		{
			//到达安全距离最小极限 则后退
			turn_to_back(carinfo);
		}
		else
		{
			//在安全距离带内
			handler_save_len(carinfo);
		}
	}
	else{
		turn_stop(carinfo);
	}
	/**///turn_to_left(carinfo);

}