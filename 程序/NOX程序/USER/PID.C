#include "stm32f10x.h"
#include "PID.H"
#include "comm.h"
#include "DataFlash.h"
 #include "comm.h"
 	  short  pre_err_AUX,last_err_AUX,err_AUX;
	  long sum_err_AUX=0;
	  short  last_err_REF,err_REF;
	  long sum_err_REF=0;
arg_all Arg_all;


void argInit(void )
{
		Arg_all.PumpO2=0;
	Arg_all.I_PumpO2=0;
	Arg_all.PumpRef=0;
	Arg_all.I_PumpRef=6000 ;
	Arg_all.Ref_VPO2_Set=0;
	Arg_all.I_PumpAux=0;
	Arg_all.I_PumpNox=0;
	Arg_all.Ref_VPAUX_Set=560;
	Arg_all.Ref_VPNO2_Set=570;
	Arg_all.PWM=0;
	Arg_all.Temperture=0;
	Arg_all.PID_P_AUX=-2;
	Arg_all.PID_I_AUX=-20;
	Arg_all.PID_D_AUX=0;
	Arg_all.AUX_I_Set=-700;
	Arg_all.PID_P_REF=0;
	Arg_all.PID_I_REF=0;
	Arg_all.PID_D_REF=0;
	Arg_all.Ref_I_Set=0;
	Arg_all.PID_P_Heater=-10;
	Arg_all.PID_I_Heater=-6;
	Arg_all.PID_D_Heater=-10;
	Arg_all.Heater_Set=6300;
	Arg_all.PID_flag=1;
	Arg_all.NOX_PPM=0;
	Arg_all.O2PP=0;
	Arg_all.NOX_ratio=4310;
	Arg_all.O2_ratio=633;
	Arg_all.offset_I_NOX=2600;//(I_pump[3]*0.80566);
	Arg_all.offset_I_O2=2600;
  Arg_all.offset_I_AUX=2600;//(I_pump[1]*0.80566);	
	Arg_all.auto_adj_th=2000;
	Arg_all.err_code=0;
}
void Init_PID_Arg(void)
{
	 	Flash_Read(FLASH_PAGE_SIZE*50,(u8 *)&Arg_all,sizeof(arg_all));
	if(Arg_all.PID_flag==-1)
			{
				argInit();
				Save_PID_Arg();
		}
}
void Save_PID_Arg(void)
{
		Flash_Write(FLASH_PAGE_SIZE*50,(u8 *)&Arg_all,sizeof(arg_all));
}
int PID_Heater(int get_r)
{
	static short  last_err_Heater,err_Heater;
	static long sum_err_Heater=0;
	int result;
	err_Heater = get_r-Arg_all.Heater_Set;
	sum_err_Heater+=err_Heater;
	if(sum_err_Heater>10000)
		sum_err_Heater=10000;
	if(sum_err_Heater<-10000)
		sum_err_Heater=-10000;
	result=(int)(Arg_all.PID_P_Heater*err_Heater+Arg_all.PID_I_Heater*sum_err_Heater+Arg_all.PID_D_Heater*(err_Heater-last_err_Heater))/100;
	if(result>700)
		result=700;
	if(result<=0)
		result=0;
	last_err_Heater=err_Heater;
	return result;
}
int absi(int i)
{
	return i>0?i:-i;
}
int PID_AUX(int get_r)
{

	int result;
	err_AUX = get_r-Arg_all.AUX_I_Set;
	sum_err_AUX+=err_AUX;

	if(sum_err_AUX>10000)
		sum_err_AUX=10000;
	if(sum_err_AUX<-10000)
		sum_err_AUX=-10000;
	result=(int)(Arg_all.PID_P_AUX*err_AUX+Arg_all.PID_I_AUX*sum_err_AUX+Arg_all.PID_D_AUX*(err_AUX-last_err_AUX))/100;
	if(result>4095)
		result=4095;
	if(result<=0)
		result=0;
	last_err_AUX=err_AUX;
	return result;
}

int PID_REF(int get_r)
{

	int result;
	err_REF = get_r-Arg_all.Ref_I_Set;
	sum_err_REF+=err_REF;
	if(sum_err_REF>1000)
		sum_err_REF=1000;
	if(sum_err_REF<-1000)
		sum_err_REF=-1000;
	result=(int)(Arg_all.PID_P_REF*err_REF+Arg_all.PID_I_REF*sum_err_REF+Arg_all.PID_D_REF*(err_REF-last_err_REF))/100;
	if(result>1500)
		result=1500;
	if(result<=-1800)
		result=-1800;
	last_err_REF=err_REF;
	return result;
}


void Send_TFT(void)
{
	u8 buff[256];u8 index=0;
	buff[0]=0XA5;
	buff[1]=0X5A;
	buff[3]=0X82;
	buff[4]=0X00;
	buff[5]=0X00;	
	while(index<sizeof(Arg_all))
	{
		buff[6+index+1]=*((u8 *)&Arg_all+index);
		buff[6+index]=*((u8 *)&Arg_all+index+1);
		index+=2;
	}
	buff[2]=index+3;
	Start_USART_DMASend(comm1,buff,buff[2]+3);
}
