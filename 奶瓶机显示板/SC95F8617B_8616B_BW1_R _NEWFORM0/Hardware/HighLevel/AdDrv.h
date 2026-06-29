/**
 *******************************************************************************
 * Copyright (c) 2025.4.9
 *  
 * @file    AdDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _AD_DRV_H_
#define _AD_DRV_H_

#include "Hardware_Config.h"

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
typedef enum
{
	TDS_2,//PIN21_P35_AIN9//tds2AD检测纯水
	TEMPERATURE_2,//PIN32_P17_AIN3//ntc2AD检测纯水温
	TDS_1,//PIN36_P23_AIN7//tds1AD检测原水
	TEMPERATURE_1,//PIN35_P22_AIN6//ntc1AD检测原水温
	//OVERFLAOW,
	//PIN15_P43_AIN15//PUMP2_AD(预留)
	//PIN22_P34_AIN8//PUMP1_AD(预留)
	ADC_END
}eADCChannelName;

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void Init_Ad( void );
// void singleSample(eADCChannelName channel,unsigned char* buffer);
void singleSample(eADCChannelName channel,unsigned int* buffer);
// unsigned char ADC_AverageValue(unsigned char* ADC_Tem);
unsigned int ADC_AverageValue(unsigned int* ADC_Tem);

#endif //_AD_DRV_H_
