#ifndef _modbus_H
#define _modbus_H


#ifdef   modbus_globals
#define  modbus_ext
#else
#define  modbus_ext  extern
#endif
#include "ModbusStruct.h"
#include "StructUsartBuf.h"
//modbus_ext uint16 para[256];
modbus_ext void pack(uint8  *bufptr,uint8 bt);//解包
modbus_ext uint8 un_pack(uint8 *bufptr,uint8 by);
modbus_ext void err_send(uint8 cmd,uint8 oerr,uint8 *obuff);

//modbus_ext void para_rd(back03_obj *dptr);//主机读寄存器值
modbus_ext uint8 srcv_cmd03(uint8 *buff, req03_obj *dptr);//读保持寄存器请求
modbus_ext void ssend_cmd03(back03_obj *dptr,uint8 *p);//读保持寄存器响应
modbus_ext uint8 truck_req_to_back(req03_obj *dptr,back03_obj *pin);
modbus_ext void para_wr16(cmd16_obj *dptr);
modbus_ext uint8  srcv_cmd06(uint8 *buff, cmd06_obj *dptr);//写单个寄存器从机请求
//modbus_ext void para_wr(cmd06_obj *dptr,uint16 *dat);//从机写寄存器值
modbus_ext void ssend_cmd06(cmd06_obj *dptr, uint8 *buff);//写单个寄存器从机响应

//modbus_ext void W_R_prg_or_buffer(u8 *inbuff,u8 *outbuff,pattern *pg);



//modbus_ext void rcv_modbus(uint8 *buff,uint8 *obuff,uint8 node_addr);



#endif
