/**
 *******************************************************************************
 * Copyright (c) 2025.4.28
 *  
 * @file    LedRamDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _RAMLEDDRV_H_
#define _RAMLEDDRV_H_

#include "Hardware_Config.h"
#include "product_config.h"
typedef enum
{
   #if NEWTPE1
   COM5,//PIN19_P37_disCom5//C7
   COM4,//PIN20_P36_disCom4//C6
   COM3,//PIN21_P35_disCom3//C5
   COM2,//PIN22_P34_disCom2//C4
   COM1,//PIN23_P33_disCom1//C3
   SEG7,//PIN24_P32_disSeg7//S1
   SEG6,//PIN25_P31_disSeg6//S2
   SEG5,//PIN26_P30_disSeg5//S3
   SEG4,//PIN27_P10_disSeg4//S4
   SEG3,//PIN29_P12_disSeg3//S6
   SEG2,//PIN29_P14_disSeg2//S8
   SEG1,//PIN30_P15_disSeg1//S9
   SEG8,//PIN31_P16_disSeg8//S10
   #else
   COM5,//PIN19_P37_disCom5//C7
   COM1,//PIN20_P36_disCom1//C6
   COM2,//PIN21_P35_disCom2//C5
   COM3,//PIN22_P34_disCom3//C4
   COM4,//PIN23_P33_disCom4//C3
   SEG1,//PIN24_P32_disSeg1//S1
   SEG2,//PIN25_P31_disSeg2//S2
   SEG3,//PIN26_P30_disSeg3//S3
   SEG4,//PIN27_P10_disSeg4//S4
   SEG5,//PIN29_P14_disSeg5//S8
   SEG6,//PIN30_P15_disSeg6//S9
   SEG7,//PIN31_P16_disSeg7//S10
   #endif
   END_SEG
}eSegName;

extern void InitSegs(void);
// extern void SetLed(eLedName led, unsigned char status);

#endif //_RAMLEDDRV_H_
