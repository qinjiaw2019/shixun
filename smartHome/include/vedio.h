/*******************************************
代码功能：视频模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __VEDIO_H__
#define __VEDIO_H__

#include "config.h"


#define VEDIO_BACK "../pic/ui/back.bmp" //返回
#define VEDIO_MUTE_PIC_Y "../pic/ui/vedio/silence_y.bmp" //静音图片
#define VEDIO_MUTE_PIC_N "../pic/ui/vedio/silence_n.bmp"

extern int pos_index;
extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;

//视频界面显示
void vedio_show(char *filename);
#endif