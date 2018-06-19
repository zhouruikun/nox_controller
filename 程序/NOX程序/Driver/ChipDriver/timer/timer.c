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

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
#ifndef  TIM3_Init
void TIM3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMER3, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIMER3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
            TIMER3, //TIM2
            TIM_IT_Update  |  //TIM �ж�Դ
            TIM_IT_Trigger,   //TIM �����ж�Դ  
            ENABLE  //ʹ��
            );
    NVIC_InitStructure.NVIC_IRQChannel = TIMER3_IRQChannel;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIMER3, ENABLE);  //ʹ��TIMx����
							 
}


void TIM3_IRQHandler(void)   //TIM3�ж�
{
    if (TIM_GetITStatus(TIMER3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
        //timer_rev1();  //����2���ն�ʱ����     
        //key_timer();
    }
    TIM_ClearITPendingBit(TIMER3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
}

#endif

#ifndef  TIM2_Init
void TIM2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMER2, ENABLE); //ʱ��ʹ��

    TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc-1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIMER2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
            TIMER2, //TIM2
            TIM_IT_Update  |  //TIM �ж�Դ
            TIM_IT_Trigger,   //TIM �����ж�Դ  
            ENABLE  //ʹ��
            );
    NVIC_InitStructure.NVIC_IRQChannel = TIMER2_IRQChannel;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_Cmd(TIMER2, ENABLE);  //ʹ��TIMx����
							 
}


void TIM2_IRQHandler(void)   //TIM3�ж�
{
    if (TIM_GetITStatus(TIMER2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
        led1=!led1;
        //timer_1s_cousor();
        //timer_30s_brightness();
    }
    TIM_ClearITPendingBit(TIMER2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
}

#endif


//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��1!
#ifdef  TIM1_Init
void TIM1_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
    
    TIM_TimeBaseStructure.TIM_Period = arr-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//���������ڼ�����ֵ,RCR���¼�����ÿ�μ�����0�������һ�������¼��Ҽ�����������RCRֵ��N����ʼ����
    
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
            TIM1, //TIM2
            TIM_IT_Update,    //TIM �ж�Դ
            //TIM_IT_Trigger,   //TIM �����ж�Դ 
            ENABLE  //ʹ��
            );
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx����
							 
}



void TIM1_UP_IRQHandler(void)
{
    //TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //TIM���±�־λ
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
    }
}
#endif

