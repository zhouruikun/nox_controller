#define Calculate_val_globals
#include "stm32f10x.h"
#include "math.h"//数字
#include "datatype.h"
#include "Calculate_val.h"
#include "adc.h"
#include "usart.h"
#include "structusartbuf.h"
#include "para.h"
#include "AT24C02.h"
#include "mlx90614.h"
float filt_a=0.95;
s16 temper1=0;
	s16 tempERR=0;
/////////////////////////归一化输出参数


u16 tempDriftTable[100][2]={0};


//温敏电阻表
#define SACLE 121
#define MIN_t -20
#define R1 10 
float temp_tab[SACLE]=
{
	67.77,64.57,61.54,58.68,55.97,53.41,50.98,48.68,46.50,44.43,42.47,40.57,38.77,37.06,
	35.44,33.90,32.44,31.05,29.73,28.48,27.28,26.13,25.03,23.99,23.00,22.05,21.15,20.30,
	19.48,18.70,17.96,17.24,16.56,15.90,15.28,14.69,14.12,13.58,13.06,12.56,12.09,11.63,
	11.20,10.78,10.38,10.00,9.632,9.281,8.944,8.622,8.313,8.014,7.728,7.454,7.192,6.940,
	6.699,6.467,6.245,6.032,5.827,5.629,5.438,5.255,5.080,4.911,4.749,5.593,4.443,5.299,
	4.160,4.026,3.896,3.771,3.651,3.563,3.425,3.318,3.215,3.116,3.020,2.927,2.838,2.751,
	2.668,2.588,2.511,2.436,2.364,2.295,2.228,2.163,2.100,2.039,1.980,1.924,1.869,1.816,
	1.765,1.716,1.668,1.622,1.577,1.533,1.492,1.451,1.412,1.373,1.336,1.301,1.266,1.232,
	1.200,1.168,1.137,1.108,1.079,1.051,1.024,0.9984,0.9731
};
float Get_Temp(u16 ad_value,u16 vref)
{
	float V=0,R=0,eer=0;
	u8 index=0;
	V=(ad_value/4096.0)*vref;
	R=(R1*V)/(vref-V);
//查表插值
	for(index=0;index<SACLE;index++)
		{
			if(R>=temp_tab[index])
				break;
		}
	//插值
	eer=(temp_tab[index]-R)/(temp_tab[index]-temp_tab[index+1]);
	
	return (MIN_t+index+eer);

}
/************************************************************************************
**功    能:  测量算出数据并发送
**入口参数:  无
**出口参数:  无
************************************************************************************/
//Y=sqrt(X)

void MeasureAndSend(void)
{

 
//        AD_val[0]= Sequence_buff(&ADCbuf[0][0],samp_num,0);
//			  AD_val[1]= Sequence_buff(&ADCbuf[0][0],samp_num,1);
//			  AD_val[2]= Sequence_buff(&ADCbuf[0][0],samp_num,2);
//			  AD_val[3]= Sequence_buff(&ADCbuf[0][0],samp_num,3);
//			  AD_val[4]= Sequence_buff(&ADCbuf[0][0],samp_num,4);
//			  AD_val[5]= Sequence_buff(&ADCbuf[0][0],samp_num,5);
//			  AD_val[6]= Sequence_buff(&ADCbuf[0][0],samp_num,6);
         AD_val[0]=  ADCbuf[0][0];
			  AD_val[1]= ADCbuf[0][1];
			  AD_val[2]= ADCbuf[0][2];
			  AD_val[3]= ADCbuf[0][3];
			  AD_val[4]= ADCbuf[0][4];
			  AD_val[5]=ADCbuf[0][5];
			  AD_val[6]=ADCbuf[0][6];
 
//        AD_val1[0]=AD_val1[0]*filt_a+ (AD_val[0])*(1-filt_a);//采了N次算平均值
//			  AD_val1[1]=AD_val1[1]*filt_a+ (AD_val[1])*(1-filt_a);//采了N次算平均值
//				AD_val1[2]=AD_val1[2]*filt_a+ (AD_val[2])*(1-filt_a);//采了N次算平均值
//				AD_val1[3]=AD_val1[3]*filt_a+ (AD_val[3])*(1-filt_a);//采了N次算平均值
//				AD_val1[4]=AD_val1[4]*filt_a+ (AD_val[4])*(1-filt_a);//采了N次算平均值
//			  AD_val1[5]=AD_val1[5]*filt_a+ (AD_val[5])*(1-filt_a);//采了N次算平均值
//				AD_val1[6]=AD_val1[6]*filt_a+ (AD_val[6])*(1-filt_a);//采了N次算平均值
		 

}


