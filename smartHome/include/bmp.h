/*******************************************
代码功能：bmp图片
编写者：覃家旺
2018-09-26
********************************************/
#ifndef __BMP_H__
#define __BMP_H__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>//内存映射

int bmp_show(char *pathname);

//自定义函数，显示任意位置任意大小
/*
  坐标原点：（x，y）
  真实的高宽： （w，h）
  路径 ：const char *pathname
*/
int bmp_show_xy(int x,int y,int w,int h,const char *pathname);
#endif