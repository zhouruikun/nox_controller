#ifndef  cmd03_h
#define  cmd03_h

#ifdef   cmd03_globals
#define  cmd03_ext
#else
#define  cmd03_ext  extern
#endif
#include "stm32f10x.h"
#include "datatype.h"
#include "StructUsartBuf.h"
#include "para.h"
//#include "public_function.h"
//#include "SPI1.h"
//#include "SaveHandData.h"
#include "modbus.h"
#include "modbusstruct.h"
//#include "modbus.h"


cmd03_ext uint8 s_cmd03(void);

cmd03_ext void para_wr(cmd06_obj *dptr,uint16 *dat);//´Ó»úÐ´¼Ä´æÆ÷Öµ


#endif
