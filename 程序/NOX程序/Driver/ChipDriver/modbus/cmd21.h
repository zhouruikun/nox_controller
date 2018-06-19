
#ifndef _cmd21_h
#define _cmd21_h

#ifdef   cmd21_globals
#define  cmd21_ext
#else
#define  cmd21_ext  extern
#endif

#include "stm32f10x.h"
#include "datatype.h"
#include "cmd20.h"
#include "cmd21.h"
#include "pattern_para.h"
#include "mc_9.h"//cmd20 cmd21 结构体
#include "StructUsartBuf.h"
#include "dma.h"
cmd21_ext uint8 write_prg_to_flash(void);


//void msend_prg21(pattern *ptr,uint8 control,uint8 *obuf);//主机发送21写
//uint8 mrcv_prg21(pattern *ptr,uint8 *abuf);//主机接收21写

#endif
