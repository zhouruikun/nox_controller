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

//ROJTOMODBUS_ext uint16 sbuff[256];//发送缓冲区 ,到箱体板时可以用inbuff
//ROJTOMODBUS_ext uint16 vbuff[256];//发送缓冲区,到箱体板时可以用outbuff
ROJTOMODBUS_ext uint8 TempModbusBuf[8];//暂存缓冲区用于roj没有地址
ROJTOMODBUS_ext uint8 ModbusToRoj(uint8 *mbuf,uint8 *tempbuf,uint8 *rbuf);//modbus协议转Roj协议
//*mbuf输入，*rbuf输出，*tempbuf为mbuf的值，保存输入数据
//返回发送个数num
ROJTOMODBUS_ext  uint8 RojToModbus(uint8 *rbuf,uint8 *vecbuf,uint8 *mbuf);//Roj协议转Modbus协议
//*rbuf输入 ，*mbuf输出，*vecbuf=*tempbuf的值
//返回发送个数num
#endif /* ROJTOMODBUS_H_ */
