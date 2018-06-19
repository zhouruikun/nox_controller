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
//          ���ձ�־    �����жϱ�־    ���ն�ʱ��ʱ   ���ռƸ���   
USART_ext u8 RX_Mark1,Rx1InterruptFlag,TimerRx1Count,Rx1Count,Tx1Count,Tx1Num,TimerTx1Count,Tx1InterruptFlag,TX_Mark1;

USART_ext u8 RX_Mark2,Rx2InterruptFlag,TimerRx2Count,Rx2Count,Tx2Count,Tx2Num;
//Baud ������       USARTx  �ڼ�������
void DK_USART_Init(unsigned long Baud,unsigned char USARTx);
void DK_USART_Send_Char(unsigned char USARTx,unsigned char data);
unsigned char DK_USART_WAIT_RXBYTE(unsigned char USARTx);
void DK_USART_PUTS(unsigned char USARTx,unsigned char *buffer);
void DK_USART_PUTS_Const(unsigned char USARTx,const unsigned char *buffer);
void DK_USART_PUTS_Arry(unsigned char USARTx,unsigned char *buffer,unsigned int len);
void DK_USART1_Printf(unsigned char *p,unsigned char *dat);
void DK_USART_OPen_INT(unsigned char USARTx);
void DK_USART_Close_INT(unsigned char USARTx);
//num���͸�����  txbuf ���ͻ�����
void Start_Uart1_Send(u8 num,u16 *txbuf);//�����������жϷ�ʽ
void Rts1485(u8 bit);//0���գ�1����

#endif
