#ifndef __UI_H__
#define __UI_H__

#include "config.h"

#define ICON_STAR_X 100   //图标绘制开始x点
#define ICON_STAR_Y 80    //图标绘制开始y点
#define ICON_INTERVAL_X 8 //图标水平间隔
#define ICON_INTERVAL_Y 5 //图标垂直间隔
#define ICON_WIDTH 60     //图标宽度
#define ICON_HEIGHT 88    //图标高度

extern int pos_index;

//触屏参数结构体
extern struct ts_sample sam;
extern int is_login;//登录控制变量
//首页UI
void home_ui();
//首页菜单
void menu();

//ui界面显示
void show();

#endif