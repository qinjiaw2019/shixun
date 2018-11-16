#include "uart2.h"
#include "uart1.h"
#include "led.h"

#define USART2_REC_MAXLEN  			200  	//定义最大接收字节数 200

u8  USART2_RX_BUF[USART2_REC_MAXLEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
u16 USART2_RX_LEN=0;         		//接收状态标记	


void uart2_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//U2_RX: PA3   U2_TX: PA2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
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
	
	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
		
  USART_Cmd(USART2, ENABLE);  //使能串口2
	USART_ClearFlag(USART2,USART_FLAG_TC);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	

}

void uart2_sendbyte(u8 dat)
{
	USART_SendData(USART2,dat);
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!= SET);
  USART_ClearFlag(USART2, USART_FLAG_TC);  
}


void uart2_sendstr(u8* str)
{
	while(*str != '\0')
	{
		uart2_sendbyte(*str);
		str++;
	} 
}
/**/
void USART2_IRQHandler(void) 
{
	u8 Res;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{

		Res = USART_ReceiveData(USART2);
		USART2_RX_BUF[USART2_RX_LEN] = Res;
		USART2_RX_LEN++;
		if(USART2_RX_LEN>(USART2_REC_MAXLEN-1)) 
			 USART2_RX_LEN=0;
		
		uart1_sendbyte(Res);
	}		
}



