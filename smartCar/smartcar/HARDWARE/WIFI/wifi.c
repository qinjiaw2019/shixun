#include "wifi.h"
#include <string.h>

#define MAXLEN     100
//wifi�жϺ���
u8 Wifi_count,Wifi_strlen,j,wifi_flag,wifi_rxflag;
char Wifi_strbuf[MAXLEN];
//wifi����ʼ��
void WifiChek_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure1,NVIC_InitStructure2;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʹ�� ��ʱ��4ʱ��
 
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
	
	NVIC_InitStructure1.NVIC_IRQChannel = USART2_IRQn;//����2�ж�ͨ��
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure1);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=100-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler=8400-1;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);//��ʱ��4��ʼ������
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��4�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��4
	
	NVIC_InitStructure2.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��4�ж�
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�1
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority=4; //�����ȼ�3
	NVIC_InitStructure2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure2);	
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	
  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2 

	
}
void usrc210_send_ch(u8 ch)
{
	USART_SendData(UART5,ch);
		while(USART_GetFlagStatus(UART5,USART_FLAG_TC)==0);
}
//�����ַ���
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
//wifi�жϺ���
void USART2_IRQHandler(void)
{
	uart1_sned_buff("wifi-USART2_IRQHandler\r\n");
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); //����жϱ�־. 
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
 * ��������ESP8266_Cmd
 * ����  ����WF-ESP8266ģ�鷢��ATָ��
 * ����  ��cmd�������͵�ָ��
 *         reply1��reply2���ڴ�����Ӧ��ΪNULL������Ӧ������Ϊ���߼���ϵ
 *         waittime���ȴ���Ӧ��ʱ��
 * ����  : 1��ָ��ͳɹ�
 *         0��ָ���ʧ��
 * ����  �����ⲿ����
 */
bool USRC210_Cmd ( char * cmd, char * reply1, char * reply2, u32 waittime )
{
	return OK;
}

