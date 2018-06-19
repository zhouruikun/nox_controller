#ifndef __AT24C02_H
#define __AT24C02_H
				   
#ifdef   AT24C02_globals
#define  AT24C02_ext
#else
#define  AT24C02_ext  extern
#endif

#include "datatype.h"

#define AT24c02_addr_samp_time   8    //采样时间
#define AT24c02_addr_Filt_ratio  12   //滤波系数
#define AT24c02_addr_TempAdj     0    //温度矫正系数
#define AT24c02_addr_offSetScope 2    //温度零点浓度
#define AT24c02_addr_offSettemp  4   //温度零点

 #define AT24c02_addr_adj_mode   6    //校准模式




AT24C02_ext void AT24C02_Init(void);
AT24C02_ext unsigned char I2C_EEPROM_Write(unsigned int WriteAddr, unsigned char* pBuffer, unsigned int NumByteToWrite);
AT24C02_ext unsigned char I2C_EEPROM_Read(unsigned int ReadAddr, unsigned char* pBuffer, unsigned int NumByteToRead);

//WriteAddr写入地址     val要写入的数据
AT24C02_ext unsigned char AT24c02WriteSingle(unsigned int WriteAddr, unsigned char val);//写入8位的一个数据
//ReadAddr读取地址
AT24C02_ext unsigned char AT24c02ReadSingle(unsigned int ReadAddr);//读取8位的一个数据
//AT24C02_ext unsigned char AT24c02WriteDouble(unsigned int WriteAddr, unsigned int val);//写入16位的一个数据
//AT24C02_ext unsigned int AT24c02ReadDouble(unsigned int ReadAddr);//读取16位的一个数据
AT24C02_ext  uint16 AT24c02WriteDouble(uint16 WriteAddr, uint16 val);
AT24C02_ext  uint16 AT24c02ReadDouble(uint16 ReadAddr);

#endif

