/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    Ad.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _MDAD_
#define _MDAD_

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
enum ADChannel { ADCHANNEL0, ADCHANNEL1, ADCHANNEL2, ADCHANNEL3,
								 ADCHANNEL4, ADCHANNEL5, ADCHANNEL6, ADCHANNEL7, 
								 ADCHANNEL8, ADCHANNEL9, ADCHANNEL10,ADCHANNEL11,
								 ADCHANNEL12,ADCHANNEL13,ADCHANNEL14,ADCHANNEL15
							 };

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void AD_Init( void );
void AD_Start( void );
void AD_Read( unsigned char*  buffer );
void AD_Stop( void );
void AD_ComparatorOn( void );
void AD_ComparatorOff( void );
void AD_SelectADChannel( enum ADChannel channel );

typedef struct 
{
    /* data */
    enum ADChannel name;
}ADC_InitTypeDef;

#endif
