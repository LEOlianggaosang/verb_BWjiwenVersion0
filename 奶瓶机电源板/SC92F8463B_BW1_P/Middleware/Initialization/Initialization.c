/**
 *******************************************************************************
  * Copyright (c) 20250117
 * 
 * @file    Initialization.c
 * @author  lianggaosang@qq.com
 * @brief   初始化程序
 *
 *******************************************************************************
 */

/*
********************************************************************************
**  Include files
********************************************************************************
*/
#include "Initialization.h"
#include "SystemDrv.h"
#include "SystemInit.h"
#include "Buzzer\Buzzer.h"
#include "WashDish\WashDish.h"
#include "LoadDrive\LoadDrive.h"
#include "ReadSwitch\ReadSwitch.h"
#include "Temperatures\Temperatures.h"
#include "TicketHandling\TicketHandling.h"
#include "IoUart_Simulate\IoUart_Simulate.h"


/*
********************************************************************************
**  Global define
********************************************************************************
*/

/**
 * @brief调用各模块的初始化函数初始各模块.
 * 无需显示的调用该函数.
 * @param 无
 * @return 无
 */
void Initialization(void)
{
  DisableInterrupt();
	
  //hardware init
  SystemInit();

	Init_TicketHandling();
	
  Init_Buzz();

  Init_Load();

  Init_Switch();

  Init_WashDish();
	#if CONFIG_UARTSIMULATE
  Init_IoUartSimulate();
	#endif
  Init_Temperatures();
	
  EnableInterrupt();

  //DebugPrint("Hello\n");

  //wait power stable to finish initialization

	//DebugPrint("Finish initialization!");
}
