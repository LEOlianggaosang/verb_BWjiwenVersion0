/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 *  
 * @file    SystemDrv.c
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
#include "SystemDrv.h"


unsigned char InitSystem(void)
{
	return System_Init();
}

void DisableInterrupt(void)
{
	EA = 0;
}

void EnableInterrupt(void)
{
	EA = 1;
}
