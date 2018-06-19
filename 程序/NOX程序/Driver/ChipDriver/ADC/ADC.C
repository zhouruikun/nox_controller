#define ADC_globals
#include "stm32f10x_adc.h"
#include "datatype.h"
#include "stm32f10x_dma.h"
#include "ADC.H"	
#include "gpio.h"
#include "timer.h"
#include "para.h"
__IO unsigned short ADC_ConvertedValue; 

/********************************************************************
*函数描述:
*函数功能：
***********************************************************************/
void DK_DMA_ADC_Init(unsigned char DMAx,unsigned char ADCx,unsigned short size,DMA_Channel_TypeDef *DMAx_Channelx)
{	  			 
	DMA_InitTypeDef   DMA_InitStructure;

	DMA_DeInit(DMAx_Channelx);//开启DMA1的第一通道
	if(DMAx==1)
	{	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	 //时钟使能
	}
	else if(2==DMAx)
	{
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);	 //时钟使能
	}
	if(ADCx==1)
 		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	//DMA对应的外设基地址，
	if(ADCx==2)
		DMA_InitStructure.DMA_PeripheralBaseAddr = ADC2_DR_Address;//DMA对应的外设基地址，


	   /* DMA1 channel1 configuration ----------------------------------------------*/
	  DMA_DeInit(DMA1_Channel1);
	  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCbuf;
	  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	  DMA_InitStructure.DMA_BufferSize = size;            
	  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	  
	  /* Enable DMA1 channel1 */
	  DMA_Cmd(DMA1_Channel1, ENABLE);
	  
}
/**
  * @brief  Configures NVIC and Vector Table base location.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure and enable ADC interrupt */
#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
#else
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
#endif
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/********************************************************************
*函数描述:
*函数功能：
***********************************************************************/
void DK_ADC_Init(ADC_TypeDef *ADCx,unsigned char ChannelSize)
{	
	ADC_InitTypeDef   ADC_InitStructure;
	u32 Retry=0;

	if(ADCx==ADC1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	}
	if(ADCx==ADC2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	}
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	  /* ADC1 configuration ------------------------------------------------------*/
	  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	        ADC_InitStructure.ADC_NbrOfChannel = ChannelSize;
	  ADC_Init(ADC1, &ADC_InitStructure);
   //ADC_TempSensorVrefintCmd(ENABLE); //ADC内置温度传感器使能（要使用片内温度传感器，要开启它） 
	//规则组通道设置，关键函数 转换器ADC1，选择哪个通道channel，规则采样顺序，
		//1到16，最后一个参数是转换时间，越长越准越稳定
	/*************************************************************************************/

 
	ADC_RegularChannelConfig(ADCx, ADC_Channel_3,1, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改
	ADC_RegularChannelConfig(ADCx, ADC_Channel_4,2, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改
	ADC_RegularChannelConfig(ADCx, ADC_Channel_5,3, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改
	ADC_RegularChannelConfig(ADCx, ADC_Channel_6,4, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改
	ADC_RegularChannelConfig(ADCx, ADC_Channel_0,6, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改
	ADC_RegularChannelConfig(ADCx, ADC_Channel_1,7, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改
	ADC_RegularChannelConfig(ADCx, ADC_Channel_2,5, ADC_SampleTime_28Cycles5);  //这里要根据实际情况修改

 
        // ADC1 to DMA, Enable
    ADC_DMACmd(ADCx, ENABLE); //ADC命令，和DMA关联。
        //ADC1 Enable
    ADC_Cmd(ADCx,ENABLE); //开启ADC1
        //Reset the Calibration of ADC1
    ADC_ResetCalibration(ADCx);  //重置校准
	Retry=0;
    while((ADC_GetResetCalibrationStatus(ADCx))&&(Retry<0xfff0))  //等待重置校准完成     
	{
		Retry++;
	}  
    ADC_StartCalibration(ADCx);  //开始校准
	Retry=0;
    while((ADC_GetCalibrationStatus(ADCx))&&(Retry<0xfff0))  //等待校准完成
	{
		Retry++;
	}
    ADC_SoftwareStartConvCmd(ADCx, ENABLE);  //连续转换开始，从选择开始，MCU可以不用管了，ADC将通过DMA不断刷新制定RAM区
		//ADC_ContinuousCmd(ADC1, ENABLE);
	NVIC_Configuration();
}

/********************************************************************
*函数描述:
*函数功能：
***********************************************************************/
void ADC_With_DMA_Init(void)
{	  
    DK_GPIO_Init(PA,GPIO_Pin_0,AIN);//模拟输入引脚 PA1
	  DK_GPIO_Init(PA,GPIO_Pin_1,AIN);//模拟输入引脚 PA1
    DK_GPIO_Init(PA,GPIO_Pin_2,AIN);//模拟输入引脚 PA1
	  DK_GPIO_Init(PA,GPIO_Pin_3,AIN);//模拟输入引脚 PA1
    DK_GPIO_Init(PA,GPIO_Pin_4,AIN);//模拟输入引脚 PA1
	  DK_GPIO_Init(PA,GPIO_Pin_5,AIN);//模拟输入引脚 PA1
    DK_GPIO_Init(PA,GPIO_Pin_6,AIN);//模拟输入引脚 PA1

	DK_ADC_Init(ADC1,M);	  //AD转换
	DK_DMA_ADC_Init(DK_DMA1,DK_ADC1,N*M,DMA1_Channel1);   	//AD转换DMA通道

}
void ADC_Delay(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
		for(j=0;j<1000;j++);
}

u16 get_adc_val(void)
{
    u16 temp;
    ADC_Delay(10);
    temp=ADC_ConvertedValue;
    return temp;
}

/********************************************************************
*函数描述:
*函数功能： 
***********************************************************************/
//
float Get_InsideTemperature(void)
{
	unsigned short result=0,temp[16];
	float Temperature;
	unsigned char i,j;
    
	for(i=16;i>0;i--)
	{
	  ADC_Delay(10); 
        
            
            temp[i]= ADC_ConvertedValue;
                   
		
	}
	for(i=0;i<16;i++)   //从小到大排序
	{
		for(j=i+1;j<16;j++)
		{
			if(temp[i]>temp[j])
			{
				result=temp[i];
				temp[i]=temp[j];
				temp[j]=result;
			}
		}
	}
	result=0;
	for(i=5;i<10;i++)
		result+=temp[i];
	result=result/5;
	Temperature= (1.42 - result*3.3/4096)*1000/4.35 + 25;

	return Temperature;
}


void    ADC_ContinuousCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE) {
        /* Enable the selected ADC CONT */
        ADCx->CR2 |= (1 << 1);
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    } else {
        /* Disable the selected ADC CONT */
        ADCx->CR2 &=~(1 << 1);
        ADC_SoftwareStartConvCmd(ADC1, DISABLE);
    }
}

