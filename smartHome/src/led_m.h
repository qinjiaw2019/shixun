/*******************************************
代码功能：LED模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __LED_M_H__
#define __LED_M_H__
#include "../include/config.h"

extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;

void led_show();

#endif