/**
******************************************************************************
* @file    USART/DMA_Interrupt/main.c 
* @author  MCD Application Team
* @version V3.5.0
* @date    08-April-2011
* @brief   Main program body
******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "stm32f10x.h"
#include "datatype.h"
#include "NVIC.H"
#include "systick.h"
#include "delay.h"
#include "exti.h"
#include "comm.h"
#include "timer.h"
#include "timerApi.h"
#include "Gripper_Valve.h"
#include "StructUsartBuf.h"
#include "ADC.h"
#include "DAC.h"
#include "Calculate_val.h"
#include "para.h"
#include "smbus.h"
 #include "PID.H"
#include "gpio.h"
#include "CAN.h"
#define STATUS_IDLE 0
#define STATUS_INIT 1
#define STATUS_HEATING 2
#define STATUS_RUN 3
#define STATUS_ERR 4

#define G_O2 51 
#define G_NOX 51 

#define G_REF 6 
#define R_O2 10
#define R_NOX 2000

 #define R_AUX 2000
 #define G_AUX 51 
u8 Staus_Machine =STATUS_IDLE;
u16 Ref_R_PT = 10000;
 u16 auxt=50;
 u8 flag=0;
 int refTOaux=0;
 int refTOaux_ratio=0;
int PumpNox=570;
int PumpAux=560;
int PumpREF=3000;
int pin_DA_REF=0;
int pin_DA_O2=0;


int offset_I_REF=0;
 
 int sum_adc[7];
 int I_pump[7];
 u8 counter=0;
 u8 RT_Flag=0;
  u8 counter_RT=0;
	u8 proid = 80;
	short pump_o24=0;
	void sensorDiagnose(void );
int main(void)
{ 
 
		SysTick_Init();//�δ��ʼ��  
		ADC_With_DMA_Init();//ADC��DMA��ʼ��
		Init_TIM1();
		INIT_MCP4822();
		UsartCommInit();//���ڳ�ʼ��
		CAN1_Com_init();
		Init_PID_Arg();
		Arg_all.PWM=0;
		StartTimer(TIMERAUX,auxt);
		StartTimer(TIMERUART,100);
		StartTimer(TIMER_REF,5);
    while (1)
    { 
			
 
			switch(Staus_Machine)
			{
				case STATUS_IDLE:
							 		Arg_all.I_PumpO2=0;/////UA
									Arg_all.I_PumpNox=0;////10nA
								 	Arg_all.PumpRef=1800;
									Arg_all.I_PumpAux=0;///10nA
									Arg_all.PumpO2=1800;
									Arg_all.NOX_PPM=0;
									Arg_all.O2PP=0;
								if(Arg_all.Temperture<Arg_all.auto_adj_th)
								{
												
								  Arg_all.offset_I_NOX=Arg_all.offset_I_NOX*0.9+ (I_pump[3]*0.80566)*0.1;
								  Arg_all.offset_I_O2=Arg_all.offset_I_O2*0.9+ (I_pump[0]*0.80566)*0.1;
								  Arg_all.offset_I_AUX=Arg_all.offset_I_AUX*0.9+(I_pump[1]*0.80566)*0.1;		  
								}

							
				
									MCP4822_WriteValue(MCP4822_CH_A,MCP4822_GATE_ON,MCP4822_SHDN_OFF,0 );
								  MCP4822_WriteValue(MCP4822_CH_B,MCP4822_GATE_ON,MCP4822_SHDN_OFF,0 );
									MCP4822_WriteValue(MCP4822_CH_C,MCP4822_GATE_ON,MCP4822_SHDN_OFF,1800 );
								  MCP4822_WriteValue(MCP4822_CH_D,MCP4822_GATE_ON,MCP4822_SHDN_OFF,0 );
									Arg_all.PWM=0;
									TIM_SetCompare1(TIM1,  Arg_all.PWM);
				         // TIM_Cmd(TIM1, DISABLE);         
									//TIM_Cmd(TIM2, DISABLE);        
					break;
				case STATUS_INIT:
					 
							Staus_Machine=STATUS_HEATING;
							TIM_Cmd(TIM1, ENABLE);        //��ʱ��1ʹ��
							TIM_Cmd(TIM2, ENABLE);        //��ʱ��1ʹ��
							StartTimer(TIMERDELAY,160);
						Save_PID_Arg();
	 
					break;
				case STATUS_HEATING:
					
							if(ReadTimer(TIMERDELAY)==OK)
							{ sensorDiagnose();
 
								
								StartTimer(TIMERDELAY,60);
								 TIM_SetCompare1(TIM1,  Arg_all.PWM);
								Arg_all.PWM+=3;
								if(Arg_all.PWM>500)
								{
									Staus_Machine=STATUS_RUN;
									PBout(3)=0;
									PBout(7)=0;
								}
							}
					break;
				case STATUS_RUN:
					sensorDiagnose();
								if(ReadTimer(TIMER_REF)==OK)
								{
										StartTimer(TIMER_REF,proid);
										Arg_all.PWM= PID_Heater(Arg_all.Temperture);
								if((Arg_all.PID_flag&PID_AUX_flag)==PID_AUX_flag)	 
									 pump_o24=PID_AUX(Arg_all.I_PumpAux);
									MCP4822_WriteValue(MCP4822_CH_D,MCP4822_GATE_ON,MCP4822_SHDN_OFF,pump_o24 );//Arg_all.PumpO2 );		
									Arg_all.Ref_VPO2_Set=pump_o24/4;
									}else
								
									{
										MCP4822_WriteValue(MCP4822_CH_D,MCP4822_GATE_ON,MCP4822_SHDN_OFF,Arg_all.Ref_VPO2_Set*4);//Arg_all.PumpO2 );		
								}
								
								Arg_all.Ref_VPO2_Set=pump_o24/4;
								 TIM_SetCompare1(TIM1,   Arg_all.PWM);
								 MCP4822_WriteValue(MCP4822_CH_A,MCP4822_GATE_ON,MCP4822_SHDN_OFF, Arg_all.Ref_VPNO2_Set*4 );
								 MCP4822_WriteValue(MCP4822_CH_B,MCP4822_GATE_ON,MCP4822_SHDN_OFF, Arg_all.Ref_VPAUX_Set*4 );
							//	 MCP4822_WriteValue(MCP4822_CH_C,MCP4822_GATE_ON,MCP4822_SHDN_OFF, Arg_all.PumpRef);
								
				
				
				
								
					break;
				case STATUS_ERR:
							Staus_Machine=STATUS_IDLE;
					break;
				default:break;
				
			}
			if(ReadTimer(TIMERUART)==OK)
				{
					StartTimer(TIMERUART,100);
					if(Staus_Machine!=STATUS_IDLE)
					{
						CAN1_Tx_data();
						
					}Send_TFT();
				}					 
        Usart_ReceiveAndSend();//�ȴ�����ͨ��
 
				 
    }
}
void sensorDiagnose(void )
{
//	//���������������
//	if((AD_val[6]-AD_val[4])<200)//��������·
//	{
//		Arg_all.err_code=1;
//		Staus_Machine=STATUS_ERR;
//		
//	}
//else if(((AD_val[4]-AD_val[5])<100))//��������·
//	{
//		Arg_all.err_code=2;
//		Staus_Machine=STATUS_ERR;
//	}	
//	
}
	
	
double iTempTable[4]={0};
void cal_current_rpt(void)
{

				Arg_all.Temperture=Arg_all.Temperture*0.9+(((AD_val[4]-AD_val[5]-AD_val[5])*Ref_R_PT)/\
				(AD_val[6]-AD_val[5]-AD_val[4]))*0.1;
	
	
				if(Arg_all.Temperture<0)
				{
					Arg_all.Temperture=0;
				}
					
				iTempTable[0]=iTempTable[0]*0.9+((I_pump[0]*0.80566-Arg_all.offset_I_O2)*1000/G_O2/R_O2)*0.1;/////UA
				Arg_all.I_PumpO2=iTempTable[0];
		
				
				iTempTable[3]=iTempTable[3]*0.9+ ((I_pump[3]*0.80566-Arg_all.offset_I_NOX)*100000/G_NOX/R_NOX)*0.1 ;////10nA	
				Arg_all.I_PumpNox=iTempTable[3];
				iTempTable[1]=iTempTable[1]*0.9	+((I_pump[1]*0.80566-Arg_all.offset_I_AUX)*100000/G_AUX/R_AUX)*0.1;///10nA			
				Arg_all.I_PumpAux=iTempTable[1];
				
				
				Arg_all.PumpRef= Arg_all.PumpRef*0.9+ (I_pump[2]*0.80566)*0.1;
				
				
				Arg_all.PumpO2=Arg_all.PumpRef-Arg_all.Ref_VPO2_Set;
				Arg_all.NOX_PPM=Arg_all.I_PumpNox*Arg_all.NOX_ratio/1000.0;
				Arg_all.O2PP=Arg_all.I_PumpO2*Arg_all.O2_ratio/1000.0;
}
void TIM2_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
				sum_adc[0]+=ADCbuf[0][0];
				sum_adc[1]+=ADCbuf[0][1];
				sum_adc[2]+=ADCbuf[0][2];
				sum_adc[3]+=ADCbuf[0][3];
					counter++;
		if(RT_Flag==1)
		
		{counter_RT++;
				sum_adc[4]+=ADCbuf[0][4];
				sum_adc[5]+=ADCbuf[0][5];
				sum_adc[6]+=ADCbuf[0][6];
		}
			//�ۼ�AD
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);    ;
	}		 	
}


 void Init_TIM1(void)
 {	     TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

	      TIM_OCInitTypeDef         TIM_OCInitStructure;
	      DK_GPIO_Init(  PA,GPIO_Pin_8,AF_PP);
				DK_GPIO_Init(  PB,GPIO_Pin_14,AF_PP);		DK_GPIO_Init(  PB,GPIO_Pin_15,AF_PP);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��   
	 	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		 //ʹ�ܶ�ʱ��ʱ��   
						TIM_TimeBaseStructure.TIM_Prescaler = 719;      //TIM1ʱ��Ƶ�ʵ�Ԥ��Ƶֵ=ϵͳʱ��/prescaler
            TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
            TIM_TimeBaseStructure.TIM_Period = 9;      //�Զ����ؼĴ�������ֵ
            TIM_TimeBaseStructure.TIM_ClockDivision = 0;      //ʱ�ӷָ�ֵ
            TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;   
	 
            TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  //��ʼ��TIM2 // ÿ100us��һ��ad����  ������
	              TIM_TimeBaseStructure.TIM_Period = 1000-1;      //�Զ����ؼĴ�������ֵ
	    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  //��ʼ��TIM2 // ÿ100us��һ��ad����  ������
   TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
            TIM2, //TIM2
            TIM_IT_Update,    //TIM �ж�Դ
            //TIM_IT_Trigger,   //TIM �����ж�Դ 
            ENABLE  //ʹ��
            );
            //PWM Mode configuration: Channel1     
										
	 
										TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 	 
	                     //PWM2ģʽ�������ϼ���ʱ����TIM1_CNT<TIM1_CRRʱ��ͨ��Ϊ��Ч��ƽ������Ϊ��Ч��ƽ����PWM1���෴
                    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�������ʹ��
										TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Enable;
										TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_Low;
										TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
                    TIM_OCInitStructure.TIM_Pulse = 0;                    //ռ�ձ�����  ռ�ձ�=CCR_Val/period
                    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;   //�������
                    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
                    TIM_OC1Init(TIM1, &TIM_OCInitStructure);   //����ͨ��һ
                    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
			 //ͨ��2���õ����������
			 	   /* TIM1 channel2 configuration in PWM mode */
				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputNState_Enable;                
				TIM_OCInitStructure.TIM_Pulse = 800; 
				TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;         
				TIM_OC2Init(TIM1, &TIM_OCInitStructure);											
		 //ͨ��3���òο��õ�������
	   /* TIM1 channel3 configuration in PWM mode */
				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputNState_Enable;                
				TIM_OCInitStructure.TIM_Pulse = 750; 
				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
				TIM_OC3Init(TIM1, &TIM_OCInitStructure);									
	 //ͨ��4����ADC����Դ
	   /* TIM1 channel4 configuration in PWM mode */
				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
				TIM_OCInitStructure.TIM_Pulse = 250; 
				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
				TIM_OC4Init(TIM1, &TIM_OCInitStructure);
        TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
            TIM1, //TIM2
            TIM_IT_CC2,    //TIM �ж�Դ
            //TIM_IT_Trigger,   //TIM �����ж�Դ 
            ENABLE  //ʹ��
            );
        TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
            TIM1, //TIM2
            TIM_IT_CC4,    //TIM �ж�Դ
            //TIM_IT_Trigger,   //TIM �����ж�Դ 
            ENABLE  //ʹ��
            );						
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
	  NVIC_InitStructure.NVIC_IRQChannel=TIM1_CC_IRQn;
	  NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	  NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
				
		
		        TIM_ARRPreloadConfig(TIM1, ENABLE);////ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
            /* TIM1 Main Output Enable */
            TIM_CtrlPWMOutputs(TIM1, ENABLE); //��ʱ��1PWM���ʹ��
            /* TIM1 counter enable */
            TIM_Cmd(TIM1, ENABLE);        //��ʱ��1ʹ��
						TIM_Cmd(TIM2, ENABLE);        //��ʱ��1ʹ��
 }
 void status_ON_OFF(u8 status)
 {
	 	if(status == 1)
	{
		 Staus_Machine=STATUS_INIT;
	}else
	{
			Staus_Machine=STATUS_IDLE;
				Arg_all.err_code=0;
	}
 }
