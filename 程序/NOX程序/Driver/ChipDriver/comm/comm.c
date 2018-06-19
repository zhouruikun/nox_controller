#define comm_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "usart1.h"
#include "usart2.h"
#include "StructUsartBuf.h"
#include "modbusstruct.h"
#include "rojtomodbus.h"
//#include "cmd21.h"
//#include "cmd20.h"
#include "para.h"
#include "cmd03.h"
#include "cmd06.h"
#include "cmd16.h"
#include "comm.h"
#include "DMA.h"
 #include "PID.H"
//#include "delay.h"
//#include "savehanddata.h"
 #include "para.h"
#include "pattern_wr.h"
	extern long sum_err_AUX;
	
	 	extern short  last_err_AUX;
 
	extern short  last_err_REF;
	extern long sum_err_REF;
void UsartCommInit(void)
{	GPIO_InitTypeDef GPIO_InitStruct;

    //  Usart2_Configuration(9600,USART_Parity_No);//波特率19200 偶校验
    //  USART2_DMA_Config(com2.txbuf,com2.rxbuf);
//	
	   Usart1_Configuration(115200,USART_Parity_No);//波特率19200 偶校验
     USART1_DMA_Config(com1.txbuf,com1.rxbuf);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//复用推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	 GPIO_Init(GPIOB, &GPIO_InitStruct);



}
 void status_ON_OFF(u8 status);


void Usart_ReceiveAndSend(void)
{
    uint8 num;
    //uint16 addr;
    if(get_end_rec(2)==1)//串口2
    {	
       
        switch(*(com2.rxbuf+0))
        {
        case 2:
            num=rcv_modbus(com2.rxbuf);   
            Start_USART_DMASend(comm2,com2.txbuf,num);
            break;  
        }
		Start_USART_DMAReceive(comm2,com2.rxbuf);	//重开DMA				
    }
		 if(get_end_rec(1)==1)//串口1
    {	
      
  
					if(com1.rxbuf[0]==0xa5&&com1.rxbuf[1]==0x5a)
					{  num=com1.rxbuf[5];
							if(num==0x1a)
							{
							    status_ON_OFF(1);
							}
							if(num==0x1b)
							{
							   status_ON_OFF(0);
							}
							if(num==0x17)
							{
							  sum_err_REF=last_err_REF=last_err_AUX=sum_err_AUX=0;
							}
						 	*((u8 *)&Arg_all+num*2)=com1.rxbuf[8];
							*((u8 *)&Arg_all+num*2+1)=com1.rxbuf[7];
						  Save_PID_Arg();
					}
					  //  Start_USART_DMASend(comm1,(u8 *)&Arg_all,sizeof(Arg_all));
	  	Start_USART_DMAReceive(comm1,com1.rxbuf);	//重开DMA	
    }

}


/************************************************************** 
 函数说明： 03读取数据
**************************************************************/

uint8 rcv_modbus(uint8 *inbuf)
{
    uint8 num=0;
    switch(*(inbuf+1))
    {
    case 3:
        
        num=s_cmd03();
        break;
    case 6:
        num=s_cmd06();
        break;
    case 16:
        num=s_cmd16();
        break;
    case 20:
        //num=read_prg_from_flash();
        break;
    case 21:
        //num=write_prg_to_flash();
        break;
    }
    return num;
             
}



