#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#include "light.h"

int main(void)
{
	delay_init(168);
	LED_init();
	
	LED1 = 0;
	LED2 = 1;
	LED3 = 0;
	
	while(1)
	{
		LED1 = ~LED1;
		LED2 = ~LED2;
		LED3 = ~LED3;
		delay_ms(1000);
	}
	
	return 0;
}
