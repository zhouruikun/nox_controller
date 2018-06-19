#define ENCODER_globals
#include "enconder.h"
#include "para.h"
#include "pininputoutput.h"
#include "pattern_para.h"
#include "public_function.h"
/* Private variables ---------------------------------------------------------*/

//****************************************************************************************************
//正交编码器接口的初始化
//****************************************************************************************************
extern uint16 ColorCount;//花型计数
void ENC_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef  TIM2_ICInitStructure;
  //TIM_OCInitTypeDef TIM_OCInitStructure;//定义输出比较初始化结构体变量

  
  RCC_APB1PeriphClockCmd(RCC_APBPeriph_ENCODER_TIMER, ENABLE);	   // ENCODER_TIMER时钟初始化
  RCC_APB2PeriphClockCmd(RCC_APBPeriph_ENCODER_GPIO, ENABLE);	   // ENCODER_GPIO时钟初始化
  
  GPIO_StructInit(&GPIO_InitStructure);				  //TI1 TI2初始化
  GPIO_InitStructure.GPIO_Pin = ENCODER_TI1 | ENCODER_TI2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //浮空输出
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENCODER_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = ENCODER_ZI ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  
  NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQChannel;	 //设置ENCODER_TIMER的优先级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Timer configuration in Encoder mode */			//设置ENCODER_TIMER为编码器模式
  TIM_DeInit(ENCODER_TIMER);				        //ENCODER_TIMER复位
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                     // 无分频
  TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;       //计数器重载值 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式   
  TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure);
 
  /*
  // 预分频配置
  //TIM_PrescalerConfig(TIM2, 71, TIM_PSCReloadMode_Immediate);
  //输出比较时间模式配置：通道1 
  //TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_Timing;//这个地方就是改比较模式的
  //但是由于比较模式无论选哪个对于产生中断的作用是一样的，所以选TIMING都可以

  TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//使能TIM2_CH1通道
  TIM_OCInitStructure.TIM_Pulse=10000;//翻转周期：2000个脉冲
  TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出为正逻辑
  TIM_OC1Init(ENCODER_TIMER, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(ENCODER_TIMER, TIM_OCPreload_Disable);//禁止TIM_CCR1寄存器的预装载使能
//TIMx_CCRx寄存器能够在任何时候通过软件进行更新以控制输出波形，条件是
//未使用预装载寄存器(OCxPE=’0’，否则TIMx_CCRx影子寄存器只能在发生下
//一次更新事件时被更新)。这里设置为Disable就是为了后面在中断服务子程序可以修改
//TIMx_CCR实时起作用

*/
  
  //初始化TIM2输入捕获参数
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01选择输入端 IC1映射到TI1上
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//上升沿捕获
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//映射到TI1上
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//配置输入分频,不分频 
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);

  TIM_EncoderInterfaceConfig(
                             ENCODER_TIMER,                 //来选择TIM外设 
                             TIM_EncoderMode_TI12,          //使用TIM编码模式3
                             TIM_ICPolarity_Rising,         //TIM输入捕获上升沿 
                             TIM_ICPolarity_Rising);	    //编码器接口初始化
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
  TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);
  
 // Clear all pending interrupts
  TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);
  TIM_ITConfig(ENCODER_TIMER, TIM_IT_CC3, ENABLE);
  //TIM_ITConfig(ENCODER_TIMER, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM2->CNT = COUNTER_RESET;
  
  TIM_Cmd(ENCODER_TIMER, ENABLE);  
}

int16 Get_Enconder_Counter(void)
{
    return TIM_GetCounter(ENCODER_TIMER);
}


//****************************************************************************************************
// 计算马达转子相对于初始位置的角度	  -180至+180
//****************************************************************************************************
s16 ENC_Get_Electrical_Angle(void)
{
    //int32_t temp;
    int16_t tim_count;	
    s16 Angle;
    tim_count=TIM_GetCounter(ENCODER_TIMER);   //获取ENCODER_TIMER的值
    if ( (ENCODER_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down) 
    {// encoder timer down-counting 反转
         Angle=((4*ENCODER_PPR)-tim_count)*360/(4*ENCODER_PPR);//整数部分
    }
    else
    {//encoder timer up-counting 正转
         Angle=tim_count*360/(4*ENCODER_PPR);//整数部分
    }
    return Angle;
													
}
/*******************************************************************************
* Function Name  : ENC_Calc_Average_Speed
* Description    : Compute smoothed motor speed based on last SPEED_BUFFER_SIZE
                   informations and store it variable  
* Input          : None
* Output         : s16
* Return         : Return rotor speed in 0.1 Hz resolution. This routine 
                   will return the average mechanical speed of the motor.
*******************************************************************************/
void ENC_Calc_Average_Speed(void)
{   
  s32 wtemp;
  u32 i;
  
  wtemp = ENC_Get_Electrical_Angle();
        
/* Compute the average of the read speeds */  
  hSpeed_Buffer[bSpeed_Buffer_Index] = (s16)wtemp;
  bSpeed_Buffer_Index++;
  
  if (bSpeed_Buffer_Index == SPEED_BUFFER_SIZE) 
  {
    bSpeed_Buffer_Index = 0;
  }

  wtemp=0;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    wtemp += hSpeed_Buffer[i];
  }
  wtemp /= SPEED_BUFFER_SIZE;
  
  hRot_Speed = ((s16)(wtemp));
}
/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
void TIM2_IRQHandler(void)
{
    //uint16 capture;

    //TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);
    if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); //清中断 
        
        Electrical_Angle=TIM_GetCounter(ENCODER_TIMER);//得到编码器角度
            if(Electrical_Angle>500 && Electrical_Angle<900)
            //if(Electrical_Angle>elm[2].angle_on && Electrical_Angle<elm[2].angle_off)
            {
                GripperOutA(1);
            }
            else 
            {
                GripperOutA(0);
            } 
        capture=TIM_GetCapture1(TIM2);
        TIM_SetCompare1(TIM2, capture+500);//比较值加
    }
    
}
*/
void TIM2_IRQHandler(void)
{

    if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC3 );
        TIM2->CNT = COUNTER_RESET;
        flag_z++;
        z_count++;
        z_count2++;
    }
}



