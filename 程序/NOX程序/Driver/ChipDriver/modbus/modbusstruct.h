#ifndef _modbusStruct_H
#define _modbusStruct_H


#ifdef   modbusStruct_globals
#define  modbusStruct_ext
#else
#define  modbusStruct_ext  extern
#endif

typedef struct
{
    uint8 node_addr;//本机地址     
    uint8 cmd;//功能码              
    uint16 data_addrl;//寄存器地址  
    uint16 data_len;//寄存器数量    
}req03_obj;


typedef struct
{
    uint8  node_addr;//本机地址
    uint8  cmd;//功能码
    uint8  bytelen;//字节 
    uint16  data_addr2;//寄存器地址
    uint8  zl_len;
    uint16 para_1[100];
}back03_obj;

typedef struct	 
{
    uint8  node_addr;//地址
    uint8  cmd;//功能码
    uint16   data_addr;//寄存器地址
    uint16   content;//寄存器值
    uint8  zl_len;
}cmd06_obj;

typedef struct
{
    uint8  node_addr;//本机地址
    uint8  cmd;//功能码
    uint16  strat_address;//起始地址 
    uint16  data_len;//寄存器数量
    uint8 byte;//字节数
    uint16 dataptr[100];//值
}cmd16_obj;



modbusStruct_ext req03_obj req03;
modbusStruct_ext back03_obj back03;
modbusStruct_ext cmd06_obj cmd06;
modbusStruct_ext cmd16_obj cmd16;

#endif
