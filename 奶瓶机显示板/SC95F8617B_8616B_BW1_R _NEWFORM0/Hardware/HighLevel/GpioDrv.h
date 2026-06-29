/**
 *******************************************************************************
 * Copyright (c) 2025.4.23
 *  
 * @file    GpioDrv.h
 * @author lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _GPIO_DRV_H_
#define _GPIO_DRV_H_

#include "Hardware_Config.h"

typedef enum
{
   // COM5,//PIN19_P37_disCom5//C7
   // COM4,//PIN20_P36_disCom4//C6
   // COM3,//PIN21_P35_disCom3//C5
   // COM2,//PIN22_P34_disCom2//C4
	// //-------------------------------
   // COM1,//PIN23_P33_disCom1//C3
   // SEG7,//PIN24_P32_disSeg7//S1
   // SEG6,//PIN25_P31_disSeg6//S2
   // SEG5,//PIN26_P30_disSeg5//S3
   // SEG4,//PIN27_P10_disSeg4//S4
   // SEG3,//PIN29_P14_disSeg3//S8
   // SEG2,//PIN30_P15_disSeg2//S9
   // SEG1,//PIN31_P16_disSeg1//S10
   END_PIN
}ePinName;

extern void InitPorts(void);
extern void SetPin(ePinName pin, unsigned char status);
extern unsigned char GetPin(ePinName pin);
extern void ReallocatePin(ePinName pin);

#endif //_GPIO_DRV_H_
/*
1/5占空比，S1~S27为segment，C3!C7为COMMON，共阴极
//----------------------------------------------------------------------------------
8616B
// PIN1_P02
// PIN2_P03
// PIN3_P04
// PIN4_P05
// PIN5_P06
// PIN6_P07_CMOD
// PIN7_VSS
// PIN8_P50
// PIN9_P51
// PIN10_P52
// PIN11_P53
// PIN12_VDD
PIN13_P45_USTX2//disRX
PIN14_P44_USRX2//disTX
// PIN15_P43
// PIN16_P42
// PIN17_P41
// PIN18_P40
PIN19_P37_disCom5//C7
PIN20_P36_disCom4//C6
PIN21_P35_disCom3//C5
PIN22_P34_disCom2//C4
//-------------------------------
PIN23_P33_disCom1//C3
PIN24_P32_disSeg7//S1
PIN25_P31_disSeg6//S2
PIN26_P30_disSeg5//S3
PIN27_P10_disSeg4//S4
PIN28_P11_tCK
// PIN29_P12
PIN28_P11_tDIO
PIN29_P14_disSeg3//S8
PIN30_P15_disSeg2//S9
PIN31_P16_disSeg1//S10
PIN32_P17_KEY7//TK15
PIN33_P20_KEY6//TK16
// PIN34_P21
PIN35_P22_KEY5//TK18
// PIN36_P23
PIN37_P24_KEY4//TK20
// PIN38_P25
PIN39_P26_KEY3//TK22
PIN40_P27_KEY2//TK23
PIN42_P00_KEY1//TK24
// PIN41_P01
 */