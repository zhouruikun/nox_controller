#define ENCODER_globals
#include "enconder.h"
#include "para.h"
#include "pininputoutput.h"
#include "pattern_para.h"
#include "public_function.h"
/* Private variables ---------------------------------------------------------*/

//****************************************************************************************************
//�����������ӿڵĳ�ʼ��
//****************************************************************************************************
extern uint16 ColorCount;//���ͼ���
void ENC_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_ICInitTypeDef  TIM2_ICInitStructure;
  //TIM_OCInitTypeDef TIM_OCInitStructure;//��������Ƚϳ�ʼ���ṹ�����

  
  RCC_APB1PeriphClockCmd(RCC_APBPeriph_ENCODER_TIMER, ENABLE);	   // ENCODER_TIMERʱ�ӳ�ʼ��
  RCC_APB2PeriphClockCmd(RCC_APBPeriph_ENCODER_GPIO, ENABLE);	   // ENCODER_GPIOʱ�ӳ�ʼ��
  
  GPIO_StructInit(&GPIO_InitStructure);				  //TI1 TI2��ʼ��
  GPIO_InitStructure.GPIO_Pin = ENCODER_TI1 | ENCODER_TI2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //�������
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ENCODER_GPIO, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = ENCODER_ZI ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); 
  
  
  NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQChannel;	 //����ENCODER_TIMER�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Timer configuration in Encoder mode */			//����ENCODER_TIMERΪ������ģʽ
  TIM_DeInit(ENCODER_TIMER);				        //ENCODER_TIMER��λ
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                     // �޷�Ƶ
  TIM_TimeBaseStructure.TIM_Period = (4*ENCODER_PPR)-1;       //����������ֵ 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ   
  TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure);
 
  /*
  // Ԥ��Ƶ����
  //TIM_PrescalerConfig(TIM2, 71, TIM_PSCReloadMode_Immediate);
  //����Ƚ�ʱ��ģʽ���ã�ͨ��1 
  //TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_Timing;//����ط����ǸıȽ�ģʽ��
  //�������ڱȽ�ģʽ����ѡ�ĸ����ڲ����жϵ�������һ���ģ�����ѡTIMING������

  TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//ʹ��TIM2_CH1ͨ��
  TIM_OCInitStructure.TIM_Pulse=10000;//��ת���ڣ�2000������
  TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//���Ϊ���߼�
  TIM_OC1Init(ENCODER_TIMER, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(ENCODER_TIMER, TIM_OCPreload_Disable);//��ֹTIM_CCR1�Ĵ�����Ԥװ��ʹ��
//TIMx_CCRx�Ĵ����ܹ����κ�ʱ��ͨ��������и����Կ���������Σ�������
//δʹ��Ԥװ�ؼĴ���(OCxPE=��0��������TIMx_CCRxӰ�ӼĴ���ֻ���ڷ�����
//һ�θ����¼�ʱ������)����������ΪDisable����Ϊ�˺������жϷ����ӳ�������޸�
//TIMx_CCRʵʱ������

*/
  
  //��ʼ��TIM2���벶�����
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01ѡ������� IC1ӳ�䵽TI1��
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//�����ز���
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ӳ�䵽TI1��
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//���������Ƶ,����Ƶ 
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);

  TIM_EncoderInterfaceConfig(
                             ENCODER_TIMER,                 //��ѡ��TIM���� 
                             TIM_EncoderMode_TI12,          //ʹ��TIM����ģʽ3
                             TIM_ICPolarity_Rising,         //TIM���벶�������� 
                             TIM_ICPolarity_Rising);	    //�������ӿڳ�ʼ��
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
// �������ת������ڳ�ʼλ�õĽǶ�	  -180��+180
//****************************************************************************************************
s16 ENC_Get_Electrical_Angle(void)
{
    //int32_t temp;
    int16_t tim_count;	
    s16 Angle;
    tim_count=TIM_GetCounter(ENCODER_TIMER);   //��ȡENCODER_TIMER��ֵ
    if ( (ENCODER_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down) 
    {// encoder timer down-counting ��ת
         Angle=((4*ENCODER_PPR)-tim_count)*360/(4*ENCODER_PPR);//��������
    }
    else
    {//encoder timer up-counting ��ת
         Angle=tim_count*360/(4*ENCODER_PPR);//��������
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
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); //���ж� 
        
        Electrical_Angle=TIM_GetCounter(ENCODER_TIMER);//�õ��������Ƕ�
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
        TIM_SetCompare1(TIM2, capture+500);//�Ƚ�ֵ��
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



