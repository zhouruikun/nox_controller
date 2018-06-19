#ifndef __EXTI_H
#define __EXIT_H	 

#include "stm32f10x.h"
//#include "datatype.h"

#ifdef   EXTI_globals
#define  EXTI_ext
#else
#define  EXTI_ext  extern
#endif
#define Trigger_Rising 1
#define Trigger_Falling 2
#define Trigger_Rising_Falling 3
//��cpu���       ������  ��                          �����
//VIN1==PD13   ->   PE0   //___|----|____|----|____   PD13   ����CPUһ���ź�
//VIN11==PD12  ->   PC12  //___|-------------------   PD12   PWM
//��cpu���       ������  ��ɴ��
//GIN22==PD8   ->   PB6   A��
//GIN11==PD10  ->   PB7   B��

void DK_EXTI_Init(u8 GPIOx,u16 EXTI_Linex,u8 Type);//DK_EXTI_Init(PB, EXTI_Line6, Trigger_Falling);
//ͷ�˵㶯
//Gpio ���� PA1 PA2
#define CoilFeederInA GPIO_Pin_1
#define CoilFeederInB GPIO_Pin_2
//�ж���

#define EXTI_LINE_CoilFeederInA    EXTI_Line1
#define EXTI_LINE_CoilFeederInB    EXTI_Line2

//�����ĸ��ź���
//GPIO���� PB6 PB7 PB8 PB9
#define GripperIn1  GPIO_Pin_6 //��ɴ��1����
#define GripperIn2  GPIO_Pin_7 //��ɴ��2����
#define Valvein1    GPIO_Pin_8 //ת��1����PE0
#define Valvein2    GPIO_Pin_9 //ת��2����PC12

//�ж���
#define EXTI_LINE_GripperIn1    EXTI_Line6
#define EXTI_LINE_GripperIn2    EXTI_Line7
#define EXTI_LINE_Valvein1      EXTI_Line8
#define EXTI_LINE_Valvein2      EXTI_Line9

//EXTI_ext u8 start_count_flag;
EXTI_ext u8  Exit8_sta,Valve_dule_flag1,valve1_timer_count,valve2_timer_count;
//           �ж�״̬, ��1��־λ  Valve_dule_flag1=1ʱA��,Valve_dule_flag1=0ʱB��
EXTI_ext u8  Exit9_sta;	//�ж�״̬	
EXTI_ext u8  Exit6_sta,Gripper1_timer_count;
EXTI_ext u8  Exit7_sta,Gripper2_timer_count;
EXTI_ext u8  Exit1_sta;	//�ж�״̬
EXTI_ext u8  Exit2_sta;	//�ж�״̬

void  Extix_Init(void);//IO��ʼ��
		 					    
#endif

