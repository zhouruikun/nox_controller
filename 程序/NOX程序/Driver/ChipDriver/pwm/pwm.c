#include "pwm.h"
#include "gpio.h"

/**************************************************************************************
* 名    称:    DK_TIM1_PWM(unsigned int prescaler,unsigned int period,unsigned int CCR_Val)
* 功    能:    PWM输出初始化程序：输出频率=系统时钟/prescaler/period,占空比=CCR_Val/period
* 参    数:    prescaler->预分频，period->周期，CCR_Val->占空比
* 返 回 值:    无
* 作    者：   D&K
**************************************************************************************/ 
void DK_TIM_PWM(unsigned char TIMERx, unsigned int period,unsigned int prescaler,unsigned int CCR_Val,unsigned char channel)
{ 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  //时间计数结构体
    TIM_OCInitTypeDef  TIM_OCInitStructure;  //定时器初始化结构体

    switch(TIMERx)
    {
        case 1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		 //使能定时器时钟   
                /* Time Base configuration */
            TIM_TimeBaseStructure.TIM_Prescaler = prescaler;      //TIM1时钟频率的预分频值=系统时钟/prescaler
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
            TIM_TimeBaseStructure.TIM_Period = period-1;      //自动重载寄存器周期值
            TIM_TimeBaseStructure.TIM_ClockDivision = 0;      //时钟分割值
            TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //初始化TIM1的时间计数数据
            //PWM Mode configuration: Channel1     
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
            switch(channel)
            {
                case 1:
                    
                    //PWM2模式，在向上计数时，当TIM1_CNT<TIM1_CRR时，通道为无效电平，否则为有效电平。若PWM1，相反
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //正向输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //占空比设置  占空比=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //输出极性
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC1Init(TIM1, &TIM_OCInitStructure);   //设置通道一
                    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
                    
                break;
                case 2:
                    //PWM Mode configuration: Channel2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //正向输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //占空比设置  占空比=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //输出极性
                    TIM_OC2Init(TIM1, &TIM_OCInitStructure);   //设置通道二
                    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器

                break;
                case 3:
                    //PWM Mode configuration: Channel3
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //正向输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //占空比设置  占空比=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //输出极性
                    TIM_OC3Init(TIM1, &TIM_OCInitStructure);   //设置通道三
                    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
                break;
                case 4:
                    //PWM Mode configuration: Channel4
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //正向输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;                    //占空比设置  占空比=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //输出极性
                    TIM_OC4Init(TIM1, &TIM_OCInitStructure);   //设置通道四
                    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
                break;
            }
            TIM_ARRPreloadConfig(TIM1, ENABLE);////使能TIMx在ARR上的预装载寄存器
            /* TIM1 Main Output Enable */
            TIM_CtrlPWMOutputs(TIM1, ENABLE); //定时器1PWM输出使能
            /* TIM1 counter enable */
            TIM_Cmd(TIM1, ENABLE);        //定时器1使能
        break;
        case 2:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		 //使能定时器时钟       
            TIM_TimeBaseStructure.TIM_Period = period-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //设置用来作为TIMx时钟频率除数的预分频值  不分频
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
            TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
             switch(channel)
             {
                 case 1:
                    //PWM Mode configuration: Channel1 
                    
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                 break;
                 case 2:
                    // PWM1 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //使能通道2
                    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
                 break;
                 case 3:
                    //PWM1 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //使能通道3
                    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
                 break;
                 case 4:
                    //PWM1 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//使能通道4
                    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
                 break;
             }

            TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器
            TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
        break;
        case 3:
            
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		 //使能定时器时钟       
            TIM_TimeBaseStructure.TIM_Period = period-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //设置用来作为TIMx时钟频率除数的预分频值  不分频
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
            TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
             switch(channel)
             {
                 case 1:
                    //PWM Mode configuration: Channel1 
                    
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                 break;
                 case 2:
                    // PWM1 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //使能通道2
                    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
                 break;
                 case 3:
                    //PWM1 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3
                    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
                 break;
                 case 4:
                    //PWM1 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//使能通道4
                    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
                 break;
             }

            TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
            TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
        break;
        case 4:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);		 //使能定时器时钟   
            TIM_TimeBaseStructure.TIM_Period = period-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //设置用来作为TIMx时钟频率除数的预分频值  不分频
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
            TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

            //PWM0 Mode configuration: Channel1 
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            switch(channel)
            {
                case 1:
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 2:
                //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 3:
                //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 4:
                //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
            }
                    
            
            TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
            TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设
        break;
        case 5:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);		 //使能定时器时钟   
            TIM_TimeBaseStructure.TIM_Period = period-1; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
            TIM_TimeBaseStructure.TIM_Prescaler =prescaler; //设置用来作为TIMx时钟频率除数的预分频值  不分频
            TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
            //TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
            TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

            //PWM0 Mode configuration: Channel1 
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            switch(channel)
            {
                case 1:
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 2:
                //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 3:
                //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 4:
                //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
            }
                    
            
            TIM_ARRPreloadConfig(TIM5, ENABLE); //使能TIMx在ARR上的预装载寄存器
            TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设
        break;
    }
            

}
/**************************************************************************************
* 名    称:    DK_TIM1_PWM_Reload(unsigned int CCR_Val)
* 功    能:    重载PWM占空比
* 参    数:    CCR_Val
* 返 回 值:    无
* 作    者：   D&K
**************************************************************************************/ 
void DK_TIM_PWM_Reload(unsigned char TIMERx,unsigned int CCR_Val,unsigned char channel )
{ 
    TIM_OCInitTypeDef  TIM_OCInitStructure; //结构体
    switch(TIMERx)
    {
        case 1:
            switch(channel)
            {
                case 1:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWM模式2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//正向通道有效  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //占空时间  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //数初始化外设TIMx通道 1
                break;
                case 2:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWM模式2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//正向通道有效  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //占空时间  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //数初始化外设TIMx通道 2
                break;
                case 3:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWM模式2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//正向通道有效  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //占空时间  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //数初始化外设TIMx通道 3
                break;
                case 4:
                /* Channel 1, 2,3 and 4 Configuration in PWM mode */
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //PWM模式2
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//正向通道有效  PA8 
                    TIM_OCInitStructure.TIM_Pulse =CCR_Val;     //占空时间  
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性 
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //数初始化外设TIMx通道 4
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
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 2:
                    ///PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 3:
                ///PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 4:
                ///PWM0 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
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
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 2:
                    ///PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 3:
                ///PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 4:
                ///PWM0 Mode configuration: Channel4 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
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
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 2:
                //PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 3:
                //PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 4:
                //PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
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
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 2:
                //PWM0 Mode configuration: Channel2 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 3:
                //PWM0 Mode configuration: Channel3 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                case 4:
                //PWM0 Mode configuration: Channel1 
                    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
                    //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
                    //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
                    TIM_OCInitStructure.TIM_Pulse = CCR_Val; //设置待装入捕获比较寄存器的脉冲值(输出一个占空比的PWM)
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
                    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
                    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
                break;
                default:
                
                break;
            }     
        break;
    }
}
void DK_TIM1_PWM_Init(void)
{
    
    DK_GPIO_Init(PA,GPIO_Pin_8,AF_PP);//初始化输出PWM的IO PA8
    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer4完全重映射 
    DK_TIM_PWM(timer1,Valve_period,72,0,1); //第几个定时器,周期500us，预分频 72，占空比 0 通道1
    
    //DK_GPIO_Init(PD,GPIO_Pin_12,AF_PP);//初始化输出PWM的IO PA8
    //GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //Timer4完全重映射 
    //DK_TIM_PWM(timer4,Valve_period,72,0,1); //第几个定时器,周期580us，预分频 72，占空比 0 通道1
}