*/
/*******************************************************************************
*�������ܣ�										
*����������
***********************************************************************************/
void DK_TIMER_Init(u8 TIMERx,u32 period,u32 prescaler)
{
        //TIM_OCInitTypeDef        TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_BaseInitStructure;	 //ͨ�ö�ʱ��������ʼ��TIMx��ʱ�������λ
	switch(TIMERx)
	{	   
		case 1:	
                    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  //TIM1ʱ��ʹ��
                    //TIM1���ڲ���PWM�ź�
                    TIM_BaseInitStructure.TIM_Period = period;  //PWM frequency : 281.250KHz
                    TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //TIM1CLK = 72 MHz
                    TIM_BaseInitStructure.TIM_ClockDivision = 0;  //������ʱ�ӷָ�޷ָ�72M
                    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM���ϼ���ģ
                    TIM_TimeBaseInit(TIM1,&TIM_BaseInitStructure);
                    TIM_SetCounter(TIM1, 0);               
                    TIM_Cmd(TIM1, ENABLE);
                    TIM_ClearFlag(TIM1, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
                    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //ʹ���ж�Դ	
		break;	  
		case 2:	
                     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //TIM1ʱ��ʹ��
                     TIM_BaseInitStructure.TIM_Period = period; //����ֵ0x0000��0xFFFF֮��  �ӳ�ֵ�ӵ����ֵ�Ͳ����ж�Դ 35ms����һ���ж�
                     TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //Ԥ��Ƶֵ 0x0000��0xFFFF֮��,��ʱ�ӷ�Ƶ  
                     TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //������ʱ�ӷָ�޷ָ�72M
                     TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM���ϼ���ģ
                     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //TIM2ʱ��ʹ��
                     TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure);	
                     TIM_SetCounter(TIM2, 0);
                     TIM_Cmd(TIM2, ENABLE);	//TIM2�ܿ��أ�����
                     TIM_ClearFlag(TIM2, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
                     TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ���ж�Դ	
		break;
		case 3:	        
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //TIM1ʱ��ʹ��
                    TIM_BaseInitStructure.TIM_Period = period; //����ֵ0x0000��0xFFFF֮��  �ӳ�ֵ�ӵ����ֵ�Ͳ����ж�Դ��1s����һ���ж�
                    TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //Ԥ��Ƶֵ 0x0000��0xFFFF֮��,��ʱ�ӷ�Ƶ    
                    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //������ʱ�ӷָ�޷ָ�72M
                    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM���ϼ���ģ
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //TIM3ʱ��ʹ��
                    TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);	                       
                    TIM_SetCounter(TIM3, 0);										
                    TIM_Cmd(TIM3, ENABLE);	//TIM3�ܿ��أ�����
                    TIM_ClearFlag(TIM3, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
		    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //ʹ���ж�Դ	
				
		break;

		case 4:	
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //TIM1ʱ��ʹ��
                    //��ΪAPB1�ķ�ƵֵΪ2�����Զ�ʱ��2~7������ʱ�Ӷ���2��Ƶ�ˣ���Ӧ���Ͽɿ�ʱ����
                    //	TIM_BaseInitStructure.TIM_Period = 2000; //����ֵ0x0000��0xFFFF֮��  �ӳ�ֵ�ӵ����ֵ�Ͳ����ж�Դ
                    // TIM_BaseInitStructure.TIM_Prescaler = 31999;  //Ԥ��Ƶֵ 0x0000��0xFFFF֮��,��ʱ�ӷ�Ƶ
                    TIM_BaseInitStructure.TIM_Period = period; //����ֵ0x0000��0xFFFF֮��  �ӳ�ֵ�ӵ����ֵ�Ͳ����ж�Դ
                    TIM_BaseInitStructure.TIM_Prescaler = prescaler-1;  //Ԥ��Ƶֵ 0x0000��0xFFFF֮��,��ʱ�ӷ�Ƶ    
                    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //������ʱ�ӷָ�޷ָ�
                    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // TIM���ϼ���ģ
                    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //TIM4ʱ��ʹ��
                    TIM_TimeBaseInit(TIM4, &TIM_BaseInitStructure);	                                          	
                    TIM_SetCounter(TIM4, 0);						
                    TIM_Cmd(TIM4, ENABLE);	//TIM4�ܿ��أ�����
                    TIM_ClearFlag(TIM4, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�
                    TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE); //ʹ���ж�Դ
				
		break;
	}	
}

void DK_TIM_OPen_INT(u8 TIMERx)
{
	switch(TIMERx)
	{
		case 1:
		TIM_ClearFlag(TIM1, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
		TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //ʹ���ж�Դ		
		break;
		case 2:
		TIM_ClearFlag(TIM2, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ���ж�Դ	
		break;
		
		case 3:
		TIM_ClearFlag(TIM3, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //ʹ���ж�Դ	
		break;
		
		case 4:
		TIM_ClearFlag(TIM4, TIM_FLAG_Update); 	//���жϣ�����һ�����жϺ����������ж�				
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //ʹ���ж�Դ	
		break;
	}
}

void DK_TIM_All_Init(u8 TIMERx,u32 period,u32 prescaler)
{
    switch(TIMERx)
    {
        case 1:
            DK_NVIC_Init(0);//ѡ��NVIC_PriorityGroup_0��4λȫ��Ϊռ��ʽ���ȼ���Ҫʵ���жϱ����ȳ�ʼ��NVIC
            DK_NVIC_IRQ_Set(TIM1_UP_IRQn,0,0,ENABLE);//Ҫʵ�������жϣ�������������������ȼ�
            DK_TIMER_Init(TIMERx,period,prescaler);
        break;
        case 2:
            DK_NVIC_Init(0);//ѡ��NVIC_PriorityGroup_0��4λȫ��Ϊռ��ʽ���ȼ���Ҫʵ���жϱ����ȳ�ʼ��NVIC
            DK_NVIC_IRQ_Set(TIM2_IRQn,0,0,ENABLE);//Ҫʵ�������жϣ�������������������ȼ�
            DK_TIMER_Init(TIMERx,period,prescaler);
            //DK_TIM_OPen_INT(TIMERx);//�������Ҳ����
        break;
        case 3:
            DK_NVIC_Init(0);//ѡ��NVIC_PriorityGroup_0��4λȫ��Ϊռ��ʽ���ȼ���Ҫʵ���жϱ����ȳ�ʼ��NVIC
            DK_NVIC_IRQ_Set(TIM3_IRQn,0,0,ENABLE);//Ҫʵ�������жϣ�������������������ȼ�
            DK_TIMER_Init(TIMERx,period,prescaler);
        break;
        case 4:
            DK_NVIC_Init(0);//ѡ��NVIC_PriorityGroup_0��4λȫ��Ϊռ��ʽ���ȼ���Ҫʵ���жϱ����ȳ�ʼ��NVIC
            DK_NVIC_IRQ_Set(TIM4_IRQn,0,0,ENABLE);//Ҫʵ�������жϣ�������������������ȼ�
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
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {
      TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
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
				MeasureAndSend();//����������
				cal_current_rpt();
		    REF_I_ON_OFF(1);
	
    }
}
 