/************************************************************************************
**功    能:  对测量出来的数据进行排序滤波
**入口参数:  u16 *buff,采样数据存放缓冲区   u8 ubit连续采样次数
**出口参数:  数字滤波结果
************************************************************************************/
u16 Sequence_buff(u16 *buff,u8 ubit,u8 chall)
{
    u16 result=0;
    u32 aa=0;
    u32 i,j;   
//    for(i=0;i<ubit;i++)   //从小到大排序
//    {
//        for(j=i+1;j<ubit;j++)
//        {
//            if(*(buff+i*M+chall)>*(buff+j*M+chall))
//            {
//                result=*(buff+i*M+chall);
//                *(buff+i*M+chall)=*(buff+j*M+chall);
//                *(buff+j*M+chall)=result;
//            }
//        }
//    }
    for(i=(0+chall);i<(700+chall);i+=7)
   // for(i=((ubit*2)-20+chall);i<((ubit*2)+20+chall);i+=4)
    {
        aa+=*(buff+i);
    }
    result=aa/100;
    return result;
    
}
/************************************************************** 
 函数说明：  把十六进制整数转换成ASCII码
 输入 shu
 输出 dptr->str1[]
 位数 wei  1-5位
**************************************************************/
#ifndef  Int_to_ascii
void Int_to_ascii(u8 *dptr,uint32 shu,uint8 wei)
{
	switch(wei)
	{
		case 1:
			    *(dptr+0)=shu%10+0x30;
		        *(dptr+1)=0;
			    break;
		case 2:
			    if(shu>99)
				{
					*(dptr+0)=shu%100/10+0x30;
				    *(dptr+1)=shu%100%10+0x30;
				}
				else
				{
					*(dptr+0)=shu/10+0x30;
				    *(dptr+0)=shu%10+0x30;
				}
				*(dptr+2)=0;
			    break;
		case 3:
			    if(shu>999)
				{
					*(dptr+0)=shu%1000/100+0x30;
					*(dptr+1)=shu%1000%100/10+0x30;
					*(dptr+2)=shu%1000%100%10+0x30;
				}
				else
				{
					*(dptr+0)=shu/100+0x30;
					*(dptr+1)=shu%100/10+0x30;
					*(dptr+2)=shu%100%10+0x30;
				}
				*(dptr+3)=0;
			    break;
		case 4:
			    if(shu>9999)
				{
					*(dptr+0)=shu%10000/1000+0x30;
					*(dptr+1)=shu%10000%1000/100+0x30;
					*(dptr+2)=shu%10000%1000%100/10+0x30;
					*(dptr+3)=shu%10000%1000%100%10+0x30;
				}
				else
				{
					*(dptr+0)=shu/1000+0x30;
					*(dptr+1)=shu%1000/100+0x30;
					*(dptr+2)=shu%1000%100/10+0x30;
					*(dptr+3)=shu%1000%100%10+0x30;
				}
				*(dptr+4)=0;
			    break;
       case 5:		
                if(shu>99999)	
                {

					*(dptr+0)=shu%100000/10000+0x30;
					*(dptr+1)=shu%100000%10000/1000+0x30;
					*(dptr+2)=shu%100000%10000%1000/100+0x30;
					*(dptr+3)=shu%100000%10000%1000%100/10+0x30;
					*(dptr+4)=shu%100000%10000%1000%100%10+0x30;
				}
				else
				{
					*(dptr+0)=shu/10000+0x30;
					*(dptr+1)=shu%10000/1000+0x30;
					*(dptr+2)=shu%10000%1000/100+0x30;
					*(dptr+3)=shu%10000%1000%100/10+0x30;
					*(dptr+4)=shu%10000%1000%100%10+0x30;
				}
				
				*(dptr+5)=0;
				break;	
	}
}
#endif
