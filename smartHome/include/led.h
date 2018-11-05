/*******************************************
代码功能：LED模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __LED_H__
#define __LED_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>    //标准输入输出
#include <sys/ioctl.h>//监测头文件
#include <unistd.h>   //延时


#define TEST_MAGIC 'x'                    //定义幻数

//定义下LED灯
#define LED1 _IO(TEST_MAGIC,0)
#define LED2 _IO(TEST_MAGIC,1)
#define LED3 _IO(TEST_MAGIC,2)
#define LED4 _IO(TEST_MAGIC,3)

//定义开和关
#define LED_ON   0    //低电平  亮灯
#define LED_OFF  1    //高电平  灭灯

int led_open();
//控制灯的状态
void led(int index,int mode);

//熄灭所有led
void led_all_off();
void led_all_on();

#endif