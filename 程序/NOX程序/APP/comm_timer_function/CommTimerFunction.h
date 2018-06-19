#ifndef __CommTimerFunction_H
#define __CommTimerFunction_H

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
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
