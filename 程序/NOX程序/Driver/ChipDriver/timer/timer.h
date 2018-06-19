#ifndef __TIMER_H
#define __TIMER_H
//#include "sys.h"
	  
#ifdef   TIMER_globals
#define  TIMER_ext
#else
#define  TIMER_ext  extern
#endif  






#define TIMER2                  TIM2  
#define RCC_APB1Periph_TIMER2   RCC_APB1Periph_TIM2
#define TIMER2_IRQChannel       TIM2_IRQn

#define TIMER3                  TIM3  
#define RCC_APB1Periph_TIMER3   RCC_APB1Periph_TIM3
#define TIMER3_IRQChannel       TIM3_IRQn

void TIM1_Init(u16 arr,u16 psc);
void TIM2_Init(u16 arr,u16 psc);
void TIM3_Init(u16 arr,u16 psc);

void TIM4_Cap_Init(u16 arr,u16 psc); 
void TIM3_PWM_Init(u16 arr,u16 psc);
//TIMERx->第几个定时器,period->周期,prescaler->预分频
void DK_TIM_All_Init(u8 TIMERx,u32 period,u32 prescaler);


TIMER_ext u8 timer1_flag;

#endif
