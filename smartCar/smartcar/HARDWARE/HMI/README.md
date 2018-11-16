#include "stm32f4xx.h"

#include "hmi.h"

int main(void)
{
	HmiUart_init(9600);
	hmi_show(0,"0m");
	hmi_show(1,"test");
	


	while(1);
	return 0;
}


