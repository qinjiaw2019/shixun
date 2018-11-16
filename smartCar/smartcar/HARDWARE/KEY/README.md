# 按键扫描
# 模块功能描述
扫描按键,返回按键代码

# API
1.KeyInit
函数功能:按键初始化
输入参数:无
返回值:无
原型：void KeyInit();

2.key_scan
 函数功能:按键扫描
 输入参数:无
 返回值:
		有效返回值:KEY1,KEY2,KEY3
		无效返回值:KEY_ERROR
说明:
KEY1,KEY2,KEY3 为按键代码
KEY_ERROR 为无效代码

# example
#include "led.h"
#include "key.h"

# example
按键控制相应的灯
```
#include "led.h"
#include "key.h"

int main(void)
{
	int key = -1;
	LEDInit();
	KeyInit();
	led(LED_ALL_OFF);
	
	while(1)
	{
		key = key_scan();
		
		led(key);
	}
	return 0;
}
```