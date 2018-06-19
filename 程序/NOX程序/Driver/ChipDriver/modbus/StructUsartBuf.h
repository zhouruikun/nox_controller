/* 防止重定义-----------------------------------------------------------------*/
#ifndef _StructUsartBuf_H
#define _StructUsartBuf_H
/* 包含头文件 *****************************************************************/

/* 类型声明 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/    
/* 变量 ----------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
/* 函数定义 ------------------------------------------------------------------*/
#ifdef   StructUsartBuf_globals
#define  StructUsartBuf_ext
#else
#define  StructUsartBuf_ext  extern
#endif


typedef struct 
{
    uint8 rxbuf[256];
    uint8 txbuf[256]; 
}com_obj;

StructUsartBuf_ext com_obj com1,com2;

StructUsartBuf_ext uint8 *get_inbuf(com_obj *com);
StructUsartBuf_ext uint8 *get_outbuf(com_obj *com);
StructUsartBuf_ext uint8 get_end_rec(uint8 channel);


#endif
