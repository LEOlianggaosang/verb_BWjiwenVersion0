/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    Ad.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _AD_
#define _AD_
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
//enum ADChannel { ADCHANNEL0, ADCHANNEL1, ADCHANNEL2, 
//								 ADCHANNEL3, ADCHANNEL4, ADCHANNEL5, 
//								 ADCHANNEL6, ADCHANNEL7, ADCHANNEL8,
//								 ADCHANNEL9};
/***********ADC采样频率选择*************/
enum ADCFreq {F32=0,F24,F16,F12,F8,F6,F4,F3};

/***********ADC采样口选择*************/
#ifdef SC92F8463B_ENABLED
enum Channel {AIN0=0,AIN1,AIN2,AIN3,AIN4,AIN5,AIN6,AIN7,AIN8,AIN9,VDD4=31};
#endif

#ifdef SC92F8462B_ENABLED
enum Channel {AIN2=2,AIN3,AIN4,AIN5,AIN8=8,AIN9,VDD4=31};
#endif

#ifdef SC92F8461B_ENABLED
enum Channel {AIN2=2,AIN3,AIN4,AIN8=8,AIN9,VDD4=31};
#endif

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void AD_Init(void);
//void ADC_Init(uint Channel,uchar ADCFreq);
//unsigned int ADC_AverageValue(void);
void AD_Start( void );
//void AD_Read( unsigned char*  buffer );
void AD_Stop( void );
void AD_ComparatorOn( void );
void AD_ComparatorOff( void );
void AD_SelectADChannel( enum Channel name );

//typedef struct 
//{
//    /* data */
//    enum Channel name;
//}ADC_InitTypeDef;

#endif
