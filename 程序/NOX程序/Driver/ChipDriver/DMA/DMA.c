
#define DMA_globals
#include "stm32f10x.h"
#include "datatype.h"
#include "delay.h"
#include "DMA.h"
#include "usart1.h"
#include "usart2.h"
#include "StructUsartBuf.h"

#define USART1_DR_BASE    ((u32)0x40013804)
#define USART2_DR_BASE    ((u32)0x40004404)

/*
 * 函数名：Delay
 * 描述  ：延时函数
 * 输入  : dly
 * 输出  ：无
 */	



void DMA1_RCC_Configuration(void)
{
    /* Enable DMA1 clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
}



void Uart1_DMA_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    DMA1_RCC_Configuration(); 
    
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置优先级分组：先占优先级和从优先级
	//Enable DMA Channel4 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    
    /*Enable DMA Channel5 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    
}

void Uart2_DMA_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    DMA1_RCC_Configuration(); 
    //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置优先级分组：先占优先级和从优先级
/*Enable DMA Channel6 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
     //Enable DMA Channel7 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
}    

/*
 * 函数名：USART1_DMA_RxConfig
 * 描述  ：DMA1通道5接收配置函数
 * 输入  : RxInitBuf1
 * 输出  ：无
 */	
void USART1_DMA_RxConfig(uint8 *RxInitBuf1)
{
   /* DMA1 Channel5 (triggered by USART1 Rx event) Config */
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel5);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxInitBuf1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 256;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
  
  DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
  DMA_ITConfig(DMA1_Channel5, DMA_IT_TE, ENABLE);
  
  /* Enable USART1 DMA RX request */
  USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
  
  DMA_Cmd(DMA1_Channel5, ENABLE);

}
/*
 * 函数名：USART1_DMA_TxConfig
 * 描述  ：DMA1通道4发送配置函数
 * 输入  : TxInitBuffer
 * 输出  ：无
 */	
void USART1_DMA_TxConfig(uint8 *TxInitBuf1)
{
   /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel4);  
  DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_BASE;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxInitBuf1;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 256;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  
  DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
  DMA_ITConfig(DMA1_Channel4, DMA_IT_TE, ENABLE);
  /* Enable USART1 DMA TX request */
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  
  DMA_Cmd(DMA1_Channel4, DISABLE);
  
}

/*
 * 函数名：USART2_DMA_RxConfig
 * 描述  ：DMA1通道6接收配置函数
 * 输入  : RxInitBuffer
 * 输出  ：无
 */	
void USART2_DMA_RxConfig(uint8 *RxInitBuf2)
{
  /* DMA channel6 configuration USART RX*/
  DMA_InitTypeDef DMA_InitStructure;
  DMA_DeInit(DMA1_Channel6);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)USART2_DR_BASE;  //设置外设地址串口2
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)RxInitBuf2;	  //设置存储器地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   //外设地址为传输的源地址
  DMA_InitStructure.DMA_BufferSize = 256;	//数据传输长度
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不递增
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	 //存储器地址递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //外设数据宽度 8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//存储器数据宽度
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular	 //循环模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;  //高优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	//内存到内存传输失能
  DMA_Init(DMA1_Channel6, &DMA_InitStructure);

  DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);  //传输完成中断使能
  DMA_ITConfig(DMA1_Channel6, DMA_IT_TE, ENABLE);  //传输错误中断使能
  USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); //使能USART2的接收,传送DMA请求

  DMA_Cmd(DMA1_Channel6, ENABLE); //开启DMA1通道6
}

/*
 * 函数名：USART2_DMA_TxConfig
 * 描述  ：DMA1通道7发送配置函数
 * 输入  : TxInitBuffer
 * 输出  ：无
 */	

void USART2_DMA_TxConfig(uint8 *TxInitBuf2)
{
    /* DMA channel7 configuration USART TX*/
   DMA_InitTypeDef DMA_InitStructure;
   DMA_DeInit(DMA1_Channel7);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)USART2_DR_BASE; //设置外设地址串口2
   DMA_InitStructure.DMA_MemoryBaseAddr = (u32)TxInitBuf2;	  //设置存储器地址
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;		 //外设地址为传输的目的地址
   DMA_InitStructure.DMA_BufferSize = 256;		//数据传输长度
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	 //外设地址不递增
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	   //存储器地址递增
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设数据宽度 8位
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 	//存储器数据宽度
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;  //循环模式
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;	 //高优先级
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	  //内存到内存传输失能
   DMA_Init(DMA1_Channel7, &DMA_InitStructure);

   DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);  //传输完成中断使能
   DMA_ITConfig(DMA1_Channel7, DMA_IT_TE, ENABLE);	//传输错误中断使能
   USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);	//使能USART2的发送,传送DMA请求
   DMA_Cmd(DMA1_Channel7, DISABLE);		//关闭DMA1通道7


}


