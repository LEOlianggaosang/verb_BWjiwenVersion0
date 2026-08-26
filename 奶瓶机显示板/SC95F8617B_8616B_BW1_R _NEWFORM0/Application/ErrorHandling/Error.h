/**
 *******************************************************************************
 * 
 * @file    Error.h
 * @author  lianggaosang@qq.com
 * @version 1.0
 * @date    22:5:2025   15:49
 * @brief   异常处理模块API
 * 
 * 处理系统出现的异常状况.
 * 
 *******************************************************************************
 *
 * @attention
 * 

 *******************************************************************************
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#include "product_config.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
//! NEWFORM1 #5-1 更改故障代码
typedef enum
{
  ERROR_NULL,//E0
  ERROR_LACK,//E1 //! 改回E1且不显示
  ERROR_INLET,//E2
  ERROR_HEATER,//E3
  ERROR_OVER,//E4 //! 溢流硬件支持预留，改回E4与柜机保持一致，删除TDS故障添加
  ERROR_SERIAL,//E5 
  ERROR_RT,//E6 //! 改回E6与柜机保持一致
  ERROR_DOOR,//E7 //! 不显示，也不显示OPE
  ERROR_FAN,//E8
  // ERROR_DRAIN, 
  // ERROR_PMAM, 
}ErrorCode;
//!
// typedef enum
// {
//   ERROR_NULL,//E0
//   ERROR_TDS,//E1//20251110 NEWFORM0 8.5
//   ERROR_INLET,//E2
//   ERROR_HEATER,//E3
//   ERROR_RT,//E4
//   ERROR_SERIAL,//E5 
//   ERROR_DOOR,//OPE(6)
//   ERROR_LACK,//不显示(7)//20251110 NEWFORM0 8.5
//   ERROR_FAN,//e12
//   // ERROR_DRAIN, 
//   // ERROR_PMAM, 
//   ERROR_OVER
// }ErrorCode;
/***********************************************************************************************************************
Global variable
***********************************************************************************************************************/
extern ErrorCode Error_CurrentCode;
extern UCHAR_XDATA drainCount;
extern UCHAR_XDATA fanfbCount;
/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/**
 * @brief 设置当前的故障代码
 * 
 * @param [in] errorCode 故障代码
 * @return 无
 */
void Error_SetCode(ErrorCode errorCode);

/**
 * @brief 故障处理
 * 根据不同的故障代码进行相应报警及处理
 * @param 无
 * @return 无
 */
void Error_Handling(void);

#endif