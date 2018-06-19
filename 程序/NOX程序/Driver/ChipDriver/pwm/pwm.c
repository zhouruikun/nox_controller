#include "pwm.h"
#include "gpio.h"

/**************************************************************************************
* ��    ��:    DK_TIM1_PWM(unsigned int prescaler,unsigned int period,unsigned int CCR_Val)
* ��    ��:    PWM�����ʼ���������Ƶ��=ϵͳʱ��/prescaler/period,ռ�ձ�=CCR_Val/period
* ��    ��:    prescaler->Ԥ��Ƶ��period->���ڣ�CCR_Val->ռ�ձ�
* �� �� ֵ:    ��
* ��    �ߣ�   D&K
**************************************************************************************/ 
void DK_TIM_PWM(unsigned char TIMERx, unsigned int period,unsigned int prescaler,unsigned int CCR_Val,unsigned char channel)
{ 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  //ʱ������ṹ��
    TIM_OCInitTypeDef  TIM_OCInitStructure;  //��ʱ����ʼ���ṹ��

    switch(TIMERx)
    {
        case 1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��   
                /* Time Base configuration */
            TIM_TimeBaseStructure.TIM_Prescaler = prescaler;      //TIM1ʱ��Ƶ�ʵ�Ԥ��Ƶֵ=ϵͳʱ��/prescaler
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
            TIM_TimeBaseStructure.TIM_Period = period-1;      //�Զ����ؼĴ�������ֵ
            TIM_TimeBaseStructure.TIM_ClockDivision = 0;      //ʱ�ӷָ�ֵ
            TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //��ʼ��TIM1��ʱ���������
            //PWM Mode configuration: Channel1     
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
            switch(channel)
            {
                case 1:
                    
                    //PWM2ģʽ�������ϼ���ʱ����TIM1_CNT<TIM1_CRRʱ��ͨ��Ϊ��Ч��ƽ������Ϊ��Ч��ƽ����PWM1���෴
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�������ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //ռ�ձ�����  ռ�ձ�=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�������
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC1Init(TIM1, &TIM_OCInitStructure);   //����ͨ��һ
                    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
                    
                break;
                case 2:
                    //PWM Mode configuration: Channel2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�������ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //ռ�ձ�����  ռ�ձ�=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�������
                    TIM_OC2Init(TIM1, &TIM_OCInitStructure);   //����ͨ����
                    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���

                break;
                case 3:
                    //PWM Mode configuration: Channel3
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�������ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //ռ�ձ�����  ռ�ձ�=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�������
                    TIM_OC3Init(TIM1, &TIM_OCInitStructure);   //����ͨ����
                    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                    //PWM Mode configuration: Channel4
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�������ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //ռ�ձ�����  ռ�ձ�=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�������
                    TIM_OC4Init(TIM1, &TIM_OCInitStructure);   //����ͨ����
                    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
                break;
            }
            TIM_ARRPreloadConfig(TIM1, ENABLE);////ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
            /* TIM1 Main Output Enable */
            TIM_CtrlPWMOutputs(TIM1, ENABLE); //��ʱ��1PWM���ʹ��
            /* TIM1 counter enable */
            TIM_Cmd(TIM1, ENABLE);        //��ʱ��1ʹ��
        break;
        case 2:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��       
            TIM_TimeBaseStructure.TIM_Period = period-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
            TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
             switch(channel)
             {
                 case 1:
                    //PWM Mode configuration: Channel1 
                    
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                 break;
                 case 2:
                    // PWM1 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //ʹ��ͨ��2
                    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
                 break;
                 case 3:
                    //PWM1 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��3
                    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
                 break;
                 case 4:
                    //PWM1 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//ʹ��ͨ��4
                    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
                 break;
             }

            TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
            TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
        break;
        case 3:
            
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��       
            TIM_TimeBaseStructure.TIM_Period = period-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
            TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
             switch(channel)
             {
                 case 1:
                    //PWM Mode configuration: Channel1 
                    
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                 break;
                 case 2:
                    // PWM1 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //ʹ��ͨ��2
                    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
                 break;
                 case 3:
                    //PWM1 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��3
                    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
                 break;
                 case 4:
                    //PWM1 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��4
                    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
                 break;
             }

            TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
            TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
        break;
        case 4:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��   
            TIM_TimeBaseStructure.TIM_Period = period-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
            TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

            //PWM0 Mode configuration: Channel1 
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            switch(channel)
            {
                case 1:
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 2:
                //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 3:
                //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
            }
                    
            
            TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
            TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx����
        break;
        case 5:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��   
            TIM_TimeBaseStructure.TIM_Period = period-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
            TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

            //PWM0 Mode configuration: Channel1 
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            switch(channel)
            {
                case 1:
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 2:
                //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 3:
                //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
            }
                    
            
            TIM_ARRPreloadConfig(TIM5, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
            TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����
        break;
    }
            

}
/**************************************************************************************
* ��    ��:    DK_TIM1_PWM_Reload(unsigned int CCR_Val)
* ��    ��:    ����PWMռ�ձ�
* ��    ��:    CCR_Val
* �� �� ֵ:    ��
* ��    �ߣ�   D&K
**************************************************************************************/ 
void DK_TIM_PWM_Reload(unsigned char TIMERx,unsigned int CCR_Val,unsigned char channel )
{ 
    TIM_OCInitTypeDef  TIM_OCInitStructure; //�ṹ��
    switch(TIMERx)
    {
        case 1:
            switch(channel)
            {
                case 1:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWMģʽ2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//����ͨ����Ч  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //ռ��ʱ��  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������� 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����ʼ������TIMxͨ�� 1
                break;
                case 2:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWMģʽ2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//����ͨ����Ч  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //ռ��ʱ��  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������� 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����ʼ������TIMxͨ�� 2
                break;
                case 3:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWMģʽ2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//����ͨ����Ч  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //ռ��ʱ��  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������� 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����ʼ������TIMxͨ�� 3
                break;
                case 4:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWMģʽ2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//����ͨ����Ч  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //ռ��ʱ��  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //������� 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����ʼ������TIMxͨ�� 4
                break;
                default:
                break;
            }
            
        break;
        case 2:
           switch(channel)
            {
                case 1:
                    ///PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 2:
                    ///PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 3:
                ///PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                ///PWM0 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                default:
                
                break;
                
            }
        break;
        case 3:
            switch(channel)
            {
                case 1:
                    ///PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 2:
                    ///PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 3:
                ///PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                ///PWM0 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                default:
                
                break;
                
            }
                
            
            
        break;
        case 4:
            switch(channel)
            {
                case 1:
                    //PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 2:
                //PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 3:
                //PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                //PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                default:
                
                break;
            }     
        break;
        case 5:
            switch(channel)
            {
                case 1:
                    //PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 2:
                //PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 3:
                //PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                case 4:
                //PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
                    //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
                    //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //���ô�װ�벶��ȽϼĴ���������ֵ(���һ��ռ�ձȵ�PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
                    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
                    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
                break;
                default:
                
                break;
            }     
        break;
    }
}
void DK_TIM1_PWM_Init(void)
{
    
    DK_GPIO_Init(PA,GPIO_Pin_8,AF_PP);//��ʼ�����PWM��IO PA8
    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer4��ȫ��ӳ�� 
    DK_TIM_PWM(timer1,Valve_period,72,0,1); //�ڼ�����ʱ��,����500us��Ԥ��Ƶ 72��ռ�ձ� 0 ͨ��1
    
    //DK_GPIO_Init(PD,GPIO_Pin_12,AF_PP);//��ʼ�����PWM��IO PA8
    //GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //Timer4��ȫ��ӳ�� 
    //DK_TIM_PWM(timer4,Valve_period,72,0,1); //�ڼ�����ʱ��,����580us��Ԥ��Ƶ 72��ռ�ձ� 0 ͨ��1
}


void DK_TIM3_PWM_Init(void)
{
    
    DK_GPIO_Init(PA,GPIO_Pin_6 | GPIO_Pin_7 ,AF_PP);//��ʼ�����PWM��IO PA8
    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer4��ȫ��ӳ�� 
    DK_TIM_PWM(timer3,Gripper1_period,72,0,1); //�ڼ�����ʱ��,����520us��Ԥ��Ƶ 72��ռ�ձ� 0  ͨ��1
    DK_TIM_PWM(timer3,Gripper2_period,72,0,2); //�ڼ�����ʱ��,����520ms��Ԥ��Ƶ 72��ռ�ձ� 0  ͨ��2
}
void Output_compare1_enable(uint8 channel,uint8 y_n)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure; //�ṹ��
    switch(channel)
    {
        case 1:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
            //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܹ�
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ�ܹ�
            }
            TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        break;
        case 2:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
            //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܹ�
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ�ܹ�
            }
            TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        break;
        case 3:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
            //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܹ�
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ�ܹ�
            }
            TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        break;
        default:
        case 4:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
            //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܹ�
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ�ܹ�
            }
            TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        break;
        
    }
            
}


void Output_compare3_enable(uint8 channel,uint8 y_n)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure; //�ṹ��
    switch(channel)
    {
        case 1:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
            //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܹ�
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ�ܹ�
            }
            TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        break;
        case 2:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
            //ѡ��ʱ������Ƚ�ΪPWMģʽ2�������ϼ���ʱ���� TIM1_CNT<TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ��
            //�����¼���ʱ����TIM1_CNT>TIM1_CRR1ʱ��ͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ�����ѡ��PWMģʽ1�����෴��
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ�ܹ�
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ�ܹ�
            }
            TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
        break;
        default:
        
        break;
    }
          
}
