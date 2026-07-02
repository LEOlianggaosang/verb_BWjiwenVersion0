#include "intrins.h"
#include "IAP.h"
#ifdef SC95F8617_ENABLED
#include "..\SC95F861x_C.H"
//#define IapROM  0x00	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
//#define IapEPPROM  0x02	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
static void IAPWrite(unsigned int Addr,unsigned char Value,unsigned char IAPArea);
static void IAPPageErase(unsigned int Addr,unsigned char IAPArea);
static unsigned char IAPRead(unsigned int Addr,unsigned char IAPArea);
unsigned char code *IapAddr = 0x00;
#endif
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#include "IAP_Lib/IAP_Option_EW.h"
// IAP_CodeSectorEraseOption(0xFFFE);			//往CODE 0x1FFFE地址块擦
// IAP_CodeProgramByteOption(0xFFFE, 0x55);			//往CODE 0x1FFFE地址写入0x55
static unsigned char IAPRead(unsigned long Add, unsigned char Iapade);
#endif
static unsigned char uart_CheckSum(unsigned char *puchMsg,unsigned char DataLen);

static unsigned char uart_CheckSum(unsigned char *puchMsg,unsigned char DataLen)
{
    unsigned char i;
    unsigned char CheckSum = 0;
    for(i=0;i<DataLen;i++)
    {
        CheckSum += * puchMsg++;
    }
    return CheckSum;
}

void IAP_eepromSaveData(unsigned char *WByte, unsigned char NumByte)
{
    unsigned char xdata data_buffer[BLOCK_MAX_LENGTH]; 
	unsigned char xdata data_buffer_restore[BLOCK_MAX_LENGTH]; 
    unsigned char i;

	//
	for (i = 0; i<NumByte; i++)
	{
		data_buffer[i] = WByte[i];
	}
	data_buffer[NumByte+1] = uart_CheckSum(data_buffer, NumByte);	
	
	do
	{
		#ifdef SC95F8616B_ENABLED
		IAP_EEPROMSectorEraseOption(IAP_FLASH_START_ADDR);//调用库函数
		#endif
		#ifdef SC95F8617_ENABLED
		IAPPageErase(IAP_FLASH_START_ADDR,IAP_AREA_VALUE);   //???
		#endif
		for (i = 0; i< NumByte; i++)
		{
			#ifdef SC95F8616B_ENABLED
			IAP_EEPROMProgramByteOption(IAP_FLASH_START_ADDR+i, data_buffer[i]);//调用库函数
			#endif
			#ifdef SC95F8617_ENABLED
			IAPWrite(IAP_FLASH_START_ADDR+i,data_buffer[i],IAP_AREA_VALUE);  //??
			#endif
		}
		
		for (i = 0; i< NumByte; i++)
		{
			data_buffer_restore[i] = IAPRead(IAP_FLASH_START_ADDR+i,IAP_AREA_VALUE);
			data_buffer_restore[NumByte] += data_buffer_restore[i];
		}
	}while(data_buffer[NumByte] != data_buffer_restore[NumByte]);
}

void IAP_eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte)
{
		unsigned char i;
		for (i = 0; i< NumByte; i++)
		{
			dataPtr[i] = IAPRead(IAP_FLASH_START_ADDR+i,IAP_AREA_VALUE);
		}	
}
#ifdef SC95F8617_ENABLED
/*****************************************************
*函数名称：void IAPWrite(uchar Addr,uchar Value,uchar IAPArea)
*函数功能：IAP写初始化
*入口参数：Addr,Value,IAPArea
*出口参数：void
*****************************************************/
//IAP写操作
static void IAPWrite(unsigned int Addr,unsigned char Value,unsigned char IAPArea)
{	
    bit temp = EA;
	 EA = 0;
    IAPADE = IAPArea;   //IAPArea=0x00：选择ROM区操作  IAPArea=0x02：选择EEPROM区操作
	IAPDAT = Value;     //写入数据Data
	IAPADH = (unsigned char)((Addr >> 8));   //写入地址的高8位
	IAPADL = (unsigned char)Addr;            //写入地址的低8位
	IAPKEY = 0xF0;		//IAP开启保护控制时间
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
	IAPADE = 0x00;      //MOVC指向ROM
	EA = temp;
}

/*****************************************************
*函数名称：void IAPPageErase(uint Addr,uchar IAPArea)
*函数功能：IAP页擦除
*入口参数：Addr,IAPArea
*出口参数：void
*****************************************************/
static void IAPPageErase(unsigned int Addr,unsigned char IAPArea)
{
	bit temp = EA;
	EA = 0;
	IAPADE = IAPArea;
	
	IAPADH = (unsigned char)((Addr >> 8)); //写入待擦除首地址高位
  IAPADL = (unsigned char)Addr;          //写入待擦除首地址低位
	
	IAPKEY = 0XF0;
	IAPCTL = 0X20;
	IAPCTL |= 0X02;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
  _nop_();
	_nop_();
	_nop_();
	_nop_();
	IAPADE = 0x00;
	EA = temp;		
}
/*****************************************************
*函数名称：uchar IAPRead(uchar Addr,uchar IAPArea)
*函数功能：IAP读初始化
*入口参数：Addr,IAPArea
*出口参数：ReadValue
*****************************************************/
static unsigned char IAPRead(unsigned int Addr,unsigned char IAPArea)
{
	unsigned char ReadValue = 0x00;
   bit temp = EA;
	EA = 0;
	IAPADE = IAPArea;
	ReadValue = *(IapAddr+Addr); //读取的数据
	IAPADE = 0x00;               //MOVC指向ROM
	EA = temp;
	return ReadValue;
}
#endif
#ifdef SC95F8616B_ENABLED
/**************************************************
*函数名称：static unsigned char IAPRead(unsigned long Add,unsigned char ADER)
*函数功能：单Byte读取
*入口参数：Add ：需要擦除的地址(0X00~0X1FFFF（FLASH物理地址）
*         Data：要写入的Byte,ADER:操作对象 APROM为00,EEPROM为02
*出口参数：void
**************************************************/
unsigned char IAPRead(unsigned long Add, unsigned char Iapade)
{
  unsigned char IAP_IapData;
  //保存ROMBNK、IAPADE、EA
  unsigned char tempADER = IAPADE;
  unsigned char tempEA = EA;

  unsigned char code* point = 0;

  EA = 0;//关闭中断

  IAPADE = Iapade;

  IAP_IapData = *(point + Add);

  //操作结束恢复ROMBNK、IAPADE、EA，避免MOVC位置出错
  IAPADE = tempADER;
  EA = tempEA;

  return IAP_IapData;
}
#endif
