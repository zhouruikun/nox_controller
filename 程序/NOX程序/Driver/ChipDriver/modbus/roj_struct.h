/*
 * Roj_Struct.h
 *
 *  Created on: 2013-1-23
 *      Author: lqm_8
 */

#ifndef ROJ_STRUCT_H_
#define ROJ_STRUCT_H_


#ifdef   Roj_Struct_globals
#define  Roj_Struct_ext
#else
#define  Roj_Struct_ext  extern
#endif


typedef struct
{
	    uint16   start;//头
        uint16   node_addr;//本机地址
        uint16   len;//长度
        uint16   cmd;//功能码
        uint16   data_addr;//寄存器地址
	    uint16   save_data_addr;//存储寄存器地址
        uint16   *para_data;//参数数据
        uint16   end;
}RojWrite_obj;


Roj_Struct_ext RojWrite_obj roj_write;


#endif /* ROJ_STRUCT_H_ */
