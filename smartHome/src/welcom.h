/*******************************************
代码功能：欢迎界面模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __WELCOM_H__
#define __WELCOM_H__

#include "../include/config.h"

extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;
extern int is_login;//登录控制变量

//界面显示
void welcom_show();
#endif