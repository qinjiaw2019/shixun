/*******************************************
代码功能：相机模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../include/config.h"

extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;


//界面显示
void camera_show();
#endif