/**
 *******************************************************************************
  * Copyright (c) 2025.4.29
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
#include "product_config.h"

#include "TicketHandling\TicketHandling.h"
#include "Power\Power.h"
#include "PowerLostMemory\PowerLostMemory.h"
#include "Display\Display.h"
#include "Key\Key.h"
#include "Work\Work.h"

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
unsigned char Initialization(void)
{
  unsigned char resetFlag;
  DisableInterrupt();

  //hardware init
  resetFlag = SystemInit();

  Init_TicketHandling();

  Init_PowerLostMemory();

  Init_Key();
	
	Init_Power();

  EnableInterrupt();

  //DebugPrint("Hello\n");

  //wait power stable to finish initialization
	
	//DebugPrint("Finish initialization!");

  return resetFlag;
}
