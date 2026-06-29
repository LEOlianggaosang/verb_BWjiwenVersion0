/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    Ad.c
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC95F8617_ENABLED
#include "..\SC95F861x_C.H"
#endif
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#endif
#include "Ad.h"

/*
********************************************************************************
**  Global Functions Define
********************************************************************************
*/

/**
 * @brief 初始化AD转化器
 * 
 * @param 无
 * @return 无
 */
void AD_Init( void )
{
	ADCCON = 0;
	//
#ifdef SC95F8617_ENABLED
	ADCCFG0 = 0X0f;
	ADCCFG1 = 0X00;
#endif
#ifdef SC95F8616B_ENABLED
	ADCCFG0 = 0Xf0;
	ADCCFG1 = 0X00;
#endif
	//sample time 32 system clock
	ADCCFG2 = 0X1c;
	
	EADC = 0;
	IPADC = 0;
	// reference value set by option byte, VDD
	
}


/**
 * @brief 启动AD转化器
 * 
 * @param 无
 * @return 无
 */
void AD_Start( void )
{
	//ADC on
	ADCCON |= 0X80;
}

// /**
//  * @brief 将转化的结果保存在buffer指针所指向的地址.
//  * 
//  * @param buffer:要存放转化结果的地址
//  * @return 无
//  */
// void AD_Read( unsigned char* buffer )
// {
// 	*buffer = ADCVH;
// }

/**
 * @brief 停止AD转化
 * 
 * @param 无
 * @return 无
 */
void AD_Stop( void )
{
	ADCCON &= ~0x80;
}

/**
 * @brief 使能比较器操作
 * 
 * @param 无
 * @return 无
 */
void AD_ComparatorOn( void )
{//只有写1有效
	// ADCS on
	ADCCON |= 0X40;
}

// /**
//  * @brief 停止比较器操作
//  * 
//  * @param 无
//  * @return 无
//  */
// void AD_ComparatorOff( void )
// {
// 	// ADCS on
// 	ADCCON &= ~0X40;
// }

/**
 * @brief 选择模拟输入通道
 * 
 * @param channel:模拟输入通道
 * @return 无
 * @brief	每次只能开启一个通道
 */
void AD_SelectADChannel( enum ADChannel channel )
{
	ADCCON &= 0xe0;
	ADCCON |= channel;
	if(channel<8)
	{
		ADCCFG0 = 1<<channel;   //Set channel as the sampling port
	}
	else
	{
		ADCCFG1 = 1<<(channel-8);   //Set channel as the sampling port
	}
	ADCCFG2 = 0X1c;
}
