#ifndef __cap_H
#define __cap_H

#include "stm32f10x.h"
#include "datatype.h"

void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM2_Cap_Init(u16 arr,u16 psc);
u32 Cap_TIM2_Complete(void);
u32 Cap_TIM5_Complete(void);

#endif