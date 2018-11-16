/************************************************************************/
/*   模块称:定时计数器
*   最后修改时间：2018-11-13
*   作者：覃家旺  
*   描述:                                                      
************************************************************************/
#ifndef __TIMER_H
#define __TIMER_H 	

#include "sys.h"


	
//定时器中断处理
#define TIMER_INT 1
#define TIMER_RUN 2

//定时器2处理函数
extern void timer2_handler(int state);
//定时器3处理函数
//extern void timer3_handler(int state);
//TIM2_Int_Init(9999,72-1);		                     //定时器2分频系数72，频率=72MHz/(71+1)=1MHz
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!边沿对齐，向上计数
void TIM2_Int_Init(u16 arr,u16 psc);	


void TIM3_Int_Init(u16 arr,u16 psc);


#endif