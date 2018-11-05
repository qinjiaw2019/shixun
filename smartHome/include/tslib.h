/*******************************************
代码功能：触摸子系统
编写者：覃家旺
2018-09-26
********************************************/
#ifndef __TSLIB_H__
#define __TSLIB_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	
#include <linux/input.h> //输入子系统
#include <stdio.h>  

struct ts_sample{
	int x;//x坐标
	int y;//y坐标
	int pressure;//压力值
};
//打开触摸屏
int ts_open();
//关闭触摸屏
int ts_close(int ts_fd);
/*
获取坐标
ts:触摸文件描述符
ts_sample 坐标结构体
*/
int ts_read(int ts,struct ts_sample *sam);
#endif