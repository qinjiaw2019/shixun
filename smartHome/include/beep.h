#ifndef _BEEP_H_
#define _BEEP_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>    //标准输入输出
#include <sys/ioctl.h>//监测头文件
#include <unistd.h>   //延时

#define BEEP_GPIO 1
//蜂鸣器是三极管
#define BEEP_ON  1  //打开
#define BEEP_OFF 0  //关闭

/*
	蜂鸣器
	lay：响几秒
*/
int beep(int lay);
void beep_star();
void beep_stop();

#endif