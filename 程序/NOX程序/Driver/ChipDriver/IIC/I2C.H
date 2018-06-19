#ifndef __I2C_H
#define __I2C_H


void IIC_Default_Init(unsigned char IICx);

unsigned char I2C_Read(unsigned char DK_I2Cx,unsigned char I2C_Addr,unsigned short addr,unsigned char *buf,unsigned char num,unsigned char addrLenDword);
unsigned char I2C_Write(unsigned char DK_I2Cx,unsigned char I2C_Addr,unsigned short addr,unsigned char *buf,unsigned char num,unsigned char addrLenDword);

#endif
