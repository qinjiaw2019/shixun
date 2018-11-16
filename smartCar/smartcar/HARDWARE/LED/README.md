# LED模块
# 模块功能描述
LED灯控制

# const
1.LED1,LED2,LED3 led灯1,2,3
2.LED_ALL_OFF 熄灭所有的灯
3.LED_ALL_ON 点亮所有的灯

# API
1.LEDInit
函数功能:LED初始化
输入参数:无
返回值:无
原型：void LEDInit(void)

2.led
 函数功能:改变第n个led灯的状态
 输入参数:LED1,LED2,LED3
 返回值:无
 原型:void led(int n);
说明:
LED1,LED2,LED3 为LED灯编码

# example
#include "led.h"
#include "key.h"

# usage
1.引入#include "led.h"
2.初始化LED LEDInit();
3.控制灯 led(LED1);

# example
1.控制制定的灯
```
#include "led.h"

int main(void)
{
	LEDInit();
	led(LED1);//点亮第一个灯
	led(LED2);//点亮第二个灯
	led(LED3);//点亮第三个灯
	led(LED_ALL_ON);//点亮所有的灯
	led(LED_ALL_OFF);//熄灭所有的灯
	
	while(1)；
	return 0;
}
```