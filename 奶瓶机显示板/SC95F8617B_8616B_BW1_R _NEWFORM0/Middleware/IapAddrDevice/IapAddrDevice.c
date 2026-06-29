/**
 *******************************************************************************
 * Copyright (c) 2025.4.7
 * 
 * @file    IapAddrDevice.c
 * @author  lianggaosang@qq.com
 * @brief   循环使用EEPROM空间模块//20250403 SOC
 *
 *******************************************************************************
 */
 
/*
 *------------------------------------------------------------------------------
 * include
 *------------------------------------------------------------------------------
 */
#include "IapAddrDevice.h"
#include "IAP_Lib/IAP_Option_EW.h"
#if CONFIG_IAPADDR_DEVICE	
/**------------------------------------------------------------------------------
 * global
 *------------------------------------------------------------------------------
 */
/* Variables define-------------------------------------------------- */
UCHAR_XDATA IapSectorCnt = 0;
/*
 *------------------------------------------------------------------------------
 * static
 *------------------------------------------------------------------------------
 */
/* static void define------------------------------------------------------- */
static unsigned char Iap_Address_Device_Init(void);
static void Device_Iap_Erase(unsigned int Add);//底层擦接口
static void Device_Iap_Write(unsigned int Add,unsigned char Date);//底层写接口
static unsigned char Device_Iap_Read(unsigned int Add,unsigned char ADER);//底层读接口
/**
 *------------------------------------------------------------------------------
 * Function
 *------------------------------------------------------------------------------
 */
void IapAddrDevice_Init(void)
{
	IapSectorCnt = Iap_Address_Device_Init();//获取掉电前扇区计数
}

void Iap_Address_Device_Write(unsigned char *WByte, unsigned char NumByte)
{
	unsigned char i = 0;
	unsigned int addrbuf = 0;
	unsigned char xdata data_buffer[BLOCK_MAX_LENGTH]; //33
	unsigned char xdata data_buffer_restore[BLOCK_MAX_LENGTH]; //33
	unsigned char add = 0;//20251206
	
	data_buffer[NumByte] = 0;//20251206
	for (i = 0; i<NumByte; i++)
	{
		data_buffer[i] = WByte[i];//31
		data_buffer[NumByte] += data_buffer[i];//32
	}

	add = 0;//20251206

	do
	{
		if(add)
		{//20251206 只有写校验不通过才会增加选区数，并且擦除损坏选区，重置看门狗

			WDTCON |= 0x10;//20251206 清看

			Device_Iap_Erase(addrbuf);

			if(++IapSectorCnt >= IAP_SECTOR_NUM)
			{
				IapSectorCnt = 0;
				break;
			}
		}

		addrbuf = IAP_START_ADDRESS + IAP_SECTOR_SIZE*IapSectorCnt;//20251206 

		Device_Iap_Erase(addrbuf);//擦除数据区块

		for (i = 0; i<NumByte; i++)
		{
			Device_Iap_Write((addrbuf+i),WByte[i]);//写入数据
		}

		WDTCON |= 0x10;//20251206 清看

		data_buffer_restore[NumByte] = 0;//20251206
		for (i = 0; i<NumByte; i++)
		{//写完马上读
			data_buffer_restore[i] = IAPRead(addrbuf+i,IAP_AREA_VALUE);//20251206
			data_buffer_restore[NumByte] += data_buffer_restore[i];
		}

		add = 1;

	}while(data_buffer[NumByte] != data_buffer_restore[NumByte]);
}

void Iap_Address_Device_Read(unsigned char *WByte, unsigned char NumByte)
{
	static unsigned char i = 0;
	static unsigned int addrbuf;//返回值读写区块起始地址

	addrbuf = IAP_START_ADDRESS + IAP_SECTOR_SIZE*IapSectorCnt;//20251206 
	for(i=0;i<NumByte;i++)
	{
		WByte[i] = Device_Iap_Read((addrbuf+i),IAP_REMEBER_LOCETION);//读取数据
	}
}

/**
 *------------------------------------------------------------------------------
 * private
 *------------------------------------------------------------------------------
 */

static unsigned char Iap_Address_Device_Init(void)
{//每次上电执行一次，获取掉电前扇区计数
	static unsigned char i,ret= 0;
	static unsigned char buf1,buf2= 0;//20251206
	static unsigned int addrbuf = 0;
	//根据写记忆格式查找当前扇区计数
	for(i=0;i<=IAP_SECTOR_NUM;i++)
	{//检索写过区域
		ret = i;
		addrbuf = IAP_START_ADDRESS + IAP_SECTOR_SIZE*i;
		buf1 = Device_Iap_Read((addrbuf+2),IAP_REMEBER_LOCETION);//20251206
		buf2 = Device_Iap_Read((addrbuf+3),IAP_REMEBER_LOCETION);//20251206
		if((0xa0 == buf1)&&(0xb0 == buf2))//20251206
		{//获取读计数
			return ret;//20251206 获取读计数
		}
	}
	Device_Iap_Erase(IAP_START_ADDRESS);//20251206 保证读无效时恢复成默认值
	return 0;//20251206 存储区为空或全损坏
}

static void Device_Iap_Erase(unsigned int Add)
{
	#ifdef SC95F8616B_ENABLED
	IAP_EEPROMSectorEraseOption(Add);//调用库函数
	#endif
}

static void Device_Iap_Write(unsigned int Add,unsigned char Date)
{
	#ifdef SC95F8616B_ENABLED
	IAP_EEPROMProgramByteOption(Add,Date);//调用库函数
	#endif
}
static unsigned char Device_Iap_Read(unsigned int Add,unsigned char ADER)
{
	unsigned char ret;
	unsigned long addr;
	addr = (unsigned long)Add;
	#ifdef SC95F8616B_ENABLED
	ret = IAPRead(addr,ADER);//"IAP.h"
	#endif
	return ret;
}

#endif

