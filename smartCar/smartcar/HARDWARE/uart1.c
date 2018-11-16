#include "uart1.h"
//#include "led.h"
#include "uart2.h"

#define USART1_REC_MAXLEN  			200  	//�����������ֽ��� 200

u8  USART1_RX_BUF[USART1_REC_MAXLEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
u16 USART1_RX_LEN=0;         		//����״̬���	

//extern u8  UART5_RX_BUF[];

void uart1_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//U1_RX: PA10   U1_TX: PA9
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
		
  USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	

}

void uart1_sendbyte(u8 dat)
{
	USART_SendData(USART1,dat);
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)!= SET);
  USART_ClearFlag(USART1, USART_FLAG_TC);  
}


void uart1_sendstr(u8* str)
{
	while(*str != '\0')
	{
		uart1_sendbyte(*str);
		str++;
	} 
}

void USART1_IRQHandler(void) 
{
	u8 Res;
	
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		Res = USART_ReceiveData(USART1);
		USART1_RX_BUF[USART1_RX_LEN] = Res;
		USART1_RX_LEN++;
		if(USART1_RX_LEN>(USART1_REC_MAXLEN-1)) 
			 USART1_RX_LEN=0;
		
		uart2_sendbyte(Res);
	}		
}



