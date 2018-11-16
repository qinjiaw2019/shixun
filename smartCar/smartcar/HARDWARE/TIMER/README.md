定时器

1.#include "timer.h"
2.TIM2_Int_Init(10-1,8400-1);//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数10次为1ms   
3.实现处理函数
state：TIMER_INT（中断处理信号），TIMER_RUN

void timer2_handler(int state)
{
	if(state==TIMER_INT)
	{
		 keyValue = key_scan();
	}
	else if(state==TIMER_RUN)
	{
		cpu_counter++;
		led(LED_ALL,1);
		if(cpu_counter>=500)
		{
			cpu_counter = 0;
			led(LED_ALL,0);
		}
		
	}
}



#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#include "led.h"
#include "key.h"
#include "motor.h"
#include "xunji.h"
#include "timer.h"

int keyValue = -1;
int led3 = 1;
static unsigned int cpu_counter = 0; 
void timer2_handler(int state)
{
	if(state==TIMER_INT)
	{
		 keyValue = key_scan();
	}
	else if(state==TIMER_RUN)
	{
		cpu_counter++;
		led(LED_ALL,1);
		if(cpu_counter>=5000)
		{
			cpu_counter = 0;
			led(LED_ALL,0);
		}
		
	}
}
int main(void)
{
	TIM2_Int_Init(10-1,8400-1);
	led(LED_ALL,1);
	
 while(1);

	return 0;
}