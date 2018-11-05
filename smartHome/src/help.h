/*******************************************
代码功能：简介模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __HELP_H__
#define __HELP_H__

#include "../include/config.h"


extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;
extern int is_login;//登录控制变量
extern char system_pass[5];//默认密码

//界面显示
void show_help();
#endif