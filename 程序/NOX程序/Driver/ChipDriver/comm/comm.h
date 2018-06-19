
/* 防止重定义-----------------------------------------------------------------*/
#ifndef _comm_H
#define _comm_H
/* 包含头文件 *****************************************************************/

/* 类型声明 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/    
/* 变量 ----------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
/* 函数定义 ------------------------------------------------------------------*/
#ifdef   comm_globals
#define  comm_ext


#else
#define  comm_ext  extern
#endif


#define comm1 1
#define comm2 2
 
comm_ext unsigned char feeder_run_st;
comm_ext void Usart_ReceiveAndSend(void);//串口接收并发送
comm_ext void UsartCommInit(void);//串口初始化
comm_ext unsigned char rcv_modbus(unsigned char *inbuf);//

comm_ext int delay_cnt ;
comm_ext void Init_TIM1(void);
#endif
