#ifndef ROJAGREEMENT_H_
#define ROJAGREEMENT_H_

#ifdef   RojAgreement_globals
#define  RojAgreement_ext
#else
#define  RojAgreement_ext  extern
#endif

RojAgreement_ext uint8 master_shake_hands_send(uint8 *buffer,RojWrite_obj *dptr);//主机发送握手命令//RojWrite_obj 结构体可以向成员写数据 为发送缓冲区
RojAgreement_ext uint8 master_shake_hands_rcv(uint8 node_addr,uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr);//主机握手接收
RojAgreement_ext uint8 master_read_send(uint8 *buffer,RojWrite_obj *dptr);// 主机读取发送
RojAgreement_ext uint8 master_read_back(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr);//主机返回接收
RojAgreement_ext uint8 master_write_send(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr);//主机写测试发送
RojAgreement_ext uint8 master_write_back(uint8 *buffer);//主机写返回


#endif /* ROJAGREEMENT_H_ */
