#include "hmi.h"
#include <string.h>
#include <stdio.h>

void hmi_send_end()
{
    int i;
	USART_ClearFlag(UART5,USART_FLAG_TC);
	for(i=0;i<3;i++)
	{
		UART5->DR=0xff;
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!=SET);
	}
}
//串口发送字符串
void hmi_send_t(char *str)
{
	USART_ClearFlag(UART5,USART_FLAG_TC);
	while(*str)
	{
		USART_SendData(UART5,*str);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
		str++;
	}
}
//显示字符串
void hmi_show(int line,char *str)
{
	char s[50];
	sprintf(s,"t%d.txt=\"%s\"",line,str);
	
	hmi_send_end();
	hmi_send_t(s);
	
}
void HmiUart_init(u32 bound){
   //GPIO端口设置
    GPIO_InitTypeDef GPIOC_InitStructure,GPIOD_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOc/d时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);//使能USART5时钟
 
	//串口5对应引脚复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); //GPIOA10复用为USART1
	
	//USART1端口配置
    GPIOC_InitStructure.GPIO_Pin = GPIO_Pin_12; //GPIOA9与GPIOA10
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIOC_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIOC_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOC,&GPIOC_InitStructure); //初始化PA9，PA10
	
	GPIOD_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOA9与GPIOA10
	GPIOD_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIOD_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIOD_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIOD_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIOD_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART5, &USART_InitStructure); //初始化串口1
		
  USART_Cmd(UART5, ENABLE);  //使能串口1 
	
				hmi_send_end();
				hmi_send_t("r0.val=1");
				hmi_send_end();
				hmi_send_t("r1.val=0");
				hmi_send_end();
				hmi_send_t("r2.val=0");
				hmi_send_end();
				hmi_send_t("r3.val=0");
				hmi_send_end();
				hmi_send_t("r4.val=0");
				hmi_send_end();
				hmi_send_t("r5.val=0");
				hmi_send_end();
				hmi_send_t("r6.val=0");
				hmi_send_end();
				hmi_send_t("r7.val=0");
				hmi_send_end();	
				hmi_send_t("r8.val=0");
				hmi_send_end();
				hmi_send_t("t0.txt=\"\"");
				hmi_send_end();	
				hmi_send_t("t3.txt=\"\"");
				hmi_send_end();	
				hmi_send_t("t7.txt=\"\"");
				hmi_send_end();	
				hmi_send_t("t8.txt=\"\"");
				hmi_send_end();	
				hmi_send_t("t9.txt=\"\"");
				hmi_send_end();	
				hmi_send_t("t11.txt=\"\"");
				hmi_send_end();
				hmi_send_t("t13.txt=\"\"");
				hmi_send_end();
				hmi_send_t("t17.txt=\"\"");
				hmi_send_end();
				hmi_send_t("t18.txt=\"\"");
				hmi_send_end();
}

