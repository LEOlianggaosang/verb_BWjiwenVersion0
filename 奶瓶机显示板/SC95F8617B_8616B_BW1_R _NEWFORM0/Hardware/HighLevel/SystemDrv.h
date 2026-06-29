/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 *  
 * @file    SystemDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _SYSTEM_DRV_H_
#define _SYSTEM_DRV_H_

#include "Hardware_Config.h"
#define System_Init()	1
extern void DisableInterrupt(void);
extern void EnableInterrupt(void);
extern unsigned char InitSystem(void);

#endif //_SYSTEM_DRV_H_
