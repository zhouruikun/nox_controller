#ifndef __CommTimerFunction_H
#define __CommTimerFunction_H

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
#ifdef   CommTimerFunction_globals
#define  CommTimerFunction_ext
#else
#define  CommTimerFunction_ext  extern
#endif



CommTimerFunction_ext void timer_rev1(void);
CommTimerFunction_ext void timer_rev2(void);
CommTimerFunction_ext void timer_send1(void);
CommTimerFunction_ext void timer_send2(void); 
CommTimerFunction_ext void pressure_measurement_timer(void);
#endif
