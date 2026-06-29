/**
 *******************************************************************************
 * 
 * @file    Self_Test.h
 * @author  Arno Zhang
 * @version 1.0
 * @date    26:4:2012   17:30
 * @brief   自检模块
 * 
 * 包括车间自检和整机自检
 * 
 *******************************************************************************
 */

#ifndef SELF_TEST_H_
#define SELF_TEST_H_

#include "WatchdogDrv.h"
#include "EepromDrv.h"
#include "GpioDrv.h"
#include "user_define.h"

extern BOOL_XDATA Test_Entered;
extern UCHAR_XDATA Test_CurrentStep;
extern UCHAR_XDATA Test_CurrentStage;
extern BOOL_XDATA Timer1s;

extern UCHAR_XDATA boardCheckSecondCount;

extern BOOL_XDATA workshop_Entered;
/**
 * @brief 整机自检
 * 
 * @param 无
 * @return 无
 */
void Test_Machine(void);
/**
 * @brief 车间自检
 * 
 * @param 无
 * @return 无
 */
void Test_Board(void);


#endif