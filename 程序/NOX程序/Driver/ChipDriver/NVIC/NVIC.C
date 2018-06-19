#include "misc.h"
#include "NVIC.H"


void DK_NVIC_Init(u8 Group)
{
	switch(Group)
	{
		case 0:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		break;
		case 1:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		break;
		case 2:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
		break;
		case 3:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
		break;
		case 4:
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
		break;
	}
}

void DK_NVIC_IRQ_Set(u8 NVIC_IRQChannel, u8 pre_pri, u8 sub_pri, FunctionalState cmd)
{
  NVIC_InitTypeDef NVIC_InitStructure;	
  //NVIC_ClearPendingIRQ(NVIC_IRQChannel); 
  NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;	
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = pre_pri;  //抢占优先级		
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = sub_pri;				 //子优先级0
  NVIC_InitStructure.NVIC_IRQChannelCmd = cmd;
  NVIC_Init(&NVIC_InitStructure);
}
/******************* (C) COPYRIGHT 2012 D&K电子工作室 *****END OF FILE****************/
