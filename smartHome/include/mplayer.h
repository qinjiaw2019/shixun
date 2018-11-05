/*******************************************
代码功能：视频模块封装
编写者：雷民用
2018-09-26
********************************************/
#ifndef __MPLAYER_H__
#define __MPLAYER_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//#define VEDIO_PLAY 0 //播放状态
#define VEDIO_PAUSE 1 //暂停状态
#define VEDIO_STOP 2 //停止状态
#define VEDIO_MUTE_Y 3 //静音
#define VEDIO_MUTE_N 3 //静音

//创建管道，会创建/tmp/fifo管道
int creat_fifo();
/*
	自定义视频播放
	pathName.视频路径
	x，y屏幕的起止位置
	w，h视频的宽高
*/
int mplayer_tv(char *pathName, char *x, char *y, char *w, char *h);
/**
	视频控制
	传入salve命令 
	seek      Float [Integer]   ---》快进和快退
	 
	quit      [Integer]        ----》退出
	quit 0\n
	 
	pause     [Integer]       ----》暂停/恢复
	pause\n
		 
	volume    Float [Integer]  ----》调节声音 
	volume  1000\n
    volume  -1000\n	 

    mute         [Integer]        ----》静音/恢复
    mute 0\n
	
	如：mplayer_cmd（"seek 10\n"）;
*/
int mplayer_cmd(char *cmd);
void mplayer_destroy();
#endif