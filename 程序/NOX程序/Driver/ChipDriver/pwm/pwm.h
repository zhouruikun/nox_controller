#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"
#include "datatype.h"


#define timer1  1
#define timer2  2
#define timer3  3
#define timer4  4
#define timer5  5
#define timer6  6
#define timer7  7
#define timer8  8


#define Valve_period 500//500us
#define Valve_CCR_Val 440//440us 
#define Gripper1_period 520//1ms
#define Gripper1_CCR_Val 320//500us
#define Gripper2_CCR_Val 320//500us
#define Gripper2_period 520//1ms
//void TIM3_PWM_Init(u16 arr,u16 psc);
//void TIM1_PWM_Init(u16 arr,u16 psc);
void DK_TIM1_PWM_Init(void);//PWM初始化
void DK_TIM4_PWM_Init(void);//PWM初始化
void DK_TIM3_PWM_Init(void);
void Tim_PwmOut(TIM_TypeDef* TIMx, uint16_t Compare2);//Tim_PwmOut(TIM3,led0pwmval);
//TIMERx->哪个定时器,prescaler->预分频，period->周期，CCR_Val->占空比
void DK_TIM_PWM(unsigned char TIMERx, unsigned int period,unsigned int prescaler,unsigned int CCR_Val,unsigned char channel);
//TIMERx->哪个定时器,CCR_Val->占空比
void DK_TIM_PWM_Reload(unsigned char TIMERx,unsigned int CCR_Val,unsigned char channel );//重设占空比
void Output_compare4_enable(uint8 channel,uint8 y_n);

void Output_compare3_enable(uint8 channel,uint8 y_n);
void Output_compare1_enable(uint8 channel,uint8 y_n);
#endif
