#ifndef __MUSIC_H__
#define __MUSIC_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//宏定义，是音量
#define MUSIC_UP 1
#define MUSIC_DOWD 0

#define MUSIC_PLAY 0 //暂停状态
#define MUSIC_PAUSE 1 //暂停状态
#define MUSIC_STOP 2 //停止状态
#define MUSIC_MUTE_Y 3 //静音
#define MUSIC_MUTE_N 3 //静音




/**
	音乐播放及音量控制
	1.pathName：音乐文件
	2.cmd: 数值
	音量范围： -175 to 18 
		
*/
int madplay_music(char *pathName, char *cmd);

/**
	音乐，暂停，播放，停止
	1.cmd
		18或SIGCONT	  继续
		19或SIGSTOP   暂停
		9或SIGKILL    杀死进程madplay
*/
int madplay_controller(char *cmd);
#endif