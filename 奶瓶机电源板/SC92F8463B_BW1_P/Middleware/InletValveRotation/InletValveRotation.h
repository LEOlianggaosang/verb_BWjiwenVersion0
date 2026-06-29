/**
 *******************************************************************************
 * Copyright (c) 2022
 * 
 * @file    InletValveRotation.h
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief  
 *
 *******************************************************************************
 */

#ifndef _INLET_VALVE_ROTATION_H_
#define _INLET_VALVE_ROTATION_H_

#include "user_define.h"

extern USHORT_XDATA Signal_CurrentStepRotationCount;
extern USHORT_XDATA Signal_CurrentStageRotationCount;
extern USHORT_XDATA Test_Check_CurrentStepRotationCount;

void CalculatorInletValveRotation(void);

void Init_InletValveRotation(void);

#endif
