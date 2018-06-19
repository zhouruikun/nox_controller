#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"
#include "datatype.h"

#ifdef   ENCODER_globals
#define  ENCODER_ext
#else
#define  ENCODER_ext  extern
#endif

//****************************************************************************************************
//编码器的接口
//****************************************************************************************************
#define ENCODER_GPIO GPIOA
#define ENCODER_TI1	  GPIO_Pin_0
#define	ENCODER_TI2	  GPIO_Pin_1
#define	ENCODER_ZI	  GPIO_Pin_2
#define RCC_APBPeriph_ENCODER_GPIO	  RCC_APB2Periph_GPIOA
//****************************************************************************************************
// 定时器ENCODER_TIMER
//****************************************************************************************************
#define ENCODER_TIMER   TIM2  // Encoder unit connected to TIM2
#define RCC_APBPeriph_ENCODER_TIMER    RCC_APB1Periph_TIM2
#define TIMER_IRQChannel		 TIM2_IRQn

#define ENCODER_PPR     (uint16_t)(360) // number of pulses per revolution

#define COUNTER_RESET   (uint16_t)0
#define ICx_FILTER      (uint8_t) 6 // 6<-> 670nsec
//
#define TIMx_PRE_EMPTION_PRIORITY 1	//ENCODER_TIMER先占优先级
#define TIMx_SUB_PRIORITY 0		//ENCODER_TIMER从优先级   
#define SPEED_BUFFER_SIZE 8

static s16  hSpeed_Buffer[SPEED_BUFFER_SIZE],hRot_Speed;
static u8 bSpeed_Buffer_Index = 0;


ENCODER_ext void ENC_Init(void);
ENCODER_ext int16 Get_Enconder_Counter(void);
//ENCODER_ext s16 ENC_Calc_Rot_Speed(void);
ENCODER_ext s16 ENC_Get_Electrical_Angle(void);
ENCODER_ext void ENC_Calc_Average_Speed(void);

#endif