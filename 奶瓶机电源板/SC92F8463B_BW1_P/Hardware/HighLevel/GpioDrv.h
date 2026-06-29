/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    GpioDrv.h
 * @author  lianggaosang@qq.com
 * @brief   BW1
 *
 *******************************************************************************
 */
 
#ifndef _GPIO_DRV_H_
#define _GPIO_DRV_H_

#include "Hardware_Config.h"
#include "product_config.h"

#ifdef SC92F8463B_ENABLED
typedef enum
{
	#if NEWTYPE1
	PS,//PIN10_P15_PS//OUTPUT
	HEAT,//PIN11_P16_HEAT//OUTPUT
	PTC,//PIN12_P17_PTC//OUTPUT
	IV,//PIN13_P27_INLET//OUTPUT
	//********************************
	DOOR,//PIN16_P24_DOOR//INPUT
	LED,//PIN17_P23_LED//OUTPUT
	FM,//PIN21_P07_FM//INPUT//INT23
	FAN_FB,//PIN22_P06_FAN_FB//INPUT//INT22
	FAN,//PIN23_P05_FAN//OUTPUT
	INP,//PIN24_P04_INLETPUMP//OUTPUT
	WP,//PIN28_P00_WP//OUTPUT
	#else
	//PIN01_VDD,
	//PIN02_P10_CMOD,
	//PIN03_VSS,
	HEAT,//PIN04_P51_HEAT//OUTPUT
	PTC,//PIN05_P50_PTC//OUTPUT
	PS,//PIN06_P11_PS//OUTPUT
	//PIN07_P12_tCK,//RX0
	//PIN08_P13_tDIO,//TX0
	//PIN09_P14_NTC//AIN9,
	//PIN10_P15
	//PIN11_P16
	//PIN12_P17
	IV,//PIN13_P27_INLET//OUTPUT
	WP,//PIN14_P26_WP//OUTPUT
	//********************************
	FAN_IN,//PIN15_P25_FAN_IN//OUTPUT
	UV,//PIN16_P24_UV//OUTPUT
	INP,//PIN17_P23_INLETPUMP//OUTPUT,
	FAN_IN_FB,//PIN18_P22_FAN_IN_FB//INPUT
	//PIN19_P21//RX1
	//PIN20_P20//TX1
	FAN_OUT,//PIN21_P07_FAN_OUT//OUTPUT
	FAN_OUT_FB,//PIN22_P06_FAN_OUT_FB//INPUT
	FM_IN,//PIN23_P05_FM_IN//INPUT
	FM_OUT,//PIN24_P04_FM_OUT//INPUT
	//PIN25_P03
	MP,//PIN26_P02_MOVEPUMP//OUTPUT
	DOOR,//PIN27_P01_DOOR//INPUT
	//PIN28_P00_BUZ//PWM0
	#endif
	
   END_PIN
}ePinName;
#endif

extern void InitPorts(void);
extern void SetPin(ePinName pin, unsigned char status);
extern unsigned char GetPin(ePinName pin);
extern void ReallocatePin(ePinName pin);

#endif //_GPIO_DRV_H_
