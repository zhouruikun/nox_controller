 
#include "DataFlash.h"
#include "AT24C02.h"
u8 para_buff[256]={0};
 //初始化读出所有参数模拟24c02
void AT24C02_Init(void)
{
	//
	 	Flash_Read(FLASH_PAGE_SIZE*50,(u8 *)para_buff,sizeof(para_buff));
			//FLASH_PAGE_SIZE就是页大小，128Kflash以下容量单片机是1K每页  以上是2K每页 乘50的意思就是在50K的地址上读写数据
}


/************************************************************************************
**功    能:  写入16位的一个数据
**入口参数:  WriteAddr写入地址     val要写入的数据
**出口参数: 成功返回0
************************************************************************************/
uint16 AT24c02WriteDouble(uint16 WriteAddr, uint16 val)
{
    uint8  err=0;
		para_buff[WriteAddr]=val/256;
		para_buff[WriteAddr+1]=val%256;
		Flash_Write(FLASH_PAGE_SIZE*50,(u8 *)para_buff,sizeof(para_buff));
    return err;
    
}

/************************************************************************************
**功    能:  读取16位的一个数据
**入口参数: ReadAddr读取地址     
**出口参数: 成功返回读取数据
************************************************************************************/
uint16 AT24c02ReadDouble(uint16 ReadAddr)
{
 
    uint16 temp;
		temp=(para_buff[ReadAddr]<<8)|(para_buff[ReadAddr+1]);
    return temp;
    
}
