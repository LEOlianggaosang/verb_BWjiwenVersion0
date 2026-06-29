/**
 *******************************************************************************
 * Copyright (c) 20250423
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
#ifdef SC92F8463B_ENABLED
#include "H/SC92F846XB_C.H"
#endif
#include "Ad.h"
#include "product_config.h"
//bit AdcFlag = 0;
//unsigned int ADCValue = 0x0000;
///*****************************************************
//*函数名称：void ADC_Test(void)
//*函数功能：ADC测试
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void ADC_Test(void)
//{
//	ADC_Init(AIN3,F8);
//	while(1)
//	{
//		ADCValue = ADC_AverageValue();
//	}
//}
///*****************************************************
//*函数名称：void ADC_Init(uint Channel,uchar ADCFreq)
//*函数功能：ADC初始化
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void ADC_Init(uint Channel,uchar ADCFreq)
//{
//	//ADCCON = 0X80|Channel;		//开启ADC，ADC采样频率为2M ,选择Channel位ADC采样口
//	ADCCON = Channel;			//选择Channel位ADC采样口
//	if(Channel<8)
//	{
//		ADCCFG0 = 1<<Channel;   //设置Channel作为采样口
//	}
//	else
//	{
//		ADCCFG1 = 1<<(Channel-8);   //设置Channel作为采样口
//	}
//	//ADCCFG2 = 0X08|ADCFreq;		//36+14fadc
//	ADCCFG2 = ADCFreq;					//6+14fadc
//	//IE |= 0X40;        //开启ADC中断
//	EA = 1;
//}

void AD_Init( void )
{
	ADCCON = 0;
	//
	#if NEWTYPE1
	ADCCFG0 = 0X08;//AIN3
	ADCCFG1 = 0X00;
	#else
	ADCCFG0 = 0X00;
	ADCCFG1 = 0X02;//AIN8,AIN9
	#endif
	//sample time 32 system clock
	ADCCFG2 = 0X07;//6+14fadc//f32/3
	
	EADC = 0;
	IPADC = 0;
	// reference value set by option byte, VDD
}

//unsigned int ADC_AverageValue()
//{
//	int i = 0; 
//	unsigned int ADC_ValueSum = 0, ADC_ValueMax = 0 ,ADC_ValueMin = 0x01 << 12 ,ADC_ValueMean = 0 ,ADC_ValueTad = 0;
//	for(i=0;i<10;i++ )
//	{	
//		ADCCON |= 0X40;   //开始ADC转换
//	  while(!AdcFlag);	         		 //等待 ADC转换完成;
//		AdcFlag = 0;
//		ADC_ValueTad = (ADCVH<<4)+(ADCVL>>4);
//		if(ADC_ValueTad>ADC_ValueMax)
//		{
//		 ADC_ValueMax = ADC_ValueTad;
//		}
//		if(ADC_ValueTad<ADC_ValueMin)
//		{
//		 ADC_ValueMin = ADC_ValueTad;
//		}
//		ADC_ValueSum += ADC_ValueTad;
//	}
//	ADC_ValueMean = (unsigned int)((ADC_ValueSum - ADC_ValueMax - ADC_ValueMin) / 8);
//  return ADC_ValueMean;
//}


//void ADC_Interrupt(void) interrupt 6
//{
//	ADCCON&=~(0X20);  //清中断标志位
//	AdcFlag = 1;
//}


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
/**
 * @brief 将转化的结果保存在buffer指针所指向的地址.
 * 
 * @param buffer:要存放转化结果的地址
 * @return 无
 */
//void AD_Read( unsigned char* buffer )
//{
//	*buffer = ADCVH;
//}

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
{
	// ADCS on
	ADCCON |= 0X40;
}

/**
 * @brief 停止比较器操作
 * 
 * @param 无
 * @return 无
 */
void AD_ComparatorOff( void )
{
	// ADCS on
	ADCCON &= ~0X40;
}

/**
 * @brief 选择模拟输入通道
 * 
 * @param channel:模拟输入通道
 * @return 无
 */
void AD_SelectADChannel( enum Channel name )
{
	ADCCON |= name;
}
