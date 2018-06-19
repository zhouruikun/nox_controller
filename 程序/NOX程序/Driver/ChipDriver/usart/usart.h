#ifndef __USART_H
#define __USART_H

#define DK_USART1 1
#define DK_USART2 2
#define DK_USART3 3

#ifdef   USART_globals
#define  USART_ext
#else
#define  USART_ext  extern
#endif
//          接收标志    接收中断标志    接收定时计时   接收计个数   
USART_ext u8 RX_Mark1,Rx1InterruptFlag,TimerRx1Count,Rx1Count,Tx1Count,Tx1Num,TimerTx1Count,Tx1InterruptFlag,TX_Mark1;

USART_ext u8 RX_Mark2,Rx2InterruptFlag,TimerRx2Count,Rx2Count,Tx2Count,Tx2Num;
//Baud 波特率       USARTx  第几个串口
void DK_USART_Init(unsigned long Baud,unsigned char USARTx);
void DK_USART_Send_Char(unsigned char USARTx,unsigned char data);
unsigned char DK_USART_WAIT_RXBYTE(unsigned char USARTx);
void DK_USART_PUTS(unsigned char USARTx,unsigned char *buffer);
void DK_USART_PUTS_Const(unsigned char USARTx,const unsigned char *buffer);
void DK_USART_PUTS_Arry(unsigned char USARTx,unsigned char *buffer,unsigned int len);
void DK_USART1_Printf(unsigned char *p,unsigned char *dat);
void DK_USART_OPen_INT(unsigned char USARTx);
void DK_USART_Close_INT(unsigned char USARTx);
//num发送个数据  txbuf 发送缓冲区
void Start_Uart1_Send(u8 num,u16 *txbuf);//启动发送以中断方式
void Rts1485(u8 bit);//0接收，1发送

#endif
