#ifndef __SPI2_H
#define __SPI2_H			 
#include "stm32f10x.h"
#include "datatype.h"

/*----------------CS片选信号--------------------*/
#define AT_CS_0			GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define AT_CS_1			GPIO_SetBits(GPIOB,GPIO_Pin_12)

/*-----------------应用函数---------------------*/
void SPI2_init(void);	//初始化SPI

u8 SPI2_ReadByte(void);	    //接收字节
u8 SPI2_WriteByte(u8 byte);	//发送字节


u8 AT_RSR(void);      //读状态寄存器
// 数据写入缓存器	 操作码：0x84 缓存1；操作码：0x87 缓存2
void AT_bwrite(u8 buffer,u16 BFA,u8 *ptr,u16 len);
// 数据先写入缓存器，再将缓存器上数据写入主内存（带预擦除）
void write_array(u8 buffer,u16 PA,u16 BFA,u8 *ptr,u16 len);
// 数据先写入缓存器，再将缓存器上数据写入主内存（不带预擦除）
void write_array_no(u8 buffer,u16 PA,u16 BFA,u8 *ptr,u16 len);
// 从主内存读数据串	 操作码：0x52
void read_array(u16 PA,u16 BFA,u8 *ptr,u16 len);
// 缓存器上数据写入主内存（带预擦除）
void buffer_array(u8 buffer,u16 PA);

// PA  页地址，0 - 2047   共89个花板
//pattno 花板号
void read_from_flash(uint8 pattno,uint8 *prg_buf);
// PA  页地址，0 - 2047   共89个花板
//pattno 花板号
//写好以后需过7ms后才能保证可靠读取正确数据
void write_to_flash(uint8 pattno,uint8 *prg_buf);

void ES_RSR(u8 *ptr); //读扇区信息

#endif