void REF_I_ON_OFF(bool status)
{
	if(status == 1)
	{
		 MCP4822_WriteValue(MCP4822_CH_C,MCP4822_GATE_ON,MCP4822_SHDN_OFF, Arg_all.I_PumpRef/5+1800);
	}else
	{
		 MCP4822_WriteValue(MCP4822_CH_C,MCP4822_GATE_ON,MCP4822_SHDN_OFF, 1800);
	}
}
void INIT_MCP4822(void)
{
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	 DK_GPIO_Init(PB,0x00FF,Out_PP); 
 PBout(3)=1;
	PBout(7)=1;
}
 
#define uchar unsigned char
void MCP4822_WriteValue(u8 ch,bool gate,bool shdn,uint16 dat)		//ch[0:A,1:B],gate[0:gate,1:not gate],shdn[0:shdn,1:on],dat:0-0xfff;
{ 
	uchar i; 
	uchar dat_h=0;
	dat_h=(uchar) ch<<7;			//?16?
	dat_h|=(uchar) gate<<5;		//?14?
	dat_h|=(uchar) shdn<<4;		//?13?
	dat&=0x0fff;
	dat|=(uint16) dat_h<<8;
 if(ch<2)
 {
	MCP48221_CS=1;
	delay_us(1);
	MCP48221_CS = 0; 
	delay_us(1);
	MCP48221_SCK = 0;
	delay_us(1);
	
	for(i=16;i>0;i--) 
	{
		if(dat&0x8000)
			MCP48221_SI=1;
		else 
			MCP48221_SI=0;
			delay_us(1);
		dat <<= 1;
		MCP48221_SCK = 1;
		delay_us(1);
		MCP48221_SCK = 0;
			delay_us(1);
	}
	
	  MCP48221_CS = 1;
		delay_us(1);
}
 else if(ch<4)
 {
	 	MCP48222_CS=1;
	delay_us(1);
	MCP48222_CS = 0; 
	delay_us(1);
	MCP48222_SCK = 0;
	delay_us(1);
	
	for(i=16;i>0;i--) 
	{
		if(dat&0x8000)
			MCP48222_SI=1;
		else 
			MCP48222_SI=0;
			delay_us(1);
		dat <<= 1;
		MCP48222_SCK = 1;
		delay_us(1);
		MCP48222_SCK = 0;
			delay_us(1);
	}
	
	  MCP48222_CS = 1;
		delay_us(1);
 }
}
 

/*
????????:	
MCP4822_SPI_Write(MCP4822_CH_B,MCP4822_GATE_ON,MCP4822_SHDN_OFF,0xfff);
*/

/*----------------------------------------------------------------------------*/
/******************* (C) COPYRIGHT 2014 STMicroelectronics *****END OF FILE****/
