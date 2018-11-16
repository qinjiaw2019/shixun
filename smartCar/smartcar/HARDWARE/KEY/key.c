#include "key.h"
#include "sys.h"
#include "delay.h"

//�����˿ڶ���
#define key3 PDin(10)
#define key2 PDin(9)
#define key1 PDin(8)

/**
*	��������:KeyInit
*   ��������:������ʼ��
*	�������:��
*	����ֵ:��
**/
void KeyInit()
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//���빦��
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
}

/**
*	��������:key_scan
*   ��������:����ɨ��
*	�������:��
*	����ֵ:
*		��Ч����ֵ:KEY1,KEY2,KEY3
*		��Ч����ֵ:KEY_ERROR
**/
int key_scan()
{
	u8 key1_flag=0,key2_flag=0,key3_flag=0;
	//key1ɨ��
	if(key1==0)
	{
		delay_ms(5);
		if(key1==0)
		{

				key1_flag=1;
				return KEY1;
			while(key1==0);
		}
	}
	
	//key2ɨ��
	if(key2==0)
	{
		delay_ms(5);
		if(key2==0)
		{
			 key2_flag=1;

			return KEY2;
			while(key2==0);
		}
	}
	//key3ɨ��
	if(key3==0)
	{
		delay_ms(5);
		if(key3==0)
		{
			key3_flag=1;
		
				return KEY3;
			while(key3==0);
		}
	}
	
	return KEY_ERROR;
}