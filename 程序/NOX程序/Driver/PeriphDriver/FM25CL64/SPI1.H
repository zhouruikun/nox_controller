#ifndef __SPI1_H
#define __SPI1_H			 
#include "stm32f10x.h"
#include "datatype.h"

/*----------------FM25CL64命令--------------------*/
#define  WREN_INST           0x06     //写使能
#define  WRDI_INST           0x04     //写禁止
#define  RDSR_INST           0x05     //读状态寄存器
#define  WRSR_INST           0x01     //写状态寄存器
#define  WRITE_INST          0x02     //写数据
#define  READ_INST           0x03     //读数据

/*----------------CS片选信号--------------------*/
#define FLASH_CS_0			GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define FLASH_CS_1			GPIO_SetBits(GPIOA,GPIO_Pin_4)

/*-----------------应用函数---------------------*/
void SPI1_init(void);	//初始化SPI

u8 SPI1_ReadByte(void);	    //接收字节
u8 SPI1_WriteByte(u8 byte);	//发送字节

void wren_cmd(void); //写使能
void wrdi_cmd(void);//写禁止
u8 rdsr_cmd(void);//读状态寄存器
void wrsr_cmd(u8 status);//写状态寄存器
void wrpara(uint16 reg_addr,uint16 reg_val);//写字节
void write_fm2564(void *ram_addr,uint16 len,uint16 fram_addr);//写数据串
uint16 read_para(uint16 reg_addr); //读字节
void read_fm2564(void *ram_addr,uint16 len,uint16 fram_addr);  //读数据串

//wrsr_cmd(0x00); //无写保护



#endif

