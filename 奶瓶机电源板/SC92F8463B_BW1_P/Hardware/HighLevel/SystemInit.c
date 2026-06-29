/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    SystemInit.c
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
#include "SystemInit.h"

void SystemInit(void)
{

//	DisableInterrupt();
  
	InitPorts();
	
	InitAd();
	
	InitTimers();
	
	Init_Uart();
	
	Init_Buzzer();

#ifdef	EXTERNAL_INT_ENABLED
	EX_Init();
#endif
//	EnableInterrupt();

}
