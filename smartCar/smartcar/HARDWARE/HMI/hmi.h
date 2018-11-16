/************************************************************************/
/*   模块称：HMI模块
*   最后修改时间：2018-11-13
*   作者：覃家旺  
*   描述:HMI模块                                                        
************************************************************************/
#ifndef __HMI_H
#define __HMI_H
#include <sys.h>	

/**
*	函数名称:HmiUart_init
* 函数功能:初始化HMI
*	输入参数:bound：波特率
*	返回值:无
**/
void HmiUart_init(u32 bound);

/**
*	函数名称:hmi_show
* 函数功能:在指定的行显示字符串
*	输入参数:bound：波特率
*	返回值:无
**/
void hmi_show(int line,char *str);

#endif

