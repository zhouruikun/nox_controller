
/* ��ֹ�ض���-----------------------------------------------------------------*/
#ifndef _comm_H
#define _comm_H
/* ����ͷ�ļ� *****************************************************************/

/* �������� ------------------------------------------------------------------*/
/* �궨�� --------------------------------------------------------------------*/    
/* ���� ----------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
/* �������� ------------------------------------------------------------------*/
#ifdef   comm_globals
#define  comm_ext


#else
#define  comm_ext  extern
#endif


#define comm1 1
#define comm2 2
 
comm_ext unsigned char feeder_run_st;
comm_ext void Usart_ReceiveAndSend(void);//���ڽ��ղ�����
comm_ext void UsartCommInit(void);//���ڳ�ʼ��
comm_ext unsigned char rcv_modbus(unsigned char *inbuf);//

comm_ext int delay_cnt ;
comm_ext void Init_TIM1(void);
#endif
