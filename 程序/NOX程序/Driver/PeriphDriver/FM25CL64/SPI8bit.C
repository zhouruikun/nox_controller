/**
  ******************************************************************************
  * 文件名    SPI1.c 
  * 功能      FM25CL64子程序
  			  void SPI1_init(void);	//初始化SPI
			  u8 SPI1_ReadByte(void);	    //接收字节收字节
			  u8 SPI1_WriteByte(u8 byte);	//发送字节
			  void wren_cmd(void); //写使能
			  void wrdi_cmd(void);//写禁止
			  u8 rdsr_cmd(void);//读状态寄存器
			  void wrsr_cmd(u8 status);//写状态寄存器
			  wrsr_cmd(0x00); //无写保护
			  void wrpara(uint16 reg_addr,uint16 reg_val);//写字节
			  void write_fm2564(void *ram_addr,uint16 len,uint16 fram_addr);//写数据串
			  uint16 read_para(uint16 reg_addr); //读字节
			  void read_fm2564(void *ram_addr,uint16 len,uint16 fram_addr);  //读数据串
			  
  * 日期      2013-6-20
  * 实验平台  XL-VWF-A-V2.0
  * 硬件连接  PA4
              PA5
			  PA6
			  PA7
  */ 
#include "stm32f10x.h"
#include "datatype.h"
#include "SPI1.h"
void SPI1_init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  /*使能GPIOA、SPI1时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_SPI1, ENABLE);
  /*配置GPIOA：PA4推挽输出、PA5、PA6、PA7复用推挽输出，输出频率50MHz*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_4);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /*配置SPI*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						//主模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//8bit
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;						//模式3
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;						//
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//SPI_BaudRatePrescaler_2;//2分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				//高位在前
  SPI_InitStructure.SPI_CRCPolynomial = 7;							
  SPI_Init(SPI1, &SPI_InitStructure);

  SPI_Cmd(SPI1, ENABLE);
}
//接收字节
u8 SPI1_ReadByte(void)
{
	return (SPI1_WriteByte(0xFF));
}
//发送字节
u8 SPI1_WriteByte(u8 byte)	
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, byte);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}
//写使能
void wren_cmd(void)
{
	FLASH_CS_0;
	SPI1_WriteByte(WREN_INST);
	FLASH_CS_1;
}
//写禁止
void wrdi_cmd(void)
{
	FLASH_CS_0;
	SPI1_WriteByte(WRDI_INST);
	FLASH_CS_1;
}
//读状态寄存器
u8 rdsr_cmd(void)
{
	u8 aa; 
	FLASH_CS_0;
	SPI1_WriteByte(RDSR_INST);
	aa = SPI1_ReadByte();
	FLASH_CS_1;
	return aa;
}
//写状态寄存器
void wrsr_cmd(u8 status)
{
	wren_cmd();
	FLASH_CS_0;
	SPI1_WriteByte(WRSR_INST);
	SPI1_WriteByte(status);
	FLASH_CS_1;
}
//写字节
void wrpara(uint16 reg_addr,uint16 reg_val)
{
	wren_cmd();
	FLASH_CS_0;
	SPI1_WriteByte(WRITE_INST);
	SPI1_WriteByte((u8)(reg_addr >> 8));
	SPI1_WriteByte((u8)(reg_addr));
	SPI1_WriteByte(reg_val);
	FLASH_CS_1;	
}
//写数据串
void write_fm2564(void *ram_addr,uint16 len,uint16 fram_addr)
{
    u8 *p;
	u8 i;
	p = ram_addr; 
	wren_cmd();
	FLASH_CS_0;
	SPI1_WriteByte(WRITE_INST);
	SPI1_WriteByte((u8)(fram_addr >> 8));
	SPI1_WriteByte((u8)(fram_addr));
	for(i=0;i<len;i++)
	{
		SPI1_WriteByte(*(p+i));
	}
	FLASH_CS_1;	
}
//读字节
uint16 read_para(uint16 reg_addr)
{
	u8 aa;
	FLASH_CS_0;
	SPI1_WriteByte(READ_INST);
	SPI1_WriteByte((u8)(reg_addr >> 8));
	SPI1_WriteByte((u8)(reg_addr));
	aa = SPI1_ReadByte();
	FLASH_CS_1;
	return aa;
}
//读数据串
void read_fm2564(void *ram_addr,uint16 len,uint16 fram_addr)
{
	u8 *p;
	u8 i;
	p = ram_addr; 
	FLASH_CS_0;
	SPI1_WriteByte(READ_INST);
	SPI1_WriteByte((u8)(fram_addr >> 8));
	SPI1_WriteByte((u8)(fram_addr));
	for(i=0;i<len;i++)
	{
		*(p+i) = SPI1_ReadByte();
	}
	FLASH_CS_1;
}

