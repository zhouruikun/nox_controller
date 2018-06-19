#ifndef cmd06_h
#define cmd06_h

#ifdef   cmd06_globals
#define  cmd06_ext
#else
#define  cmd06_ext  extern
#endif
#include "stm32f10x.h"
#include "datatype.h"
#include "modbusstruct.h"
#include "modbus.h"
#include "StructUsartBuf.h"
//#include "public_variable.h"
#include "para.h"
#include "pattern_para.h"
//#include "rwflash.h"
//#include "public_function.h"
//#include "spi1.h"
//#include "spi2.h"
//#include "SaveHandData.h"
cmd06_ext uint8 s_cmd06(void);

cmd06_ext void para_wr(cmd06_obj *dptr,uint16 *dat);//´Ó»úÐ´¼Ä´æÆ÷Öµ
#endif
