#define USART_globals
#include "stm32f10x_usart.h"
#include "datatype.h"
#include "StructUsartBuf.h"
#include "GPIO.H"
#include "USART.H"




void rts1485init(void)
{
    
    DK_GPIO_Init(PA,GPIO_Pin_11,Out_PP); //推挽输出
}

void Rts1485(u8 bit)
{
    if(bit==0)
    {
        PAout(11)=0;
    }
    else
    {
        PAout(11)=1;
    }
    
}
/*******************************************************************************
*函数功能：串口初始化
*函数描述：
***********************************************************************************/
void DK_USART_Init(unsigned long Baud,unsigned char USARTx)
{								 
	USART_InitTypeDef    USART_InitStructure; 
	USART_InitStructure.USART_BaudRate =Baud;  //bps,如9600  19200
	#ifndef _USART_Use
	#define _USART_Use
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//8位数据
		USART_InitStructure.USART_StopBits = USART_StopBits_1;	  //1位停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;	//	无奇偶校验
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	   //无硬件控制流
		USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	 //发送接收使能
	#endif
	if(USARTx==1)
	{											  
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE);
		DK_GPIO_Init(PA,GPIO_Pin_9,AF_PP);	//复用推挽输出  TX
		DK_GPIO_Init(PA,GPIO_Pin_10,IN_FLOATING);	//  RX
	    USART_Init(USART1, &USART_InitStructure);//初始化串口
		USART_Cmd(USART1, ENABLE);	//使能串口  
	}
	if(USARTx==2)
	{
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
		DK_GPIO_Init(PA,GPIO_Pin_2,AF_PP);	//复用推挽输出  TX
		DK_GPIO_Init(PA,GPIO_Pin_3,IN_FLOATING);	//  RX
		USART_Init(USART2, &USART_InitStructure);//初始化串口
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);//清楚中断位
		USART_Cmd(USART2, ENABLE);	//使能串口  
	}
	if(USARTx==3)
	{
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);  //端口管脚重映射
		DK_GPIO_Init(PC,GPIO_Pin_10,AF_PP);	//复用推挽输出  TX
		DK_GPIO_Init(PC,GPIO_Pin_11,IPU);	//  RX
		USART_Init(USART3, &USART_InitStructure);//初始化串口
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清楚中断位
		USART_Cmd(USART3, ENABLE);	//使能串口				  
	}
    rts1485init();
 	
}
/*******************************************************************************
*函数功能：打开中断
*函数描述：
***********************************************************************************/
void DK_USART_OPen_INT(unsigned char USARTx)
{
	switch(USARTx)
	{
	 	case 1:	
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能发送中断 
		break;
		
		case 2:	
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
		break;

		case 3:	
			USART_ClearITPendingBit(USART3,USART_IT_RXNE);
			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		break;
	} 
}
/*******************************************************************************
*函数功能：关闭中断
*函数描述：
***********************************************************************************/
void DK_USART_Close_INT(unsigned char USARTx)
{
	switch(USARTx)
	{
	 	case 1:	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);//关闭接收中断
		break;
		
		case 2:	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		break;

		case 3:	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
		break;
	} 
}
/*******************************************************************************
*函数功能：查询法发送一个字节
*函数描述：
***********************************************************************************/
void DK_USART_Send_Char(unsigned char USARTx,unsigned char data)
{
	switch(USARTx)
	{
	 	case 1:	USART_SendData(USART1,data); 
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);     //等待发送完毕
		break;
		
		case 2:	USART_SendData(USART2,data);  
				while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		break;

		case 3:	USART_SendData(USART3,data);  
				while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		break;
	} 
}
/*******************************************************************************
*函数功能：USARTx查询方式接收数据
*函数描述：
*******************************************************************************/
unsigned char DK_USART_WAIT_RXBYTE(unsigned char USARTx)
{
    u8 i;
	switch(USARTx)
	{
		case 1:		 
	    	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);   //等待接收数据  
			i=USART_ReceiveData(USART1);
		break;
		case 2:				   
	    	while(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==RESET);
			i=USART_ReceiveData(USART2);
		break;
		case 3:				
	    	while(USART_GetFlagStatus(USART3,USART_FLAG_RXNE)==RESET);
			i=USART_ReceiveData(USART3);
		break;
	}
	return i;
} 

