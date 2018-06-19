#include "stm32f10x_i2c.h"
#include "GPIO.H"
#include "i2c.h"

//缺省初始化
void IIC_Default_Init(unsigned char IICx)
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_StructInit(&I2C_InitStruct);
	I2C_InitStruct.I2C_ClockSpeed = 200000;  //200K,最大是400K

	if(1==IICx)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
		DK_GPIO_Init(PB,GPIO_Pin_6,AF_OD);	//复用开漏输出 
		DK_GPIO_Init(PB,GPIO_Pin_7,AF_OD);	//复用开漏输出 
		
		//I2C_DeInit(I2C1);
		I2C_Init(I2C1, &I2C_InitStruct);
		I2C_Cmd(I2C1,ENABLE);
	}
	if(2==IICx)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
		DK_GPIO_Init(PB,GPIO_Pin_10,AF_OD);	//复用开漏输出 
		DK_GPIO_Init(PB,GPIO_Pin_11,AF_OD);	//复用开漏输出 
		
		I2C_Init(I2C2, &I2C_InitStruct);
		I2C_Cmd(I2C2,ENABLE);
	}
}

static void delay(unsigned short cnt)
{
	while(cnt--);
}
/************************************************************************************
**函 数 名: static void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,unsigned char I2C_Addr)
**功    能: 等待获取I2C总线控制权
**入口参数: I2C_TypeDef *I2Cx,STM32 的I2C 寄存器基址，从器件地址
**         
**出口参数: 无
************************************************************************************/
static  void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,unsigned char I2C_Addr)
{ 
    do{ 
		I2C_GenerateSTART(I2Cx,ENABLE);
        I2C_ReadRegister(I2Cx,I2C_Register_SR1);//清除ADDR位
		I2C_ReadRegister(I2Cx,I2C_Register_SR2);//
        I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Transmitter);
		delay(10);								//发送地址后，不能马上收到ACK，需延时等待。
		
    }while(!(I2C_ReadRegister(I2Cx,I2C_Register_SR1)&0x0002)); 
 
    I2C_ClearFlag(I2Cx,I2C_FLAG_AF);
} 

/************************************************************************************
**函 数 名: 
**功    能: 通过指定I2C接口读取一个字节数据
**入口参数: I2C_TypeDef *I2Cx,STM32 的I2C 寄存器基址，从器件地址,addr 预读取字节存储位置,
			addrLenDwor为1表示存储位置地址宽度大于1个字节，为0则表示1个字节
**         
**出口参数: 读取到的数值
************************************************************************************/
static unsigned char I2C_ReadOneByte(I2C_TypeDef *I2Cx,unsigned char I2C_Addr,unsigned short addr,unsigned char addrLenDword)
{
	unsigned char res=0;
	I2C_AcknowledgePolling(I2Cx,I2C_Addr);
	
	I2C_GenerateSTART(I2Cx, ENABLE);	
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	if(1==addrLenDword)	 //如果器件读写地址超过一个字节
	{
		I2C_SendData(I2Cx,addr>>8);
		while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	I2C_SendData(I2Cx,addr);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2Cx,ENABLE);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));
	res=I2Cx->DR;

	I2C_GenerateSTOP(I2Cx,ENABLE);
	return res;
	
	
}
/************************************************************************************
**函 数 名: 
**功    能: 通过指定I2C接口读取多个字节数据
**入口参数: DK_I2Cx为1表示使用IIC总线1，为2表示是总线2，从器件地址,addr 预读取字节存储位置，
			*buf 读取数据的存储位置，num读取字节数,addrLenDwor为1表示存储位置地址宽度大于1个字节，为0则表示1个字节
**         
**出口参数: 成功返回0
************************************************************************************/
unsigned char I2C_Read(unsigned char DK_I2Cx,unsigned char I2C_Addr,unsigned short addr,unsigned char *buf,unsigned char num,unsigned char addrLenDword)
{
	I2C_TypeDef *I2Cx;

	if(1==DK_I2Cx)	 I2Cx=I2C1;
	else if(2==DK_I2Cx)	 I2Cx=I2C2;
	while(num--)
	{		
		*buf++=I2C_ReadOneByte(I2Cx,I2C_Addr,addr++,addrLenDword);
	}		
	
	return 0;
	
	
}
/************************************************************************************
**函 数 名: 
**功    能: 通过指定I2C接口写入一个字节数据
**入口参数: I2C_TypeDef *I2Cx,STM32 的I2C 寄存器基址，从器件地址,addr 预写入字节地址，value 写入数据
**         	addrLenDwor为1表示存储位置地址宽度大于1个字节，为0则表示1个字节
**出口参数: 成功返回0
************************************************************************************/
static unsigned char I2C_WriteOneByte(I2C_TypeDef *I2Cx,unsigned char I2C_Addr,unsigned short addr,unsigned char value,unsigned char addrLenDword)
{
	
	I2C_AcknowledgePolling(I2Cx,I2C_Addr);
	
	I2C_GenerateSTART(I2Cx, ENABLE);	
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
	
	I2C_Send7bitAddress(I2Cx,I2C_Addr,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	if(1==addrLenDword)	//如果器件读写地址超过一个字节
	{
		I2C_SendData(I2Cx,addr>>8);
		while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}
	I2C_SendData(I2Cx,addr);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2Cx,value);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));	
	
	I2C_GenerateSTOP(I2Cx,ENABLE);

	if(value!=I2C_ReadOneByte(I2Cx,I2C_Addr,addr,addrLenDword))
		return 1;
	return 0;
}
/************************************************************************************
**函 数 名: 
**功    能: 通过指定I2C接口写入多个字节数据
**入口参数: DK_I2Cx为1表示使用IIC总线1，为2表示是总线2，从器件地址,addr 预写入字节地址，*buf 预写入数据存储位置，num写入字节数
**         addrLenDwor为1表示存储位置地址宽度大于1个字节，为0则表示1个字节
**出口参数: 成功返回0
************************************************************************************/
unsigned char I2C_Write(unsigned char DK_I2Cx,unsigned char I2C_Addr,unsigned short addr,unsigned char *buf,unsigned char num,unsigned char addrLenDword)
{
	unsigned char err=0;
	I2C_TypeDef *I2Cx;

	if(1==DK_I2Cx)	 I2Cx=I2C1;
	else if(2==DK_I2Cx)	 I2Cx=I2C2;
	
	while(num--)
	{
		if(I2C_WriteOneByte(I2Cx, I2C_Addr,addr++,*buf++,addrLenDword))
		{
			err++;
		}
	}
	if(err)
		return 1;
	else 
		return 0;	
}

