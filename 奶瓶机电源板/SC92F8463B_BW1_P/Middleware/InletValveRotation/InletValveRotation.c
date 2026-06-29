/**
 *******************************************************************************
 * Copyright (c) 2022
 *  
 * @file    InletValveRotation.c
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief   进水转速控制
 *
 *******************************************************************************
 */

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "Signals\Signals.h"
#include "Test\Self_Test.h"
#include "Work\Work.h"
#include "ErrorHandling\Error.h"
#include "InletValveRotation.h"
/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
#define MIN_IV_LOW_DURATION     (2)
#define MIN_IV_HIGH_DURATION    (5)

USHORT_XDATA Signal_CurrentStepRotationCount = 0;
USHORT_XDATA Signal_CurrentStageRotationCount = 0;
USHORT_XDATA Test_Check_CurrentStepRotationCount = 0;

void Init_InletValveRotation(void)
{
    
}

void CalculatorInletValveRotation(void)
{
  static UCHAR_XDATA ivLowCnt = 0;
  static UCHAR_XDATA ivHighCnt = 0;
  static UCHAR_XDATA ivHighDurationCnt = 0;

  if (Signal_InletValve)
  {
      if (ivHighCnt < 255)
      {
          ivHighCnt ++;
      }

      if (ivHighDurationCnt < 255)
      {
          ivHighDurationCnt ++;
      }

      if (ivHighDurationCnt > 4)
      {
          ivLowCnt = 0;
      }
  }
  else
  {
      ivHighDurationCnt = 0;
      if (ivLowCnt < 255)
      {
          ivLowCnt ++;
      }

      if (ivLowCnt >= MIN_IV_LOW_DURATION)
      {
          if (ivHighCnt >= MIN_IV_HIGH_DURATION)
          {
              Signal_CurrentStepRotationCount ++;
              Signal_CurrentStageRotationCount ++;

              if(Test_Entered && (Work_CurrentFnIndex == INLET_ROTATION))
              {
                Test_Check_CurrentStepRotationCount++;
              }

              if (Signal_CurrentStageRotationCount >= 1500)
              {
                  Error_SetCode(ERROR_OVER);
              }
          }

          ivLowCnt = 0;
          ivHighCnt = 0;
      }
  }  
}

