/*
 * RojToModbus.h
 *
 *  Created on: 2013-1-18
 *      Author: lqm_8
 */

#ifndef ROJTOMODBUS_H_
#define ROJTOMODBUS_H_

#ifdef   ROJTOMODBUS_globals
#define  ROJTOMODBUS_ext
#else
#define  ROJTOMODBUS_ext  extern
#endif

//ROJTOMODBUS_ext uint16 sbuff[256];//���ͻ����� ,�������ʱ������inbuff
//ROJTOMODBUS_ext uint16 vbuff[256];//���ͻ�����,�������ʱ������outbuff
ROJTOMODBUS_ext uint8 TempModbusBuf[8];//�ݴ滺��������rojû�е�ַ
ROJTOMODBUS_ext uint8 ModbusToRoj(uint8 *mbuf,uint8 *tempbuf,uint8 *rbuf);//modbusЭ��תRojЭ��
//*mbuf���룬*rbuf�����*tempbufΪmbuf��ֵ��������������
//���ط��͸���num
ROJTOMODBUS_ext  uint8 RojToModbus(uint8 *rbuf,uint8 *vecbuf,uint8 *mbuf);//RojЭ��תModbusЭ��
//*rbuf���� ��*mbuf�����*vecbuf=*tempbuf��ֵ
//���ط��͸���num
#endif /* ROJTOMODBUS_H_ */
