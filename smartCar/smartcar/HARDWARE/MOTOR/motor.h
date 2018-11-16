/************************************************************************/
/*   模块称：电机模块
*   最后修改时间：2018-11-13
*   作者：覃家旺  
*   描述:四轮电机控制                                                        
************************************************************************/
#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

/**
电机定义
**/

//轮子定义第一组
//左前轮
#define MOTOR_LEFT_FRONT 1
//左后轮
#define MOTOR_LEFT_BACK 2
//左轮
#define MOTOR_LEFT 5

//右前轮
#define MOTOR_RIGHT_FRONT 3
//右后轮
#define MOTOR_RIGHT_BACK 4
//右轮
#define MOTOR_RIGHT 6
//所有轮子
#define MOTOR_ALL 7

//前进
#define MOTOR_RUN_FRONT 1
//后退
#define MOTOR_RUN_BACK -1
//停止
#define MOTOR_STOP 0

//轮子定义第二组 MOTOR_LEFT_FRONT  MOTOR_RIGHT_FRONT MOTOR_LEFT_BACK MOTOR_RIGHT_BACK
#define WHEEL1 1
#define WHEEL2 2
#define WHEEL3 3
#define WHEEL4 4
#define WHEEL_LEFT 5
#define WHEEL_RIGHT 6
#define WHEEL_ALL 7

/**
驱动方向
1.前进
2.后退
3.左转弯
4.右转弯
5.左后转弯
6.右后转弯
**/
#define MOTOR_STATE_FRONT 1
#define MOTOR_STATE_BACK 2
#define MOTOR_STATE_LEFT 3
#define MOTOR_STATE_RIGHT 4
#define MOTOR_STATE_LEFT_BACK 5
#define MOTOR_STATE_RIGHT_BACK 6


/**
*	函数名称:MotorChekInit
*   函数功能:电机初始化
*	输入参数:无
*	返回值:无
**/
void MotorChekInit();


/**
*	函数名称:motor_left_wheel_front
*   函数功能:左前轮驱动
*	输入参数:模式
*	返回值:无
**/
void motor_left_wheel_front(int mode);
/**
*	函数名称:motor_left_wheel_back
*   函数功能:左后轮驱动
*	输入参数:模式
*	返回值:无
**/
void motor_left_wheel_back(int mode);
/**
*	函数名称:motor_right_wheel_front
*   函数功能:右前轮驱动
*	输入参数:模式
*	返回值:无
**/
void motor_right_wheel_front(int mode);
/**
*	函数名称:motor_right_wheel_back
*   函数功能:右后轮驱动
*	输入参数:模式
*	返回值:无
**/
void motor_right_wheel_back(int mode);


/**
*	函数名称:motor_wheel
*   函数功能:控制第几个轮子的状态
*	输入参数:
*            wheel:轮子编码
*			 mode：模式
*	返回值:无
**/
void motor_wheel(int wheel,int mode);


/**


**/
/**
*	函数名称:motor_wheel
*   函数功能:驱动方向
			1.前进
			2.后退
			3.左转弯
			4.右转弯
			5.左后转弯
			6.右后转弯
*	输入参数:模式
*	返回值:无
**/
void motor(int state);


#endif

