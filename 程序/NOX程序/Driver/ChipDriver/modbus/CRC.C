
#include "crc.h"

//接收设备在接收时重新计算 CRC 的值,并且以uint类型返回CRC
unsigned int crc16(unsigned char *puchMsg, unsigned short usDataLen)//函数以 unsigned int 类型返回 CRC 
{ 
   unsigned char uchCRCHi = 0xFF ; //* 高CRC字节初始化 
   unsigned char uchCRCLo = 0xFF ; //* 低CRC 字节初始化  
   unsigned long uIndex ; // CRC循环中的索引 
   while (usDataLen--) // 传输消息缓冲区 
   {   
      uIndex = uchCRCHi ^ *puchMsg++ ; // 计算CRC  
      uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex] ; 
      uchCRCLo = auchCRCLo[uIndex] ; 
   } 
   return (uchCRCHi << 8 | uchCRCLo);
}
