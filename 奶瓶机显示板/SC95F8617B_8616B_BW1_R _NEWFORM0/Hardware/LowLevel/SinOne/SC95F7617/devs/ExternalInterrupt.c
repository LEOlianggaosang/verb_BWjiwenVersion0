/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    ExternalInterrupt.c
 * @author  lianggaosang@qq.com
 * @brief
 *******************************************************************************
 */
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC95F8617_ENABLED
#include "..\SC95F861x_C.H"//PIN22_P40_INT10//流量计
#endif
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#endif
#include "ExternalInterrupt.h"

intc_callback intc_func;

/**
 * @brief 外部中断功能模块初始化
 * 不需显示的调用高函数.
 * 
 * @param 无
 * @return 无
 */
void INTP_Init( void )
{
#ifdef SC95F8617_ENABLED
	P4CON &= ~(0x01);
	P4PH  &= ~(0x01);

	INT0F = 0;
	INT1F = 0X01;
	// INT1F = 0;
	INT2F = 0;
	
	INT0R = 0;
	INT1R |= 0X01;
	INT2R = 0;

	//LOW PRIORITY
	IPINT0 = 0;
	IPINT1 = 0;
	IP1 &= (~0X08);
	
	EINT0 = 0;
	EINT1 = 1;
	IE1 &= (~0X08);
#endif
// #ifdef SC95F8616B_ENABLED
// 	P3CON &= ~(0x04);
// 	P3PH  &= ~(0x04);

// 	INT0F = 0;
// 	INT1F = 0X80;
// 	// INT1F = 0;
// 	INT2F = 0;
	
// 	INT0R = 0;
// 	INT1R |= 0X80;
// 	INT2R = 0;

// 	//LOW PRIORITY
// 	IPINT0 = 0;
// 	IPINT1 = 0;
// 	IP1 &= (~0X08);
	
// 	EINT0 = 0;
// 	EINT1 = 1;
// 	IE1 &= (~0X08);
// #endif
}

void EX0() interrupt	0
{

}

void EX1() interrupt	2
{
	(*intc_func)();
}

void EX2() interrupt	10
{

}

void Intc_Set_Callback(intc_callback func)
{
	intc_func = func;
}
