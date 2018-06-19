
#include "stm32f10x.h"
#include "datatype.h"
#include "SysTick.h"
#include "comm.h"
#include "gripper_valve.h"
#include "CommTimerFunction.h"
void SysTick_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  
    
    NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
    
}

void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
        /* Capture error */ 
        while (1);
    }
    SysTick_NVIC_Configuration();
    
}


/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
	
    timer_rev1();  //����2���ն�ʱ����
    timer_rev2();  //����2���ն�ʱ����
    pressure_measurement_timer();//ѹ��������ʱ
	
	if(delay_cnt>0)
	{
			delay_cnt--;
	}
	

 
	IRQ_Handle();
   //valve1_timer_1ms();
    //Gripper1_timer_1ms(); 
    //Gripper2_timer_1ms();
}
