/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    AdDrv.c
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
#include "Hardware_Config.h"
#include "AdDrv.h"

#ifdef SC92F8463B_ENABLED
#include "intrins.h"
//ADC_InitTypeDef xdata tAdcs[ADC_END] = {ADCHANNEL9};

void InitAd( void )
{
  AD_Init();
}

void singleSample(eADCChannelName channel,unsigned char* buffer)
{
	unsigned short buf;
	AD_Start();
	
  AD_SelectADChannel(channel);
	ADCCON &= ~0x20;
  AD_ComparatorOn();
	
  _nop_();
  _nop_();
  while (!(ADCCON&0X20))
  {
    ;
  }
  //(*buffer) += ADCVH;
	//(*buffer) += (ADCVH<<4)+(ADCVL>>4);
	buf = (((ADCVH<<4)+(ADCVL>>4))>>4);
	(*buffer) = (unsigned char)buf;//20240705
  _nop_();

  AD_Stop();
}


unsigned char ADC_AverageValue(unsigned char* ADC_Tem)
{
	int i = 0; 
	unsigned int ADC_ValueSum = 0;
	unsigned char ADC_ValueMax = 0 ,ADC_ValueMin = 0xff ,ADC_ValueMean = 0 ;
	for(i=0;i<18;i++ )
	{	
		if(ADC_Tem[i]>ADC_ValueMax)
		{
		 ADC_ValueMax = ADC_Tem[i];
		}
		if(ADC_Tem[i]<ADC_ValueMin)
		{
		 ADC_ValueMin = ADC_Tem[i];
		}
		ADC_ValueSum += ADC_Tem[i];
	}
	ADC_ValueMean = (unsigned char)((ADC_ValueSum - ADC_ValueMax - ADC_ValueMin) / 16);
  return ADC_ValueMean;
}
#endif
