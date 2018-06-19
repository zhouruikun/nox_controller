#ifndef  cmd16_h
#define  cmd16_h

#ifdef   cmd16_globals
#define  cmd16_ext
#else
#define  cmd16_ext  extern
#endif

#include "stm32f10x.h"
#include "datatype.h"
#include "modbusstruct.h"
#include "modbus.h"
#include "StructUsartBuf.h"
//#include "public_variable.h"
#include "para.h"
#include "pattern_para.h"

cmd16_ext void ssend_cmd16(cmd16_obj *dptr,uint8 *p);//读保持寄存器响应
cmd16_ext uint8  srcv_cmd16(uint8 *buff, cmd16_obj *dptr);//写单个寄存器从机请求
cmd16_ext uint8 s_cmd16(void);
//cmd16_ext void rcv_modbus(uint8 *buff,uint8 *obuff);
#endif
