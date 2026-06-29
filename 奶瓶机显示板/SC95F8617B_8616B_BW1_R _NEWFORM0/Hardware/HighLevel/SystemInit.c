/**
 *******************************************************************************
 * Copyright (c) 2025.4.28
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

#include "SystemInit.h"
// #include "GpioDrv.h"
#include "TimerDrv.h"
// #include "AdDrv.h"
// #include "ExternalIntDrv.h"
#include "EepromDrv.h"
#include "WatchdogDrv.h"
#include "SystemDrv.h"
#include "SerialDrv.h"
// #include "PclBuzDrv.h"
#include "LedRamDrv.h"
#include "TKDrv.h"

unsigned char SystemInit(void)
{
	unsigned char resetflag;

	DisableInterrupt();
        
  resetflag = InitSystem();
        
	InitTimers();
	
	// InitPorts();

	// Init_Int();
	
	// Init_Ad();

	Init_Uart();
	
	// InitBuzzer();

	InitSegs();

	Init_TK();

	EnableInterrupt();

	return resetflag;
}
