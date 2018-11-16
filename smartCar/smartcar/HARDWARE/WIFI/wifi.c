#include "wifi.h"
#include <string.h>

#define MAXLEN     100
//wifi中断函数
u8 Wifi_count,Wifi_strlen,j,wifi_flag,wifi_rxflag;
char Wifi_strbuf[MAXLEN];
//wifi检查初始化
void WifiChek_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure1,NVIC_InitStructure2;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//使能 计时器4时钟
 
	//串口2对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3复用为USART2
	
	//USART2端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2与GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2，PA3

   //USART2 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART2, &USART_InitStructure); //初始化串口2
	
	NVIC_InitStructure1.NVIC_IRQChannel = USART2_IRQn;//串口2中断通道
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure1);	//根据指定的参数初始化VIC寄存器、
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=100-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=8400-1;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);//定时器4初始化配置
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器4更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器4
	
	NVIC_InitStructure2.NVIC_IRQChannel=TIM4_IRQn; //定时器4中断
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority=4; //子优先级3
	NVIC_InitStructure2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure2);	
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断
	
  USART_Cmd(USART2, ENABLE);  //使能串口2 

	
}
void usrc210_send_ch(u8 ch)
{
	USART_SendData(UART5,ch);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
}
//发送字符串
void usrc210_send(char *str)
{
	int  i=0;
	USART_ClearFlag(UART5,USART_FLAG_TC);

	while(i<strlen(str))
	{
		USART_SendData(UART5,str[i++]);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
	}
}
/*
//wifi中断函数
void USART2_IRQHandler(void)
{
	uart1_sned_buff("wifi-USART2_IRQHandler\r\n");
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); //清除中断标志. 
		wifi_rxflag=1;
		Wifi_count=3;
		Wifi_strbuf[j++]=USART_ReceiveData(USART2);
	}
	uart1_sned_buff(Wifi_strbuf);
}
*/
void TIM4_IRQHandler(void)
{

	if(TIM4->SR&0X0001)  
    {     
			if(wifi_rxflag)
			{
        if(Wifi_count>0)    
        {    
            Wifi_count--;     
        } 
				else
				{
					Wifi_strlen=j;
					j=0;
					wifi_flag=1;
					wifi_rxflag=0;
				}
			}
    }                      
    TIM4->SR&=~(1<<0);   
}
char * usrc210_response()
{
	return Wifi_strbuf;
}
/*
 * 函数名：ESP8266_Cmd
 * 描述  ：对WF-ESP8266模块发送AT指令
 * 输入  ：cmd，待发送的指令
 *         reply1，reply2，期待的响应，为NULL表不需响应，两者为或逻辑关系
 *         waittime，等待响应的时间
 * 返回  : 1，指令发送成功
 *         0，指令发送失败
 * 调用  ：被外部调用
 */
bool USRC210_Cmd ( char * cmd, char * reply1, char * reply2, u32 waittime )
{
	return OK;
}

