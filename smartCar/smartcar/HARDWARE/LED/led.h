/************************************************************************/
/*   模块称：LED模块
*   最后修改时间：2018-11-13
*   作者：覃家旺         
*   描述:LED灯控制                                                 
************************************************************************/
#ifndef __LED_H
#define __LED_H 			   
#include <sys.h>	

//led端口定义
#define LEDPD0 PDout(0)
#define LEDPD1 PDout(1)
#define LEDPD3 PDout(3)

#define LED1 1
#define LED2 2
#define LED3 3
#define LED_ALL_OFF 4
#define LED_ALL_ON 5
#define LED_ALL 6

#define LED_ON 0
#define LED_OFF 1



/**
*	函数名称:LEDInit
*   函数功能:LED初始化
*	输入参数:无
*	返回值:无
**/
void LEDInit(void);

/**
*	函数名称:led
*   函数功能:改变第n个led灯的状态
*	输入参数:n(LED1,LED2,LED3)
*	返回值:无
**/
void led(int n,int state);


#endif
