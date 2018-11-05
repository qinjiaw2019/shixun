/*******************************************
代码功能：登录模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "../include/config.h"

//按键宏定义
#define BTN_NUMBER_0 0//0
#define BTN_NUMBER_1 1//1
#define BTN_NUMBER_2 2//2
#define BTN_NUMBER_3 3//3
#define BTN_NUMBER_4 4//4
#define BTN_NUMBER_5 5//5
#define BTN_NUMBER_6 6//6
#define BTN_NUMBER_7 7//7
#define BTN_NUMBER_8 8//8
#define BTN_NUMBER_9 9//9
#define BTN_NUMBER_DEL -1//del
#define BTN_NUMBER_CANCEL -2//cancel
#define BTN_NUMBER_ERROR -3//cancel

extern int ts;//触屏
//触屏参数结构体
extern struct ts_sample sam;
extern int is_login;//登录控制变量
extern char system_pass[5];//默认密码

//界面显示
void show_login();
#endif