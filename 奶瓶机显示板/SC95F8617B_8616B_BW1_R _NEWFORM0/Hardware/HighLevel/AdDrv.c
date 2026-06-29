/**
 *******************************************************************************
 * Copyright (c) 2025.4.9
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
#include "AdDrv.h"
#include "intrins.h"
#ifdef	SC95F8617_ENABLED
ADC_InitTypeDef xdata tAdcs[ADC_END] = {ADCHANNEL0, ADCHANNEL1, ADCHANNEL2, ADCHANNEL3, /*ADCHANNEL11*/};
#endif
#ifdef	SC95F8616B_ENABLED
	#if NEWTYPE0
		ADC_InitTypeDef xdata tAdcs[ADC_END] = {ADCHANNEL9, ADCHANNEL3, ADCHANNEL7, ADCHANNEL6,};
	#else
		ADC_InitTypeDef xdata tAdcs[ADC_END] = {ADCHANNEL5, ADCHANNEL4, ADCHANNEL7, ADCHANNEL6,};
	#endif
#endif
void Init_Ad( void )
{
  AD_Init();
}

// void singleSample(eADCChannelName channel,unsigned char* buffer)
// {
// 	unsigned short buf;
// 	AD_Start();
	
//   AD_SelectADChannel(channel);
// 	ADCCON &= ~0x20;
//   AD_ComparatorOn();
	
//   _nop_();
//   _nop_();
//   while (!(ADCCON&0X20))
//   {
//     ;
//   }
//   //(*buffer) += ADCVH;
// 	//(*buffer) += (ADCVH<<4)+(ADCVL>>4);
// 	buf = (((ADCVH<<4)+(ADCVL>>4))>>4);
// 	(*buffer) = (unsigned char)buf;//20240705
//   _nop_();

//   AD_Stop();
// }
void singleSample(eADCChannelName channel,unsigned int* buffer)
{//调试用int版本
	AD_Start();
	
  AD_SelectADChannel(tAdcs[channel].name);
	ADCCON &= ~0x20;
  AD_ComparatorOn();
	
  _nop_();
  _nop_();
  while (!(ADCCON&0X20))
  {
    ;
  }

	(*buffer) = (unsigned int)((ADCVH<<4)+(ADCVL>>4));
  _nop_();

 AD_Stop();
}


// unsigned char ADC_AverageValue(unsigned char* ADC_Tem)
// {
// 	unsigned char i = 0; 
// 	unsigned int ADC_ValueSum = 0;
// 	unsigned char ADC_ValueMax = 0 ,ADC_ValueMin = 0xff,ADC_ValueMean = 0 ;
// 	for(i=0;i<18;i++ )
// 	{	
// 		if(ADC_Tem[i]>ADC_ValueMax)
// 		{
// 		 ADC_ValueMax = ADC_Tem[i];
// 		}
// 		if(ADC_Tem[i]<ADC_ValueMin)
// 		{
// 		 ADC_ValueMin = ADC_Tem[i];
// 		}
// 		ADC_ValueSum += ADC_Tem[i];
// 	}
// 	ADC_ValueMean = (unsigned char)((ADC_ValueSum - ADC_ValueMax - ADC_ValueMin) / 16);
//   return ADC_ValueMean;
// }
unsigned int ADC_AverageValue(unsigned int* ADC_Tem)
{//调试用int版本
	unsigned char i = 0; 
	unsigned int ADC_ValueSum = 0;
	unsigned int ADC_ValueMax = 0 ,ADC_ValueMin = (0x01 << 12) ,ADC_ValueMean = 0 ;
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
	ADC_ValueMean = (unsigned int)((ADC_ValueSum - ADC_ValueMax - ADC_ValueMin) / 16);
  return ADC_ValueMean;
}


