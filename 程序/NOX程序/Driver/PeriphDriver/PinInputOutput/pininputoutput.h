#ifndef __PinInputOutput_H
#define __PinInputOutput_H
#include "stm32f10x.h"
#include "datatype.h"
#ifdef   PinInputOutput_globals
#define  PinInputOutput_ext
#else
#define  PinInputOutput_ext  extern
#endif

PinInputOutput_ext uint8 Base1_count;//计数
PinInputOutput_ext uint8 Base1_flag;//标志
PinInputOutput_ext uint8 key_count;
PinInputOutput_ext uint8 key_flag;

//PinInputOutput_ext uint8 Base1_count,Base_flag;

PinInputOutput_ext void Base11_init(void);
PinInputOutput_ext void Base11_Output(uint8 val);

PinInputOutput_ext void start1_init(void);
PinInputOutput_ext void set_start1(uint8 val);

PinInputOutput_ext void Gripper_pin_init(void);
PinInputOutput_ext void GripperOutA(uint8 val);
PinInputOutput_ext void GripperOutB(uint8 val);

PinInputOutput_ext void Valve_pin_init(void);
PinInputOutput_ext void ValveOut(uint8 val);
PinInputOutput_ext void ValveCs(uint8 val);



#endif
