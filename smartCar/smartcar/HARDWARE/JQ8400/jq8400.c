#include "jq8400.h"

void JQ8400_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

  //GPIOE2初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOE,GPIO_Pin_2);//GPIOE2设置高

}

void jq8400_send_data(u8 dat)//发送指令
{
    u8 i;
	PEout(2)=1;
	delay_ms(4);
	PEout(2)=0;
	delay_ms(4);
	for(i=0;i<8;i++)
	{
		PEout(2)=1;
		if(dat&0x01)
		{
			delay_us(600);
			PEout(2)=0;
			delay_us(200);
		}
		else
		{
			delay_us(200);
			PEout(2)=0;
			delay_us(600);
		}
		dat=dat>>1;
	}
	PEout(2)=1;
}
