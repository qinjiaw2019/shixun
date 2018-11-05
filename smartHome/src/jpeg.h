/*******************************************
代码功能：JPG图片模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __JPEG_H__
#define __JPEG_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../include/config.h"

extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;

//视频界面显示
void jpeg_show(char *filename);
#endif