/************************************************************************/
/*   ģ��ƣ����ģ��
*   ����޸�ʱ�䣺2018-11-13
*   ���ߣ�������  
*   ����:���ֵ������                                                        
************************************************************************/
#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

/**
�������
**/

//���Ӷ����һ��
//��ǰ��
#define MOTOR_LEFT_FRONT 1
//�����
#define MOTOR_LEFT_BACK 2
//����
#define MOTOR_LEFT 5

//��ǰ��
#define MOTOR_RIGHT_FRONT 3
//�Һ���
#define MOTOR_RIGHT_BACK 4
//����
#define MOTOR_RIGHT 6
//��������
#define MOTOR_ALL 7

//ǰ��
#define MOTOR_RUN_FRONT 1
//����
#define MOTOR_RUN_BACK -1
//ֹͣ
#define MOTOR_STOP 0

//���Ӷ���ڶ��� MOTOR_LEFT_FRONT  MOTOR_RIGHT_FRONT MOTOR_LEFT_BACK MOTOR_RIGHT_BACK
#define WHEEL1 1
#define WHEEL2 2
#define WHEEL3 3
#define WHEEL4 4
#define WHEEL_LEFT 5
#define WHEEL_RIGHT 6
#define WHEEL_ALL 7

/**
��������
1.ǰ��
2.����
3.��ת��
4.��ת��
5.���ת��
6.�Һ�ת��
**/
#define MOTOR_STATE_FRONT 1
#define MOTOR_STATE_BACK 2
#define MOTOR_STATE_LEFT 3
#define MOTOR_STATE_RIGHT 4
#define MOTOR_STATE_LEFT_BACK 5
#define MOTOR_STATE_RIGHT_BACK 6


/**
*	��������:MotorChekInit
*   ��������:�����ʼ��
*	�������:��
*	����ֵ:��
**/
void MotorChekInit();


/**
*	��������:motor_left_wheel_front
*   ��������:��ǰ������
*	�������:ģʽ
*	����ֵ:��
**/
void motor_left_wheel_front(int mode);
/**
*	��������:motor_left_wheel_back
*   ��������:���������
*	�������:ģʽ
*	����ֵ:��
**/
void motor_left_wheel_back(int mode);
/**
*	��������:motor_right_wheel_front
*   ��������:��ǰ������
*	�������:ģʽ
*	����ֵ:��
**/
void motor_right_wheel_front(int mode);
/**
*	��������:motor_right_wheel_back
*   ��������:�Һ�������
*	�������:ģʽ
*	����ֵ:��
**/
void motor_right_wheel_back(int mode);


/**
*	��������:motor_wheel
*   ��������:���Ƶڼ������ӵ�״̬
*	�������:
*            wheel:���ӱ���
*			 mode��ģʽ
*	����ֵ:��
**/
void motor_wheel(int wheel,int mode);


/**


**/
/**
*	��������:motor_wheel
*   ��������:��������
			1.ǰ��
			2.����
			3.��ת��
			4.��ת��
			5.���ת��
			6.�Һ�ת��
*	�������:ģʽ
*	����ֵ:��
**/
void motor(int state);


#endif

