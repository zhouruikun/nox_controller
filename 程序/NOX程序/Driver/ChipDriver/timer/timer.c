#define TIMER_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "timer.h"
#include "nvic.h"
#include "pid.h"
#include "adc.h"
 #include "para.h"
void REF_I_ON_OFF(bool status);

/*

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
#ifndef  TIM3_Init
void TIM3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMER3, ENABLE); //时钟使能

    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIMER3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(  //使能或者失能指定的TIM中断
            TIMER3, //TIM2
            TIM_IT_Update  |  //TIM 中断源
            TIM_IT_Trigger,   //TIM 触发中断源  
            ENABLE  //使能
            );
    NVIC_InitStructure.NVIC_IRQChannel = TIMER3_IRQChannel;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    TIM_Cmd(TIMER3, ENABLE);  //使能TIMx外设
							 
}


void TIM3_IRQHandler(void)   //TIM3中断
{
    if (TIM_GetITStatus(TIMER3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
    {
        //timer_rev1();  //串口2接收定时函数     
        //key_timer();
    }
    TIM_ClearITPendingBit(TIMER3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
}

#endif

#ifndef  TIM2_Init
void TIM2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMER2, ENABLE); //时钟使能

    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIMER2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(  //使能或者失能指定的TIM中断
            TIMER2, //TIM2
            TIM_IT_Update  |  //TIM 中断源
            TIM_IT_Trigger,   //TIM 触发中断源  
            ENABLE  //使能
            );
    NVIC_InitStructure.NVIC_IRQChannel = TIMER2_IRQChannel;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    TIM_Cmd(TIMER2, ENABLE);  //使能TIMx外设
							 
}


void TIM2_IRQHandler(void)   //TIM3中断
{
    if (TIM_GetITStatus(TIMER2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
    {
        led1=!led1;
        //timer_1s_cousor();
        //timer_30s_brightness();
    }
    TIM_ClearITPendingBit(TIMER2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
}

#endif


//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器1!
#ifdef  TIM1_Init
void TIM1_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能
    
    TIM_TimeBaseStructure.TIM_Period = arr-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//设置了周期计数器值,RCR向下计数器每次计数至0，会产生一个更新事件且计数器重新由RCR值（N）开始计数
    
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(  //使能或者失能指定的TIM中断
            TIM1, //TIM2
            TIM_IT_Update,    //TIM 中断源
            //TIM_IT_Trigger,   //TIM 触发中断源 
            ENABLE  //使能
            );
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设
							 
}



void TIM1_UP_IRQHandler(void)
{
    //TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //TIM更新标志位
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
    }
}
#endif

*/
/*******************************************************************************
*函数功能：										
*函数描述：
***********************************************************************************/
void DK_TIMER_Init(u8 TIMERx,u32 period,u32 prescaler)
{
        //TIM_OCInitTypeDef        TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_BaseInitStructure;	 //通用定时计数器初始化TIMx的时间基数单位
	switch(TIMERx)
	{	   
		case 1:	
                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  //TIM1时钟使能
                    //TIM1用于产生PWM信号
                    TIM_BaseInitStructure.TIM_Period = period;  //PWM frequency : 281.250KHz
                    TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //TIM1CLK = 72 MHz
                    TIM_BaseInitStructure.TIM_ClockDivision = 0;  //设置了时钟分割，无分割72M
                    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM向上计数模
                    TIM_TimeBaseInit(TIM1,&TIM_BaseInitStructure);
                    TIM_SetCounter(TIM1, 0);               
                    TIM_Cmd(TIM1, ENABLE);
                    TIM_ClearFlag(TIM1, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
                    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //使能中断源	
		break;	  
		case 2:	
                     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //TIM1时钟使能
                     TIM_BaseInitStructure.TIM_Period = period; //周期值0x0000和0xFFFF之间  从初值加到这个值就产生中断源 35ms产生一次中断
                     TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //预分频值 0x0000和0xFFFF之间,对时钟分频  
                     TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置了时钟分割，无分割72M
                     TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM向上计数模
                     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //TIM2时钟使能
                     TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure);	
                     TIM_SetCounter(TIM2, 0);
                     TIM_Cmd(TIM2, ENABLE);	//TIM2总开关：开启
                     TIM_ClearFlag(TIM2, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
                     TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //使能中断源	
		break;
		case 3:	        
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //TIM1时钟使能
                    TIM_BaseInitStructure.TIM_Period = period; //周期值0x0000和0xFFFF之间  从初值加到这个值就产生中断源，1s产生一次中断
                    TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //预分频值 0x0000和0xFFFF之间,对时钟分频    
                    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置了时钟分割，无分割72M
                    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM向上计数模
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //TIM3时钟使能
                    TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);	                       
                    TIM_SetCounter(TIM3, 0);										
                    TIM_Cmd(TIM3, ENABLE);	//TIM3总开关：开启
                    TIM_ClearFlag(TIM3, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
		    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //使能中断源	
				
		break;

		case 4:	
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //TIM1时钟使能
                    //因为APB1的分频值为2，所以定时器2~7的输入时钟都被2倍频了，相应资料可看时间树
                    //	TIM_BaseInitStructure.TIM_Period = 2000; //周期值0x0000和0xFFFF之间  从初值加到这个值就产生中断源
                    // TIM_BaseInitStructure.TIM_Prescaler = 31999;  //预分频值 0x0000和0xFFFF之间,对时钟分频
                    TIM_BaseInitStructure.TIM_Period = period; //周期值0x0000和0xFFFF之间  从初值加到这个值就产生中断源
                    TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //预分频值 0x0000和0xFFFF之间,对时钟分频    
                    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置了时钟分割，无分割
                    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM向上计数模
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //TIM4时钟使能
                    TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure);	                                          	
                    TIM_SetCounter(TIM4, 0);						
                    TIM_Cmd(TIM4, ENABLE);	//TIM4总开关：开启
                    TIM_ClearFlag(TIM4, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断
                    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); //使能中断源
				
		break;
	}	
}

