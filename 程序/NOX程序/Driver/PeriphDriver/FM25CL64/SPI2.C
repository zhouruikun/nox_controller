/**
  ******************************************************************************
  * 文件名  SPI2.c 
  * 功能    AT45DB041子程序
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

			// buffer  缓存器选择，0x01选择缓存器1，0x02选择缓存器2，
			// PA  页地址，0 - 2047
			// BFA BUFFER中的起始写入地址
			// prt 数据的首地址
			// len 数据的长度

  * 日期      2013-7-9
  * 实验平台  XL-VWF-A-V2.0
  * 硬件连接  PB12
              PB13
			  PB14
			  PB15
  */ 
#include "stm32f10x.h"
#include "datatype.h"
#include "SPI2.h"
void Delay1(void);


 void ES_RSR(u8 *ptr) //读扇区信息
{
    u8 i;
    AT_CS_0;
    SPI2_WriteByte(0x35);
    SPI2_WriteByte(0x00);
    SPI2_WriteByte(0x00);
    SPI2_WriteByte(0x00);
    for(i=0;i<8;i++)
    {
            *(ptr+i) = SPI2_ReadByte();
    }
    AT_CS_1;
}


void SPI2_init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  /*使能GPIOB、SPI2时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  /*配置GPIOB：PB12推挽输出、PB13、PB14、PB15复用推挽输出，输出频率50MHz*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_12);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*配置SPI*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						//主模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//8bit
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;						//模式3
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;						//
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//2分频
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				//高位在前
  SPI_InitStructure.SPI_CRCPolynomial = 7;							
  SPI_Init(SPI2, &SPI_InitStructure);

  SPI_Cmd(SPI2, ENABLE);
}
//接收字节
u8 SPI2_ReadByte(void)
{
	return (SPI2_WriteByte(0xFF));
}
//发送字节
u8 SPI2_WriteByte(u8 byte)	
{
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2, byte);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI2);
}
//读状态寄存器
u8 AT_RSR(void)
{
	u8 i;
	AT_CS_0;
	SPI2_WriteByte(0xd7);  //0XDf	//0xd7
	i = SPI2_ReadByte();
	AT_CS_1;
	return i;
}


// 数据写入缓存器	 操作码：0x84 缓存1；操作码：0x87 缓存2
// buffer  缓存器选择，0x01选择缓存器1，0x02选择缓存器2，
// BFA BUFFER中的起始写入地址
// prt 数据的首地址
// len 数据的长度
void AT_bwrite(u8 buffer,u16 BFA,u8 *ptr,u16 len)
{
	u16 i=0;
	while(i < 30000)
	{
		i++;
		if(AT_RSR() & 0x80)
		{
			break;
		}	
	}
	AT_CS_0;
	switch(buffer)
	{
		case 1: SPI2_WriteByte(0X84);break;
		case 2: SPI2_WriteByte(0X87);break;
		default:SPI2_WriteByte(0X87);break;
	}
	SPI2_WriteByte(0X00);
	SPI2_WriteByte((u8)(BFA >> 8));
	SPI2_WriteByte((u8)BFA);
	for(i=0;i<len;i++)
	{
		SPI2_WriteByte(*(ptr+i));
	}
	AT_CS_1;
}

// 缓存器上数据写入主内存（带预擦除）	 
// 操作码：0x83 缓存1；操作码：0x86 缓存2
// buffer  缓存器选择，0x01选择缓存器1，0x02选择缓存器2，
// PA  页地址，0 - 2047
void buffer_array(u8 buffer,u16 PA)
{
	u16 i=0;
	while(i < 2000)
	{
		i++;
		if(AT_RSR() & 0x80)
		{
			break;
		}	
	}
	AT_CS_0;
	switch(buffer)
	{
		case 1: SPI2_WriteByte(0X83);break;
		case 2: SPI2_WriteByte(0X86);break;
		default:SPI2_WriteByte(0X86);break;
	}
	SPI2_WriteByte((u8)(PA >> 7));
	SPI2_WriteByte((u8)(PA << 1));
	SPI2_WriteByte(0X00);
	AT_CS_1;
}

// 数据先写入缓存器，再将缓存器上数据写入主内存（带预擦除）	 
// 操作码：0x83 缓存1；操作码：0x86 缓存2
// buffer  缓存器选择，0x01选择缓存器1，0x02选择缓存器2，
// PA  页地址，0 - 2047
// BFA BUFFER中的起始写入地址
// prt 数据的首地址
// len 数据的长度
void write_array(u8 buffer,u16 PA,u16 BFA,u8 *ptr,u16 len)
{
	u16 i=0;
	AT_bwrite(buffer,BFA,ptr,len);
	while(i < 2000)
	{
		i++;
		if(AT_RSR() & 0x80)
		{
			break;
		}	
	}
	AT_CS_0;
	switch(buffer)
	{
		case 1: SPI2_WriteByte(0X83);break;
		case 2: SPI2_WriteByte(0X86);break;
		default:SPI2_WriteByte(0X86);break;
	}
	SPI2_WriteByte((u8)(PA >> 7));
	SPI2_WriteByte((u8)(PA << 1));
	SPI2_WriteByte(0X00);
	AT_CS_1;
}

// 数据先写入缓存器，再将缓存器上数据写入主内存（不带预擦除）	 
// 操作码：0x88 缓存1；操作码：0x89 缓存2
// buffer  缓存器选择，0x01选择缓存器1，0x02选择缓存器2，
// PA  页地址，0 - 2047
// BFA BUFFER中的起始写入地址
// prt 数据的首地址
// len 数据的长度
void write_array_no(u8 buffer,u16 PA,u16 BFA,u8 *ptr,u16 len)
{
	u16 i=0;
	AT_bwrite(buffer,BFA,ptr,len);
	while(i < 2000)
	{
		i++;
		if(AT_RSR() & 0x80)
		{
			break;
		}	
	}
	AT_CS_0;
	switch(buffer)
	{
		case 1: SPI2_WriteByte(0X88);break;
		case 2: SPI2_WriteByte(0X88);break;
		default:SPI2_WriteByte(0X89);break;
	}
	SPI2_WriteByte((u8)(PA >> 7));
	SPI2_WriteByte((u8)(PA << 1));
	SPI2_WriteByte(0X00);
//	for(i=0;i<len;i++)
//	{
//		SPI2_WriteByte(*(ptr+i));
//	}
	AT_CS_1;
}

// 从主内存读数据串	 操作码：0x52
// PA  页地址，0 - 2047
// BFA BUFFER中的起始写入地址
// prt 数据的首地址
// len 数据的长度
void read_array(u16 PA,u16 BFA,u8 *ptr,u16 len)
{
	u16 i=0;
	while(i < 2000)	 //255
	{
		i++;
		if(AT_RSR() & 0x80)
		{
			break;
		}	
	}
	AT_CS_0;
	SPI2_WriteByte(0XD2);
	SPI2_WriteByte((u8)(PA >> 7));
	SPI2_WriteByte((u8)((PA << 1) | (BFA >> 8)));
	SPI2_WriteByte((u8)BFA);
	for(i=0;i<4;i++)
	{
		SPI2_WriteByte(0x00);	
	}
	for(i=0;i<len;i++)
	{
		*(ptr+i) = SPI2_ReadByte();
	}
	AT_CS_1;
}
//
// PA  页地址，0 - 2047   共89个花板
//pattno 花板号
void read_from_flash(uint8 pattno,uint8 *prg_buf)
{
	u8  PA;
	u8 i;
	PA = pattno * 23;
	for(i=0;i<12;i++)
	{
		read_array(PA,0,prg_buf,264);
		prg_buf = prg_buf + 264;
		PA++;
	}

	for(i=12;i<23;i++)
	{
		read_array(PA,0,prg_buf,264);
		prg_buf = prg_buf + 264;
		PA++;
	}		
}

void write_to_flash(uint8 pattno,uint8 *prg_buf)
{
	u8  PA;
	u8 i;

	PA = pattno * 23;
	for(i=0;i<12;i++)
	{
		write_array(1,PA,0,prg_buf,264);
		prg_buf = prg_buf + 264;
		PA++;
	}

	for(i=12;i<23;i++)
	{
		write_array(1,PA,0,prg_buf,264);
		prg_buf = prg_buf + 264;
		PA++;
	}
}


