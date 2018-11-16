# 电机模块
# 模块功能描述
四轮电机控制 

# const
电机定义
```

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
```

# API
1.MotorChekInit
函数功能:电机初始化
输入参数:无
返回值:无
原型：void MotorChekInit()

2.motor_left_wheel_front 左前轮驱动
  motor_left_wheel_back 左后轮驱动
  motor_right_wheel_front 右前轮驱动
  motor_right_wheel_back 右后轮驱动
 输入参数:mode
 返回值:无
 原型:void motor_left_wheel_front(int mode)
说明:
mode:取值为MOTOR_RUN_FRONT，MOTOR_RUN_BACK，MOTOR_STOP


3.motor_wheel
 函数功能:控制第几个轮子的状态
 输入参数:
    wheel:轮子编码
    mode：模式
 返回值:无
 原型:void motor_wheel(int wheel,int mode);
说明:
mode:取值为MOTOR_RUN_FRONT，MOTOR_RUN_BACK，MOTOR_STOP
wheel:取值为轮子的宏定义 第二组

3.motor_wheel
 函数功能:驱动方向
 输入参数:state
 返回值:无
 原型:void motor(int state);
说明:
state:取值为MOTOR_RUN_FRONT，MOTOR_RUN_BACK，MOTOR_STOP


# example
#include "led.h"
#include "key.h"

# usage
1.引入#include "led.h"
2.初始化LED LEDInit();
3.控制灯 led(LED1);

# example
1.控制制定的灯
```
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#include "led.h"
#include "key.h"
#include "motor.h"

int main(void)
{
	
	int key = -1;
	MotorChekInit();
	KeyInit();
	
	delay_init(168);
	while(1)
	{
		if(key==KEY1)
		{
			
		}
		key = key_scan();
		
		motor(MOTOR_STATE_FRONT);//前进
		delay_ms(2000);
			
		motor(MOTOR_STATE_BACK);//后退
		delay_ms(2000);
		
		motor(MOTOR_STATE_LEFT);//左转弯
		delay_ms(2000);
		
		motor(MOTOR_STATE_RIGHT);//右转弯
		delay_ms(2000);
		
		motor(MOTOR_STATE_LEFT_BACK);//左后转弯
		delay_ms(2000);
		
		motor(MOTOR_STATE_RIGHT_BACK);//右后转弯
		delay_ms(2000);
	}
	return 0;
}
```