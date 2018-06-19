#ifndef comm_roj_H_
#define comm_roj_H_

#ifdef   comm_roj_globals
#define  comm_roj_ext
#else
#define  comm_roj_ext  extern
#endif

//comm_roj_ext uint8 i1,i2, y1,y2;
comm_roj_ext uint8 shake_hands_init(uint8 *ptr);//����
comm_roj_ext void roj_read_remote_shake_hands(uint8 node_addr,uint8 *error);//����
comm_roj_ext void roj_read_remote_para(uint16 para_addr,uint16 save_para_addr,uint8 node_addr,uint8 *error);//��ȡ
comm_roj_ext void roj_write_remote_para(uint16 para_addr,uint16 save_para_addr,uint8 node_addr,uint8 len,uint8 cmd,uint8 *error);//����Ͳ���

comm_roj_ext uint8 read_remote_oneline_parameter(uint16 row);//��һ������
comm_roj_ext uint8 read_length_parameter(uint8 node_addr);//��γ��
comm_roj_ext uint8 save_remote_para_data(uint16 row);//дһ������
comm_roj_ext uint8 shake_hands(uint8 *ptr);//����
comm_roj_ext uint8 Text_motor(uint16 row);
comm_roj_ext uint8 Exit_text_motor(uint16 row);

#endif
