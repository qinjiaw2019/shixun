#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

#include "sys.h"
#include "uart.h"
#include "hcsr04.h"
int main(void)
{
	float len = 0;
	char s[100];
	delay_init(168);
	uart1_init(9600);
	hcsr04_Init();
	while(1)
	{
		len = hcsr04_measure();
		sprintf(s,"  len:%f  \n",len);
		uart1_sned_buff(s);
	
	}
	
}