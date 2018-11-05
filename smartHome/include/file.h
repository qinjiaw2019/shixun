/*******************************************
代码功能：文件模块模块
编写者：覃家旺
2018-10-30
********************************************/
#ifndef __FILE_H__
#define __FILE_H__
#include "config.h"

#define FILE_DIR_ITEM "../pic/ui/exploer_dir_item_x.bmp"  //文件夹item
#define FILE_FILE_ITEM "../pic/ui/exploer_file_item_x.bmp" //文件item

extern int ts;//触屏

//界面显示
void exploer(char *path);
#endif