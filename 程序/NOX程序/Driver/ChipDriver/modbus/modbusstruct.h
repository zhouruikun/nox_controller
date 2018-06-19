#ifndef _modbusStruct_H
#define _modbusStruct_H


#ifdef   modbusStruct_globals
#define  modbusStruct_ext
#else
#define  modbusStruct_ext  extern
#endif

typedef struct
{
    uint8 node_addr;//������ַ     
    uint8 cmd;//������              
    uint16 data_addrl;//�Ĵ�����ַ  
    uint16 data_len;//�Ĵ�������    
}req03_obj;


typedef struct
{
    uint8  node_addr;//������ַ
    uint8  cmd;//������
    uint8  bytelen;//�ֽ� 
    uint16  data_addr2;//�Ĵ�����ַ
    uint8  zl_len;
    uint16 para_1[100];
}back03_obj;

typedef struct	 
{
    uint8  node_addr;//��ַ
    uint8  cmd;//������
    uint16   data_addr;//�Ĵ�����ַ
    uint16   content;//�Ĵ���ֵ
    uint8  zl_len;
}cmd06_obj;

typedef struct
{
    uint8  node_addr;//������ַ
    uint8  cmd;//������
    uint16  strat_address;//��ʼ��ַ 
    uint16  data_len;//�Ĵ�������
    uint8 byte;//�ֽ���
    uint16 dataptr[100];//ֵ
}cmd16_obj;



modbusStruct_ext req03_obj req03;
modbusStruct_ext back03_obj back03;
modbusStruct_ext cmd06_obj cmd06;
modbusStruct_ext cmd16_obj cmd16;

#endif