void DK_TIM3_PWM_Init(void)
{
    
    DK_GPIO_Init(PA,GPIO_Pin_6 | GPIO_Pin_7 ,AF_PP);//初始化输出PWM的IO PA8
    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer4完全重映射 
    DK_TIM_PWM(timer3,Gripper1_period,72,0,1); //第几个定时器,周期520us，预分频 72，占空比 0  通道1
    DK_TIM_PWM(timer3,Gripper2_period,72,0,2); //第几个定时器,周期520ms，预分频 72，占空比 0  通道2
}
void Output_compare1_enable(uint8 channel,uint8 y_n)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure; //结构体
    switch(channel)
    {
        case 1:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
            //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //比较输出使能关
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能关
            }
            TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        break;
        case 2:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
            //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //比较输出使能关
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能关
            }
            TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        break;
        case 3:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
            //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //比较输出使能关
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能关
            }
            TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        break;
        default:
        case 4:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
            //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //比较输出使能关
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能关
            }
            TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        break;
        
    }
            
}


void Output_compare3_enable(uint8 channel,uint8 y_n)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure; //结构体
    switch(channel)
    {
        case 1:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
            //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //比较输出使能关
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能关
            }
            TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        break;
        case 2:
            TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
            //选择定时器输出比较为PWM模式2。在向上计数时，当 TIM1_CNT<TIM1_CRR1时，通道1为无效电平，否则为有效电平；
            //在向下计数时，当TIM1_CNT>TIM1_CRR1时，通道1为有效电平，否则为无效电平。如果选择PWM模式1，则相反。
            if(y_n==0)
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //比较输出使能关
            }
            else
            {
               TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能关
            }
            TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
        break;
        default:
        
        break;
    }
          
}
