/*******************************************
代码功能：MP3音频模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __MP3_H__
#define __MP3_H__
#include "config.h"

extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;

//界面显示
void mp3_show(char *filename);
#endif