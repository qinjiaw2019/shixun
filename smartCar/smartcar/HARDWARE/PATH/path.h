/************************************************************************/
/*  模块称：小车避障模块
*   最后修改时间：2018-11-13
*   作者：覃家旺  
*   描述:小车避障模块                                                       
************************************************************************/
#ifndef __PATH_H
#define __PATH_H 	
#include "sys.h"

//超声波最小范围(cm)
#define SONIC_MIN 3
//超声波最大范围(cm)
#define SONIC_MAX 400
//小车尺寸(宽*长cm)
#define CAR_WIDTH 20
#define CAR_LENGTH 20

//安全距离(cm)
#define SAVE_LENGTH_MIN 10
#define SAVE_LENGTH_MAX 20

//小车状态
#define CAR_STOP 0//停止
#define CAR_STRIGHT 1//直行中
#define CAR_TURN_LEFT 2//左转
#define CAR_TURN_RIGHT 3//右转
#define CAR_BACK 4//后退

//转弯尝试更新距离延时(秒)
#define TURN_DELAY_MS 10

//行车信息结构体
typedef struct{
	float sonic_legnth;//与障碍物的距离
	int state;//小车当前状态
	float pre_sonic_length;//上一次的距离(2m前)
}CAR_InitStructure;

void path_handler(CAR_InitStructure *carInfo);
#endif