

#ifndef _cmd20_h
#define _cmd20_h

#ifdef   cmd20_globals
#define  cmd20_ext
#else
#define  cmd20_ext  extern
#endif

#include "stm32f10x.h"
#include "datatype.h"
#include "cmd20.h"
#include "mc_9.h"
#include "pattern_para.h"
#include "StructUsartBuf.h"
#include "dma.h"
#include "para.h"
//#include "public_function.h"
//#include "spi1.h"



cmd20_ext uint8 get_res(void);
cmd20_ext uint8 deci_color_op(uint16 fileno,uint16 recno);
cmd20_ext uint16  cmp_prg(void);
cmd20_ext void  init_prg(void);
//cmd20_ext uint8 ssend_prg20(pattern *ptr,uint8 control,uint8 *obuf,back20_obj *dptr)
//cmd20_ext void msend_prg20(uint8 control,uint8 *obuf);//主机发送20
//cmd20_ext uint8 mrcv_prg20(pattern *ptr,uint8 *abuf,back20_obj *ptr1);//主机接收20读
cmd20_ext  uint8 read_prg_from_flash(void);
//cmd20_ext  uint8 W_R_prg_or_buffer(u8 *inbuff,u8 *outbuff,pattern *pg);
#endif