void USART2_DMA_Config(uint8 *TxInitBuf2,uint8 *RxInitBuf2)
{
    Uart2_DMA_NVIC_Configuration();
    USART2_DMA_RxConfig(RxInitBuf2);
    USART2_DMA_TxConfig(TxInitBuf2);
}

void USART1_DMA_Config(uint8 *TxInitBuf1,uint8 *RxInitBuf1)
{
    Uart1_DMA_NVIC_Configuration();
    USART1_DMA_RxConfig(RxInitBuf1);
    USART1_DMA_TxConfig(TxInitBuf1);
}


/*
 * 函数名：Start_USART_DMAReceive
 * 描述  ：启动串口 DMA 接收函数
 * 输入  : Getbuf,com
 * 输出  ：无
 */

void Start_USART_DMAReceive(uint8 Channel,uint8 *Getbuf)
{
    //getbuf = USART2_RECEIVE_DATA;
    if(Channel==1)//
    {
        DMA_Cmd(DMA1_Channel5, DISABLE); //关闭通道6
        DMA1_Channel5->CMAR = (u32)Getbuf;	//设置存储器外设地址 
        DMA1_Channel5->CNDTR = 256;//重装填传输长度
        DMA_Cmd(DMA1_Channel5, ENABLE);//处理完,重开DMA
    }
    else if(Channel==2)
    {
        DMA_Cmd(DMA1_Channel6, DISABLE); //关闭通道6
        DMA1_Channel6->CMAR = (u32)Getbuf;	//设置存储器外设地址 
        DMA1_Channel6->CNDTR = 256;//重装填传输长度
        DMA_Cmd(DMA1_Channel6, ENABLE);//处理完,重开DMA
    }	
}

/*
uint8 Get_DMA_ReceiveData(USART_TypeDef* USARTx,uint8 *RecData)
{
	 if(USARTx==USART1)
	 return *RecData;
	 else if(USARTx==USART2)
	 return *RecData;
}

*/
/*
 * 函数名：USART_DMA_SendStart
 * 描述  ：启动串口 DMA 发送函数
 * 输入  : Sendbuf,Buffersize,com
 * 输出  ：无
 */
/*
void Start_USART_DMASend(USART_TypeDef* USARTx,uint8 *Sendbuf,uint8 Buffersize)
{	
    if(USARTx==USART1)
    {
        //改变datasize前先要禁止通道工作
        DMA_Cmd(DMA1_Channel4, DISABLE); //关闭通道7
        DMA1_Channel4->CNDTR=Buffersize; //DMA1,传输数据量
        DMA1_Channel4->CMAR = (u32)Sendbuf;//设置存储器外设地址	
        DMA_Cmd(DMA1_Channel4, ENABLE);	 //使能DMA发送
    }
    else if(USARTx==USART2)
    {
        //改变datasize前先要禁止通道工作
        DMA_Cmd(DMA1_Channel7, DISABLE); //关闭通道7
        DMA1_Channel7->CNDTR=Buffersize; //DMA1,传输数据量
        DMA1_Channel7->CMAR = (u32)Sendbuf;//设置存储器外设地址	
        DMA_Cmd(DMA1_Channel7, ENABLE);	 //使能DMA发送
    }
}
*/

/*
uint8 Get_DMA_ReceiveData(USART_TypeDef* USARTx,uint8 *RecData)
{
	 for()   
}

*/
/*
 * 函数名：USART_DMA_SendStart
 * 描述  ：启动串口 DMA 发送函数
 * 输入  : Sendbuf,Buffersize,com
 * 输出  ：无
 */

