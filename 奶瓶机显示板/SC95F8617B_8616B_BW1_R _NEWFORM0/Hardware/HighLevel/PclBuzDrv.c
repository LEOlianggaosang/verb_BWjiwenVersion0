/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    PclBuzDrv.c
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
#include "PclBuzDrv.h"
#include "TimerDrv.h"

void StartBuzzer(void)
{
	PWM_Start();
}

void StopBuzzer(void)
{
	PWM_Stop();
}

void InitBuzzer(void)
{
	PWM_Init();
}
