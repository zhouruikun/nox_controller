#include "cap.h"

//��ʱ��5ͨ��1���벶������

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ��TIM2ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);//ʹ��GPIOAʱ��
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;  //PA0 ���֮ǰ����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA0 ����
    
    //��ʼ����ʱ��2 TIM2	 
    TIM_TimeBaseStructure.TIM_Period = arr-1;//�趨�������Զ���װֵ 
    TIM_TimeBaseStructure.TIM_Prescaler =psc;//Ԥ��Ƶ��   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM2���벶�����
    TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01ѡ������� IC1ӳ�䵽TI1��
    TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//�����ز���
    TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ӳ�䵽TI1��
    TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//���������Ƶ,����Ƶ 
    TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM2, &TIM2_ICInitStructure);
    
    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
    
    TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC3IE�����ж�	
    
    TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��5
   


}

u8  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16 TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
 
u32 Cap_TIM2_Complete(void)
{
    static u32 temp;
    if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
    {
        temp=TIM2CH1_CAPTURE_STA&0X3F;
        temp*=65536;//���ʱ���ܺ�
        temp+=TIM2CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
        //printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
        TIM2CH1_CAPTURE_STA=0;//������һ�β���
    }
    return temp;
}
//��ʱ��5�жϷ������	 
void TIM2_IRQHandler(void)
{ 
    if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
    {	  
        if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
        {	    
            if(TIM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
            {
                if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                {
                    TIM2CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
                    TIM2CH1_CAPTURE_VAL=0XFFFF;
                }
                else 
                {
                    TIM2CH1_CAPTURE_STA++;
                }                        
            }	 
        }
        if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)//����1���������¼�
        {	
            if(TIM2CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
            {	  			
                TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
                TIM2CH1_CAPTURE_VAL=TIM_GetCapture3(TIM2);
                TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
                //TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
            }
            else  								//��δ��ʼ,��һ�β���������
            {
                TIM2CH1_CAPTURE_STA=0;			//���
                TIM2CH1_CAPTURE_VAL=0;
                TIM_SetCounter(TIM2,0);
                TIM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
                TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
                //TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
            }		    
        }			     	    					   
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_CC3|TIM_IT_Update); //����жϱ�־λ
 
}
/*

//��ʱ��5ͨ��1���벶������

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
    
    //��ʼ����ʱ��5 TIM5	 
    TIM_TimeBaseStructure.TIM_Period = arr-1; //�趨�������Զ���װֵ 
    TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM5���벶�����
    TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
    TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
    TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
    TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
    TIM_ICInit(TIM5, &TIM5_ICInitStructure);
    
    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
    
    TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
    
    TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
   


}

u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16 TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
 
u32 Cap_TIM5_Complete(void)
{
    static u32 temp;
    if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
    {
        temp=TIM5CH1_CAPTURE_STA&0X3F;
        temp*=65536;//���ʱ���ܺ�
        temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĸߵ�ƽʱ��
        //printf("HIGH:%d us\r\n",temp);//��ӡ�ܵĸߵ�ƽʱ��
        TIM5CH1_CAPTURE_STA=0;//������һ�β���
    }
    return temp;
}
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 
    if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
    {	  
        if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) 
        {	    
            if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
            {
                if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
                {
                    TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
                    TIM5CH1_CAPTURE_VAL=0XFFFF;
                }
                else 
                {
                    TIM5CH1_CAPTURE_STA++;
                }                        
            }	 
        }
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
        {	
            if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
            {	  			
                TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
                TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
            }
            else  								//��δ��ʼ,��һ�β���������
            {
                TIM5CH1_CAPTURE_STA=0;			//���
                TIM5CH1_CAPTURE_VAL=0;
                TIM_SetCounter(TIM5,0);
                TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
                TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
            }		    
        }			     	    					   
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
 
}
*/
