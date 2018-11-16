#include "uart2.h"
#include "uart1.h"
#include "led.h"

#define USART2_REC_MAXLEN  			200  	//�����������ֽ��� 200

u8  USART2_RX_BUF[USART2_REC_MAXLEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
u16 USART2_RX_LEN=0;         		//����״̬���	


void uart2_init(u32 bound){
   //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//U2_RX: PA3   U2_TX: PA2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����2��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA2����ΪUSART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA3����ΪUSART2
	
	//USART2�˿�����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA2��GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2��PA3

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	
	
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
		
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
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



