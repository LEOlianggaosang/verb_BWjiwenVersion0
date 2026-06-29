#ifdef SC92F8463B_ENABLED
#include "SC92F846XB_C.H"
#endif
#include "intrins.h"
#include "IAP.h"



static void IAPWrite(unsigned int Addr,unsigned char Value,unsigned char IAPArea);
//static void IAPPageErase(unsigned int Addr,unsigned char IAPArea);
static unsigned char IAPRead(unsigned int Addr,unsigned char IAPArea);
unsigned char code *IapAddr = 0x00;

//static unsigned char uart_CheckSum(unsigned char *puchMsg,unsigned char DataLen)
//{
//    unsigned char xdata i;
//    unsigned char xdata CheckSum = 0;
//    for(i=0;i<DataLen;i++)
//    {
//        CheckSum += * puchMsg++;
//    }
//    return CheckSum;
//}
//void IAP_eepromSaveData(unsigned char *WByte, unsigned char NumByte)
//{
//    unsigned char xdata data_buffer[BLOCK_LENGTH+1]; 
//	 unsigned char xdata data_buffer_restore[BLOCK_LENGTH+1]; 
//    unsigned char xdata i;

//	//
//	for (i = 0; i<NumByte; i++)
//	{
//		data_buffer[i] = WByte[i];
//	}
//	data_buffer[BLOCK_LENGTH] = uart_CheckSum(data_buffer, BLOCK_LENGTH);	
//	
//	do
//	{
//		IAPPageErase(IAP_FLASH_START_ADDR,IAP_AREA_VALUE);   //
//		for (i = 0; i< (BLOCK_LENGTH+1); i++)
//		{
//			
//			IAPWrite(IAP_FLASH_START_ADDR+i,data_buffer[i],IAP_AREA_VALUE);  //
//		}
//		
//		for (i = 0; i< (BLOCK_LENGTH+1); i++)
//		{
//			data_buffer_restore[i] = IAPRead(IAP_FLASH_START_ADDR+i,IAP_AREA_VALUE);
//		}
//	}while(data_buffer[BLOCK_LENGTH] != data_buffer_restore[BLOCK_LENGTH]);
//}
unsigned char IAP_eepromSaveData(unsigned char *WByte, unsigned char NumByte)
{
    unsigned char data_buffer[BLOCK_LENGTH]; 
		unsigned char data_buffer_restore[BLOCK_LENGTH]; 
    unsigned char i;
		unsigned char result;
	//
	result = 0;
	for (i = 0; i<NumByte; i++)
	{
		data_buffer[i] = WByte[i];
	}
	//data_buffer[BLOCK_LENGTH-1] = uart_CheckSum(data_buffer, BLOCK_LENGTH-1);	
	//IAPPageErase(IAP_FLASH_START_ADDR,IAP_AREA_VALUE);   //
	for (i = 0; i< (BLOCK_LENGTH); i++)
	{	
		IAPWrite(IAP_FLASH_START_ADDR+i,data_buffer[i],IAP_AREA_VALUE);  //
		data_buffer_restore[i] = IAPRead(IAP_FLASH_START_ADDR+i,IAP_AREA_VALUE);
		if(data_buffer[i] != data_buffer_restore[i])
		{
			result = 1;
		}
		else
		{
			result = 0;
		}
	}
	return result;
}

void IAP_eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte)
{
		unsigned char i;
		for (i = 0; i< NumByte; i++)
		{
			dataPtr[i] = IAPRead(IAP_FLASH_START_ADDR+i,IAP_AREA_VALUE);
		}	
}

//******************************************************************************

/*****************************************************
*函数名称：void IAPWrite(uchar Addr,uchar Value,uchar IAPArea)
*函数功能：IAP写初始化
*入口参数：Addr,Value,IAPArea
*出口参数：void
*****************************************************/
//IAP写操作
static void IAPWrite(unsigned int Addr,unsigned char Value,unsigned char IAPArea)
{	
	unsigned char 	tempADER = IAPADE;
  bit temp = EA;
	
	EA = 0;
  IAPADE = IAPArea;   //IAPArea=0x00：选择ROM区操作  IAPArea=0x02：选择EEPROM区操作
	IAPDAT = Value;     //写入数据Data
	IAPADH = (unsigned char)((Addr >> 8));   //写入地址的高8位
	IAPADL = (unsigned char)Addr;            //写入地址的低8位
	IAPKEY = 0x40;		//IAP开启保护控制时间
  IAPCTL = 0X10;      //执行“写入或快擦除操作命令”后，进入flash编程操作
	IAPCTL |= 0x02;     //执行“写入或快擦除操作命令”
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  IAPADE = tempADER;
	EA = temp;
}
///**************************************************
//*函数名称:void IAP_ProgramByte(unsigned long Address, unsigned char Data, unsigned char IAP_MemType)
//*函数功能:IAP写入一个字节
//*入口参数:
//unsigned long:Address:IAP操作地址
//unsigned char:Data:写入的数据
//unsigned char:IAP_MemType:IAP操作对象
//*出口参数:void
//**************************************************/
//void IAP_ProgramByte(unsigned long Address, unsigned char Data, unsigned char IAP_MemType)
//{
//  unsigned char tempADER = IAPADE;
//  bit temp = EA;
//  EA = 0;
//  IAPADE = IAP_MemType;
//  IAPDAT = Data;
//  IAPADH = (unsigned char)(Address >> 8);
//  IAPADL = (unsigned char)Address;
//  IAPKEY = 0x40;
//  IAPCTL = 0x10;
//  IAPCTL |= 0x02;
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  IAPADE = tempADER;
//  EA = temp;
//}

