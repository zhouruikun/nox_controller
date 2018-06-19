/* 防止重定义-----------------------------------------------------------------*/
#ifndef _USART2_H
#define _USART2_H
/* 包含头文件 *****************************************************************/

/* 类型声明 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/    
/* 变量 ----------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
/* 函数定义 ------------------------------------------------------------------*/
#ifdef   USART2_globals
#define  USART2_ext
#else
#define  USART2_ext  extern
#endif

USART2_ext u8 RX_Mark2,Rx2InterruptFlag,TimerRx2Count;
//            接收结束标志, 串口中断标志，  接收定时计数
//USART2_ext u8 TX_Mark2,Tx2InterruptFlag,TimerTx2Count;
//            发送结束标志, 发送中断标志，  发送定时计数
//USART2_ext uint8 USART2_SEND_DATA[256],USART2_RECEIVE_DATA[256];
USART2_ext void Usart2_Configuration(u32 baud,u16 UsartParity);//串口2初始化，baud输入波特率，UsartParity为是否效验
USART2_ext void Rts2485(u8 bit);//控制485

#endif


