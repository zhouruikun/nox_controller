
#ifndef __Gripper_Valve_H
#define __Gripper_Valve_H
#include "stm32f10x.h"
#include "datatype.h"
#ifdef   Gripper_Valve_globals
#define  Gripper_Valve_ext
#else
#define  Gripper_Valve_ext  extern
#endif



Gripper_Valve_ext void valve1_timer_1ms(void);
Gripper_Valve_ext void Gripper1_timer_1ms(void);
Gripper_Valve_ext void Gripper2_timer_1ms(void);
Gripper_Valve_ext void Valve_pin_init(void);//��GPIO�ڳ�ʼ��
Gripper_Valve_ext void ValveOut(uint8 val);//����� 
Gripper_Valve_ext void Valve_init(void);//����ʼ��


Gripper_Valve_ext void Gripper_init(void);
Gripper_Valve_ext void Gripper_pin_init(void);//��ɴ��GPIO�ڳ�ʼ��
Gripper_Valve_ext void Gripper1Out(uint8 val);//��ɴ��A���
Gripper_Valve_ext void Gripper2Out(uint8 val);//��ɴ��B���

#endif
