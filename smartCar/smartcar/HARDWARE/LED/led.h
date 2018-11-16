/************************************************************************/
/*   ģ��ƣ�LEDģ��
*   ����޸�ʱ�䣺2018-11-13
*   ���ߣ�������         
*   ����:LED�ƿ���                                                 
************************************************************************/
#ifndef __LED_H
#define __LED_H 			   
#include <sys.h>	

//led�˿ڶ���
#define LEDPD0 PDout(0)
#define LEDPD1 PDout(1)
#define LEDPD3 PDout(3)

#define LED1 1
#define LED2 2
#define LED3 3
#define LED_ALL_OFF 4
#define LED_ALL_ON 5
#define LED_ALL 6

#define LED_ON 0
#define LED_OFF 1



/**
*	��������:LEDInit
*   ��������:LED��ʼ��
*	�������:��
*	����ֵ:��
**/
void LEDInit(void);

/**
*	��������:led
*   ��������:�ı��n��led�Ƶ�״̬
*	�������:n(LED1,LED2,LED3)
*	����ֵ:��
**/
void led(int n,int state);


#endif
