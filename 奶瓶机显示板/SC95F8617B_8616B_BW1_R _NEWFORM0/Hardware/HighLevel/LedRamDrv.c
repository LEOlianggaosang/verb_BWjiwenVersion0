/**
 *******************************************************************************
 * Copyright (c) 2025.4.28
 *  
 * @file    LedRamDrv.c
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
#include "LedRamDrv.h"

#ifdef SC95F8616B_ENABLED
const SegRam_InitTypeDef xdata tSegs[END_SEG] = 
{
	#if NEWTPE1
	{PVO3, PVO_PIN_7}, // COM5,//PIN19_P37_disCom5//C7
	{PVO3, PVO_PIN_6}, // COM4,//PIN20_P36_disCom4//C6
	{PVO3, PVO_PIN_5}, // COM3,//PIN21_P35_disCom3//C5
	{PVO3, PVO_PIN_4}, // COM2,//PIN22_P34_disCom2//C4
	{PVO3, PVO_PIN_3}, // COM1,//PIN23_P33_disCom4//C3
	{PVO3, PVO_PIN_2}, // SEG7,//PIN24_P32_disSeg7//S1
	{PVO3, PVO_PIN_1}, // SEG6,//PIN25_P31_disSeg6//S2
	{PVO3, PVO_PIN_0}, // SEG5,//PIN26_P30_disSeg5//S3
	{PVO1, PVO_PIN_0}, // SEG4,//PIN27_P10_disSeg4//S4
	{PVO1, PVO_PIN_2}, // SEG3,//PIN29_P12_disSeg3//S6
	{PVO1, PVO_PIN_4}, // SEG2,//PIN29_P14_disSeg2//S8
	{PVO1, PVO_PIN_5}, // SEG1,//PIN30_P15_disSeg1//S9
	{PVO1, PVO_PIN_6}, // SEG8,//PIN31_P16_disSeg8//S10
	#else
	{PVO3, PVO_PIN_7}, // COM5,//PIN19_P37_disCom5//C7
	{PVO3, PVO_PIN_6}, // COM4,//PIN20_P36_disCom1//C6
	{PVO3, PVO_PIN_5}, // COM3,//PIN21_P35_disCom2//C5
	{PVO3, PVO_PIN_4}, // COM2,//PIN22_P34_disCom3//C4
	{PVO3, PVO_PIN_3}, // COM1,//PIN23_P33_disCom4//C3
	{PVO3, PVO_PIN_2}, // SEG1,//PIN24_P32_disSeg1//S1
	{PVO3, PVO_PIN_1}, // SEG2,//PIN25_P31_disSeg2//S2
	{PVO3, PVO_PIN_0}, // SEG3,//PIN26_P30_disSeg3//S3
	{PVO1, PVO_PIN_0}, // SEG4,//PIN27_P10_disSeg4//S4
	{PVO1, PVO_PIN_4}, // SEG5,//PIN29_P14_disSeg5//S8
	{PVO1, PVO_PIN_5}, // SEG6,//PIN30_P15_disSeg6//S9
	{PVO1, PVO_PIN_6}, // SEG7,//PIN31_P16_disSeg7//S10
	#endif
};
#endif

void InitSegs(void)
{
	int i = 0;
#ifdef SC95F8616B_ENABLED
	DDRCON |= DDRCOM_DMOD;// LED mode
	DDRCON |= DDRCOM_DUTY_5DIV;// 1/5 duty
	DDRCON |= DDRCOM_DDRON; // Enable display driver scan switch
	// DDRCON = DDRCOM_DDRON | DDRCOM_DMOD | DDRCOM_DUTY_5DIV ;// 1/5 duty
	IOHCON0 = 0x00;
	IOHCON1 = 0x00;
	//OTCON = 0x00;//20251031 显示驱动初始化影响USCI1功能
	//P0VO = P1VO = P2VO = P3VO = 0xff;//0xff//20251031 显示驱动初始化影响USCI1功能
	for (i = 0; i < END_SEG; i++)
	{
		SegRam_Init(&tSegs[i]);
	}
	SegRam_Clear();
#endif
	// P3CON = 0xFF;  //设置为强推挽模式输出
	// P3PH  = 0x00;
	// P1CON = 0xFF;  //设置为强推挽模式输出
	// P1PH  = 0x00;

	// P37=1;
	// P36=0;
	// P35=0;
	// P34=0;
	// P33=1;

	// P32=1;
	// P31=1;
	// P30=0;
	// P10=0;
	// P14=0;
	// P15=0;
	// P16=0;
}
