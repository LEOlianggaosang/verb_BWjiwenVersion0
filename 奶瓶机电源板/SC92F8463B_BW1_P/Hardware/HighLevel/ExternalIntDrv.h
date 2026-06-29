/**
 *******************************************************************************
 * Copyright (c) 20230731
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
#include "product_config.h"

#ifdef	EXTERNAL_INT_ENABLED

typedef enum
{
   #if (CONFIG_INT_CHECK&&NEWTYPE1)
   FM_Int,
   FB_Int,
   #endif
   END_INTC
}eEXIntName;

extern void EX_Init(void);
extern void SetEXIntCallback(eEXIntName name, intc_callback func);
extern void StartEXInt(eEXIntName name);
extern void StopEXInt(eEXIntName name);
//extern void SetExternalIntCallback(intc_callback func);
#endif

#endif //_EXTERNAL_INT_DRV_H_