void Start_USART_DMASend(uint8 Channel,uint8 *Sendbuf,uint8 Buffersize)
{	
    if(Buffersize>4)
    {
        if(Channel==1)//串口1
        {

            //convert485_rts(USART1,1);
            Rts1485(1);
            //改变datasize前先要禁止通道工作
            DMA_Cmd(DMA1_Channel4, DISABLE); //关闭通道7
            DMA1_Channel4->CNDTR=Buffersize; //DMA1,传输数据量
            DMA1_Channel4->CMAR = (u32)Sendbuf;//设置存储器地址	
            
            DMA_Cmd(DMA1_Channel4, ENABLE);	 //使能DMA发送
            
            
            //while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0);
            //USART_ClearFlag(USART1,USART_FLAG_TC);
            //Rts1485(0);
        }
        else if(Channel==2)//串口2
        {

            //convert485_rts(USART2,1);
            Rts2485(1);
            //改变datasize前先要禁止通道工作
            DMA_Cmd(DMA1_Channel7, DISABLE); //关闭通道7
            DMA1_Channel7->CNDTR=Buffersize; //DMA1,传输数据量
            DMA1_Channel7->CMAR = (u32)Sendbuf;//设置存储器地址	
            DMA_Cmd(DMA1_Channel7, ENABLE);	 //使能DMA发送
            //USART_ITConfig(USART2, USART_IT_TC, ENABLE);
            //while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==0);
           // USART_ClearFlag(USART2,USART_FLAG_TC);
           // Rts2485(0);

        }
    } 
    
    //delay(1000);
    //Send_end_rec(Channel);
}

/*
 * 函数名：DMA1_Channel6_IRQHandler
 * 描述  ：DMA1_Channel6中断函数
 * 输入  : 
 * 输出  ：无
 */
void DMA1_Channel6_IRQHandler(void)//usart2 rx
{
  DMA_ClearITPendingBit(DMA1_IT_HT6); //清除传输过半中断
  DMA_ClearITPendingBit(DMA1_IT_TC6); //清除传输完成中断
  DMA_ClearITPendingBit(DMA1_IT_TE6); //清除传输错误中断
  DMA_Cmd(DMA1_Channel6, DISABLE);//关闭DMA,防止处理其间有数据
  DMA1_Channel6->CNDTR = 256;//重装填
  DMA_Cmd(DMA1_Channel6, ENABLE);//处理完,重开DMA

}

/*
 * 函数名：DMA1_Channel7_IRQHandler
 * 描述  ：DMA1_Channel7中断函数
 * 输入  : 
 * 输出  ：无
 */
void DMA1_Channel7_IRQHandler(void)//usart2 tx
{
  
 // RTS2485(0);
  if(DMA_GetITStatus(DMA1_IT_TC7)!=RESET)
  {
      //USART_ITConfig(USART2, USART_IT_TC, ENABLE);/////////
      DMA_ClearITPendingBit(DMA1_IT_TC7);  //清除传输完成中断  
  }
  DMA_ClearITPendingBit(DMA1_IT_HT7);//清除传输过半中断
  DMA_ClearITPendingBit(DMA1_IT_TE7); //清除传输错误中断
  DMA_Cmd(DMA1_Channel7, DISABLE);//关闭DMA
  
}


void DMA1_Channel5_IRQHandler(void)//usart1 rx
{
  DMA_ClearITPendingBit(DMA1_IT_HT5); //清除传输过半中断
  DMA_ClearITPendingBit(DMA1_IT_TC5); //清除传输完成中断
  DMA_ClearITPendingBit(DMA1_IT_TE5); //清除传输错误中断
  DMA_Cmd(DMA1_Channel5, DISABLE);//关闭DMA,防止处理其间有数据
  DMA1_Channel5->CNDTR = 256;//重装填
  DMA_Cmd(DMA1_Channel5, ENABLE);//处理完,重开DMA

}



void DMA1_Channel4_IRQHandler(void)//usart1 tx
{
  if(DMA_GetITStatus(DMA1_IT_TC4)!=RESET)
  {
      //USART_ITConfig(USART1, USART_IT_TC, ENABLE);///////
      DMA_ClearITPendingBit(DMA1_IT_TC4);  //清除传输完成中断  
  }
  DMA_ClearITPendingBit(DMA1_IT_HT4);//清除传输过半中断
  DMA_ClearITPendingBit(DMA1_IT_TE4); //清除传输错误中断
  DMA_Cmd(DMA1_Channel4, DISABLE);//关闭DMA
  
}