//******************************************************************************

///*****************************************************
//*函数名称：void IAPPageErase(uint Addr,uchar IAPArea)
//*函数功能：IAP页擦除
//*入口参数：Addr,IAPArea
//*出口参数：void
//*****************************************************/
//static void IAPPageErase(unsigned int Addr,unsigned char IAPArea)
//{
//	unsigned char xdata tempADER = IAPADE;
//	bit temp = EA;
//	EA = 0;
//	IAPADE = IAPArea;
//	
//	IAPADH = (unsigned char)((Addr >> 8)); //写入待擦除首地址高位
//  IAPADL = (unsigned char)Addr;          //写入待擦除首地址低位
//	
//  IAPKEY = 0x40;
//  IAPCTL = 0x20;
//  IAPCTL |= 0x02;
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  IAPADE = tempADER;
//  EA = temp;	
//}
///**************************************************
//*函数名称:void IAP_SectorErase(unsigned char IAP_MemType, unsigned long IAP_SectorEraseAddress)
//*函数功能:IAP扇区擦除
//*入口参数:
//unsigned char:IAP_MemType:IAP操作对象
//unsigned long:IAP_SectorEraseAddress:IAP扇区擦除目标地址
//*出口参数:void
//**************************************************/
//void IAP_SectorErase(unsigned char IAP_MemType, unsigned long IAP_SectorEraseAddress)
//{
//  unsigned char tempADER = IAPADE;
//  bit temp = EA;
//  EA = 0;
//  IAPADE = IAP_MemType;
//  IAPADH = (unsigned char)(IAP_SectorEraseAddress >> 8); //擦除IAP目标地址高位值
//  IAPADL = (unsigned char)IAP_SectorEraseAddress;        //擦除IAP目标地址低位值
//  IAPKEY = 0x40;
//  IAPCTL = 0x20;
//  IAPCTL |= 0x02;
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  IAPADE = tempADER;
//  EA = temp;
//}

//******************************************************************************

/*****************************************************
*函数名称：uchar IAPRead(uchar Addr,uchar IAPArea)
*函数功能：IAP读初始化
*入口参数：Addr,IAPArea
*出口参数：ReadValue
*****************************************************/

static unsigned char IAPRead(unsigned int Addr,unsigned char IAPArea)
{
	unsigned char xdata ReadValue = 0x00;
   bit temp = EA;
  //保存ROMBNK、IAPADE、EA
  unsigned char tempADER = IAPADE;
	EA = 0;
	IAPADE = IAPArea;
	ReadValue = *(IapAddr+Addr); //读取的数据
  //操作结束恢复ROMBNK、IAPADE、EA，避免MOVC位置出错
  IAPADE = tempADER;
	EA = temp;
	return ReadValue;
}

///**************************************************
//*函数名称：unsigned char IAP_Read(unsigned long IAP_IapAddr, unsigned char area)
//*函数功能：单Byte读取
//*入口参数：
//IAP_IapAddr:需要擦除的地址
//area:操作对象,APROM为00,EEPROM为02
//*出口参数：void
//**************************************************/
//unsigned char IAP_Read(unsigned long IAP_IapAddr, unsigned char area)
//{
//  unsigned char IAP_IapData;
//  //保存ROMBNK、IAPADE、EA
//  unsigned char tempADER = IAPADE;
//  bit temp = EA;

//  EA = 0;             //关闭中断
//  IAPADE = area;
//  IAP_IapData = *(POINT + IAP_IapAddr);

//  //操作结束恢复ROMBNK、IAPADE、EA，避免MOVC位置出错
//  IAPADE = tempADER;
//  EA = temp;
//  return IAP_IapData;
//}

//******************************************************************************

//unsigned char IAP_Read(unsigned long IAP_IapAddr, unsigned char area);
//void IAP_SectorErase(unsigned char IAP_MemType, unsigned long IAP_SectorEraseAddress);
//void IAP_ProgramByte(unsigned long Address, unsigned char Data, unsigned char IAP_MemType);

//void IAP_Test(void)
//{
//  unsigned char IapReadData1, IapReadData2;				//定义储存读出数据的变量

//  IAP_SectorErase(IAP_APROM, 0x7EFF);    		      //扇区擦除
//  IAP_ProgramByte(0x7EFF, 0x55, IAP_APROM);			//往APROM 0x7EFF地址写入0x55
//  IapReadData1 = IAP_Read(0x7EFF, IAP_APROM);	  //读取APROM 0x7EFF地址数据

//  IAP_SectorErase(IAP_EEPROM, 0x70);    		      //扇区擦除
//  IAP_ProgramByte(0x70, 0xAA, IAP_EEPROM);			//往EEPROM 0x70地址写入0xAA
//  IapReadData2 = IAP_Read(0x70, IAP_EEPROM);		//读取EEPROM 0x70地址数据
//  while(1)
//  {
//    if((IapReadData1 == 0x55) && (IapReadData2 == 0xAA))
//    {
//      P00 = ~P00;
//    }
//    else
//    {
//      P01 = ~P01;
//    }
//  }
//}