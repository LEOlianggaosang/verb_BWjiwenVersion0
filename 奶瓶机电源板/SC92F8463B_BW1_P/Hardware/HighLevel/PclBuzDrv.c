/**
 *******************************************************************************
 * Copyright (c) 20250117
 *  
 * @file    PclBuzDrv.c
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
#include "PclBuzDrv.h"

void Start_Buzzer(void)
{
#ifdef SC92F8463B_ENABLED
	PWM_Start();           
#endif
}

void Stop_Buzzer(void)
{
#ifdef SC92F8463B_ENABLED
	PWM_Stop();
#endif
}

void Init_Buzzer(void)
{
#ifdef SC92F8463B_ENABLED
	PWM_Init();
#endif
}