/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    ExternalIntDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _EXTERNAL_INT_DRV_H_
#define _EXTERNAL_INT_DRV_H_

#include "Hardware_Config.h"

#ifdef EXTERNAL_INT_ENABLED
extern void SetExternalIntCallback(intc_callback func);
void Init_Int( void );
#endif

#endif //_EXTERNAL_INT_DRV_H_
