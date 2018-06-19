//#include <includes.h>

#ifndef _RS485_H_
#define _RS485_H_


#ifdef   RS485_globals
#define  RS485_ext
#else
#define  RS485_ext  extern   
#endif

#ifdef   RS485_globals

#define     RTS    GPIO_PIN_7
#define RTS_high() GPIOPinWrite(GPIO_PORTA_BASE,RTS,RTS)//高电平为发送
#define RTS_low()  GPIOPinWrite(GPIO_PORTA_BASE,RTS,(0xFF-RTS))//低电平为接收



RS485_ext void init_RS485(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);                          /*  使能GPIOH                   */
	GPIOPadConfigSet(GPIO_PORTA_BASE, RTS, GPIO_STRENGTH_2MA,
                    GPIO_PIN_TYPE_STD); 								  /*  配置片选管脚为上拉，2MA输出*/
	GPIODirModeSet(GPIO_PORTA_BASE, RTS, GPIO_DIR_MODE_OUT);         /*  配置片选管脚为输出         */

}
#else
#define     RTS    GPIO_PIN_7
#define RTS_high() GPIOPinWrite(GPIO_PORTA_BASE,RTS,RTS)
#define RTS_low()  GPIOPinWrite(GPIO_PORTA_BASE,RTS,(0xFF-RTS))
RS485_ext  void init_RS485(void);

#endif
#endif
