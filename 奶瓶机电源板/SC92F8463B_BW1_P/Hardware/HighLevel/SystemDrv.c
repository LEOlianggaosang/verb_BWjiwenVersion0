/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    SystemDrv.c
 * @author  lianggaosang@qq.com
 * @brief   OK
 *
 *******************************************************************************
 */
 
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "Hardware_Config.h"
#include "SystemDrv.h"

void DisableInterrupt(void)
{
#ifdef SC92F8463B_ENABLED
	EA = 0;
#endif
}

void EnableInterrupt(void)
{
#ifdef SC92F8463B_ENABLED
	EA = 1;
#endif
}