void DK_TIM_OPen_INT(u8 TIMERx)
{
	switch(TIMERx)
	{
		case 1:
		TIM_ClearFlag(TIM1, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //使能中断源		
		break;
		case 2:
		TIM_ClearFlag(TIM2, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //使能中断源	
		break;
		
		case 3:
		TIM_ClearFlag(TIM3, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //使能中断源	
		break;
		
		case 4:
		TIM_ClearFlag(TIM4, TIM_FLAG_Update); 	//清中断，以免一启用中断后立即产生中断				
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //使能中断源	
		break;
	}
}

void DK_TIM_All_Init(u8 TIMERx,u32 period,u32 prescaler)
{
    switch(TIMERx)
    {
        case 1:
            DK_NVIC_Init(0);//选择NVIC_PriorityGroup_0，4位全部为占先式优先级，要实现中断必须先初始化NVIC
            DK_NVIC_IRQ_Set(TIM1_UP_IRQn,0,0,ENABLE);//要实现外设中断，必须先设置外设的优先级
            DK_TIMER_Init(TIMERx,period,prescaler);
        break;
        case 2:
            DK_NVIC_Init(0);//选择NVIC_PriorityGroup_0，4位全部为占先式优先级，要实现中断必须先初始化NVIC
            DK_NVIC_IRQ_Set(TIM2_IRQn,0,0,ENABLE);//要实现外设中断，必须先设置外设的优先级
            DK_TIMER_Init(TIMERx,period,prescaler);
            //DK_TIM_OPen_INT(TIMERx);//这个不用也可以
        break;
        case 3:
            DK_NVIC_Init(0);//选择NVIC_PriorityGroup_0，4位全部为占先式优先级，要实现中断必须先初始化NVIC
            DK_NVIC_IRQ_Set(TIM3_IRQn,0,0,ENABLE);//要实现外设中断，必须先设置外设的优先级
            DK_TIMER_Init(TIMERx,period,prescaler);
        break;
        case 4:
            DK_NVIC_Init(0);//选择NVIC_PriorityGroup_0，4位全部为占先式优先级，要实现中断必须先初始化NVIC
            DK_NVIC_IRQ_Set(TIM4_IRQn,0,0,ENABLE);//要实现外设中断，必须先设置外设的优先级
            DK_TIMER_Init(TIMERx,period,prescaler);
        break;
       
    }
            
}

	extern  int sum_adc[7];
 extern int I_pump[7]; 
extern u8 counter;
extern u8 RT_Flag;
 extern u8 counter_RT;
extern   u8 RT_Flag;
extern u16 Ref_R_PT ;
void cal_current_rpt(void);
void TIM1_UP_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
    {
      TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
   //  ADC_ContinuousCmd(ADC1, DISABLE);
			
				I_pump[0] = sum_adc[0]/counter;
				I_pump[1] = sum_adc[1]/counter;
				I_pump[2] = sum_adc[2]/counter;
				I_pump[3] = sum_adc[3]/counter;
			AD_val[4] =  sum_adc[4]/counter_RT;
			AD_val[5] =  sum_adc[5]/counter_RT;
			AD_val[6] =  sum_adc[6]/counter_RT;
			RT_Flag=0; 
			counter=0;
			counter_RT=0;
				sum_adc[0]=0;
				sum_adc[1]=0;
				sum_adc[2]=0;
				sum_adc[3]=0;		
				sum_adc[4]=0;
				sum_adc[5]=0;
				sum_adc[6]=0;			
				MeasureAndSend();//测量并发送
				cal_current_rpt();
		    REF_I_ON_OFF(1);
	
    }
}
 



