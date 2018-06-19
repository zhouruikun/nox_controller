
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
Gripper_Valve_ext void Valve_pin_init(void);//阀GPIO口初始化
Gripper_Valve_ext void ValveOut(uint8 val);//阀输出 
Gripper_Valve_ext void Valve_init(void);//阀初始化


Gripper_Valve_ext void Gripper_init(void);
Gripper_Valve_ext void Gripper_pin_init(void);//夹纱器GPIO口初始化
Gripper_Valve_ext void Gripper1Out(uint8 val);//夹纱器A输出
Gripper_Valve_ext void Gripper2Out(uint8 val);//夹纱器B输出

#endif
