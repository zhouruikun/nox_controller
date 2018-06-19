#ifndef __ADC_H
#define __ADC_H

#define DK_DMA1   1
#define DK_DMA2   2
#define DK_ADC1   1
#define DK_ADC2   2
#define DK_ADC3   3

#define ADC1_DR_Address    ((u32)0x4001244C)
#define ADC2_DR_Address    ((u32)0x4001284C)
#define ADC3_DR_Address    ((u32)0x40013C4C)

#ifdef   ADC_globals
#define  ADC_ext
#else
#define  ADC_ext  extern
#endif

#define  N  1        //ÿͨ����50�� 
#define  M  7       //Ϊ1��ͨ�� 
 
//ADC_ext u16  AD_Value[N][M];   //�������ADCת�������Ҳ��DMA��Ŀ���ַ
ADC_ext  float AD_Value,ada;
ADC_ext u16 ADCbuf[N][M],AD_val[M],AD_val1[M],bval;
ADC_ext u16 ADC_InjectedConvertedValueTab[3];
ADC_ext u32 adval,Pressure_val;
//          ad������������AD�Ĳ���ֵ
//ADC_ext u16 ref;
float Get_InsideTemperature(void);
void ADC_With_DMA_Init(void); 
	//��������޸�ͨ����  
u16 get_adc_val(void); 
void    ADC_ContinuousCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_10us(u16 *inbuf,u8 ubit);
#endif
