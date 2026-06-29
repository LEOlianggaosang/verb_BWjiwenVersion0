/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    AdDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _AD_DRV_H_
#define _AD_DRV_H_
#include "product_config.h"
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
typedef enum
{
	#if NEWTYPE1
	AIN3_NTC = 3, //PIN15_P25_NTC//AIN3
	#else
	AIN9_NTC = 9, //PIN09_P14_NTC//AIN9,
	#endif
	ADC_END
}eADCChannelName;

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
unsigned char ADC_AverageValue(unsigned char* ADC_Tem);
void InitAd( void );
void singleSample(eADCChannelName channel,unsigned char* buffer);//void singleSample(eADCChannelName channel,unsigned short* buffer)
#endif //_AD_DRV_H_
