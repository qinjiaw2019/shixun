#include "led.h"
#include "delay.h"


/**
*	��������:LEDInit
*   ��������:LED��ʼ��
*	�������:��
*	����ֵ:��
**/
void LEDInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//�������
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	
	
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��D�˿�
	
	delay_init(168);
}
/**
*	��������:led_all_off
*   ��������:Ϩ�����еĵ�
*	�������:��
*	����ֵ:��
**/
void led_all_off()
{
	LEDPD0 = 1;
	LEDPD1 = 1;
	LEDPD3 = 1;
}
/**
*	��������:led_all_on
*   ��������:�������еĵ�
*	�������:��
*	����ֵ:��
**/
void led_all_on()
{
	LEDPD0 = 0;
	LEDPD1 = 0;
	LEDPD3 = 0;
}

/**
*	��������:led
*   ��������:�ı��n��led�Ƶ�״̬
*	�������:n(LED1,LED2,LED3)
*	����ֵ:��
**/

void led(int n,int state)
{
	if(n==LED1)
	{
		LEDPD0 = state;
		LEDPD3 = 1;
	}
	else if(n==LED2)
	{
		LEDPD0 = 1;
		LEDPD1 = 0;
		LEDPD3 = 1;	
	}
	else if(n==LED3)
	{
		LEDPD0 = 1;
		LEDPD1 = 1;
		LEDPD3 = state;
	}
	else if(n==LED_ALL_OFF){
		LEDPD0 = 1;
		LEDPD1 = 1;
		LEDPD3 = 1;	
	}
	else if(n==LED_ALL_ON)
	{
		LEDPD0 = 0;
		LEDPD1 = 0;
		LEDPD3 = 0;	
	}
	else if(n==LED_ALL)
	{
		LEDPD0 = state;
		LEDPD1 = state;
		LEDPD3 = state;
	}
}
