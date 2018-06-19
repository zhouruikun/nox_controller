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
	    uint16   start;//ͷ
        uint16   node_addr;//������ַ
        uint16   len;//����
        uint16   cmd;//������
        uint16   data_addr;//�Ĵ�����ַ
	    uint16   save_data_addr;//�洢�Ĵ�����ַ
        uint16   *para_data;//��������
        uint16   end;
}RojWrite_obj;


Roj_Struct_ext RojWrite_obj roj_write;


#endif /* ROJ_STRUCT_H_ */
