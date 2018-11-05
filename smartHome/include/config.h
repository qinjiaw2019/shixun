#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "bmp.h"
#include "tslib.h"
#include "res.h"
#include "vedio.h"
#include "mp3.h"
#include "file.h"
#include "timer.h"
#include "mplayer.h"
#include "music.h"
#include "led.h"
#include "str.h"
#include "beep.h"



#include "../ext/lib/font.h"
#include  "../ext/show_video/lcd.h"//显示画面
#include  "../ext/show_video/jpeg/api_v4l2.h"//摄像头

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>


#define HOME -1 //首页UI
#define MP3_PLAY 1//音乐播放
#define VEDIO_PLAY 2//视频播放 
#define EXPOLER 3//文件浏览器
#define CAMERA 4//摄像头
#define LED 5//LED
#define ABLUM 6//相册
#define PHOTO 7//相机
#define WELCOM 8 //欢迎界面
#define JIANJIE 9 //简介

#define LOGINED 1 //登录
#define LOGINOUT 0 //注销(退出登录)

#define ERROR -1 //错误

#define APP_DATA "../data" //数据目录
#define ABLUM_DATA "../data/ablum"//相册目录

#define CAMERA_TMP_DATA "../data/camera/tmp" //摄像头临时数据



#define BACK 0// 返回

#endif