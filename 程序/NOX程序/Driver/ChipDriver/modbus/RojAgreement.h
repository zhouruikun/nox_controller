#ifndef ROJAGREEMENT_H_
#define ROJAGREEMENT_H_

#ifdef   RojAgreement_globals
#define  RojAgreement_ext
#else
#define  RojAgreement_ext  extern
#endif

RojAgreement_ext uint8 master_shake_hands_send(uint8 *buffer,RojWrite_obj *dptr);//����������������//RojWrite_obj �ṹ��������Աд���� Ϊ���ͻ�����
RojAgreement_ext uint8 master_shake_hands_rcv(uint8 node_addr,uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr);//�������ֽ���
RojAgreement_ext uint8 master_read_send(uint8 *buffer,RojWrite_obj *dptr);// ������ȡ����
RojAgreement_ext uint8 master_read_back(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr);//�������ؽ���
RojAgreement_ext uint8 master_write_send(uint8 *buffer,RojWrite_obj *dptr,uint16 *ptr);//����д���Է���
RojAgreement_ext uint8 master_write_back(uint8 *buffer);//����д����


#endif /* ROJAGREEMENT_H_ */