/*******************************************************************************
*函数功能：USART输出一个字符串数据
*函数描述：如果buffer指向一个数组，则数组的最后一位必须为0
*******************************************************************************/
void DK_USART_PUTS(unsigned char USARTx,unsigned char *buffer)
{	    
	while(*buffer)
	{	
		DK_USART_Send_Char(USARTx,*buffer);
		buffer++;
	}
} 
void DK_USART_PUTS_Const(unsigned char USARTx,const unsigned char *buffer)
{							 
    while(*buffer)
	{	
		DK_USART_Send_Char(USARTx,*buffer);
		buffer++;
	}
}
void DK_USART_PUTS_Arry(unsigned char USARTx,unsigned char *buffer,unsigned int len)
{			   
    while(len--)
	{
	    DK_USART_Send_Char(USARTx,*buffer);
		buffer++;
	}	   
} 
/*******************************************************************/
/*                                                                 */
/* STM32向串口1发送1串                                           */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
void Start_Uart1_Send(u8 num,u16 *txbuf)//启动发送以中断方式
{
    Rts1485(1); 
    Tx1Count=0;
    Tx1Num=num-1;
    Rx1InterruptFlag=0;
    //DK_USART_Close_INT(1);//
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);//关闭接收中断
    USART_ClearFlag(USART1, USART_FLAG_TC);//清除传输完成标志位,否则可能会丢失第1个字节的数据
    USART_SendData(USART1,*txbuf); 
    //DK_USART_OPen_INT(1);
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);//使能发送中断 
    
    
}
/*******************************************************************************
*函数功能：USART1标准输出函数，用于输出某变量的值
*函数描述：
*******************************************************************************/
void DK_USART1_Printf(unsigned char *p,unsigned char *dat)
{
    u8 shu[4];
    while((*p)!= 0)
	{
	    if((*p)!='%')
		{
		    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
		    USART_SendData(USART1,*p);
			p++;
		}
		else
		{
		    p++;
			switch(*p)
			{
			    case 'c':    //字符输出
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
			    USART_SendData(USART1,*dat);
				break;
				
				case 's':    //字符串输出
				while((*dat)!=0)
				{
				    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				    USART_SendData(USART1,*dat);
					dat++;
				}
				break;
				
				case 'd':
				shu[0]=((*dat)/1000)|0x30;
				shu[1]=((*dat)%1000/100)|0x30;
				shu[2]=((*dat)%100/10)|0x30;
				shu[3]=((*dat)%10)|0x30;
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				USART_SendData(USART1,shu[0]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				USART_SendData(USART1,shu[1]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				USART_SendData(USART1,shu[2]);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
				USART_SendData(USART1,shu[3]);
				break;
			}
			p++;
		}
	}
}


/*******************************************************************/
/*                                                                 */
/* STM32在串口1接收1字节                                           */
/* 说明：串口1接收中断                                             */
/*                                                                 */
/*******************************************************************/
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)    //若接收数据寄存器满
    {     
        com1.rxbuf[Rx1Count++]= USART_ReceiveData(USART1);//接收数据 Receive data
        RX_Mark1=0;
        Rx1InterruptFlag=1;
        TimerRx1Count=0; 
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清楚传输完成中断DISABLE THE Usart1 Receive interrupt
    }
    if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)//若发送数据寄存器满
    {  

        if(Tx1Count < Tx1Num)
        {
            Tx1Count++;
            USART_SendData(USART1, com1.txbuf[Tx1Count]);
            USART_ClearITPendingBit(USART1, USART_IT_TC);//清楚传输完成中断 Disable the Usart1 transmit complete interrupt
            
        }
        else
        {
            Rts1485(0);
            
            //LED0=!LED0;
            USART_ITConfig(USART1, USART_IT_TC, DISABLE);//关闭发送中断Disable the USART2 Transmit interrupt 
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断Enable the USART2 Receive interrupt 
        }
        //USART_SendData(USART1, com1.txbuf[Tx1Count++]);
        //USART_ClearITPendingBit(USART1, USART_IT_TC);//清楚传输完成中断 Disable the Usart1 transmit complete interrupt
        //if(Tx1Count == Tx1Num)
        //{
        //    Rts1485(0);
        //    LED0=!LED0;
        //    USART_ITConfig(USART1, USART_IT_TC, DISABLE);//关闭发送中断Disable the USART2 Transmit interrupt 
        //    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断Enable the USART2 Receive interrupt 
        //}
             
    }
    else
    {
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断
        Rts1485(0);
        Rx1Count=0;
    }
    
   //状态寄存器USART_SR的复位值为0x00C0H, 也就是第七位TXE和第六位TC复位值为1，而TXE=1,
    //表明发送数据寄存器为空， TC=1表明发送已完成。而在USART的设置中有
}


