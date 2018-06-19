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
//主cpu输出       从输入  阀                          从输出
//VIN1==PD13   ->   PE0   //___|----|____|----|____   PD13   跟主CPU一样信号
//VIN11==PD12  ->   PC12  //___|-------------------   PD12   PWM
//主cpu输出       从输入  夹纱器
//GIN22==PD8   ->   PB6   A喷
//GIN11==PD10  ->   PB7   B喷

void DK_EXTI_Init(u8 GPIOx,u16 EXTI_Linex,u8 Type);//DK_EXTI_Init(PB, EXTI_Line6, Trigger_Falling);
//头了点动
//Gpio 引脚 PA1 PA2
#define CoilFeederInA GPIO_Pin_1
#define CoilFeederInB GPIO_Pin_2
//中断线

#define EXTI_LINE_CoilFeederInA    EXTI_Line1
#define EXTI_LINE_CoilFeederInB    EXTI_Line2

//接收四根信号线
//GPIO引脚 PB6 PB7 PB8 PB9
#define GripperIn1  GPIO_Pin_6 //夹纱器1输入
#define GripperIn2  GPIO_Pin_7 //夹纱器2输入
#define Valvein1    GPIO_Pin_8 //转阀1输入PE0
#define Valvein2    GPIO_Pin_9 //转阀2输入PC12

//中断线
#define EXTI_LINE_GripperIn1    EXTI_Line6
#define EXTI_LINE_GripperIn2    EXTI_Line7
#define EXTI_LINE_Valvein1      EXTI_Line8
#define EXTI_LINE_Valvein2      EXTI_Line9

//EXTI_ext u8 start_count_flag;
EXTI_ext u8  Exit8_sta,Valve_dule_flag1,valve1_timer_count,valve2_timer_count;
//           中断状态, 阀1标志位  Valve_dule_flag1=1时A喷,Valve_dule_flag1=0时B喷
EXTI_ext u8  Exit9_sta;	//中断状态	
EXTI_ext u8  Exit6_sta,Gripper1_timer_count;
EXTI_ext u8  Exit7_sta,Gripper2_timer_count;
EXTI_ext u8  Exit1_sta;	//中断状态
EXTI_ext u8  Exit2_sta;	//中断状态

void  Extix_Init(void);//IO初始化
		 					    
#endif

