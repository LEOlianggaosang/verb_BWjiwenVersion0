/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    ExternalIntDrv.c
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
#include "ExternalIntDrv.h"

#ifdef EXTERNAL_INT_ENABLED
#ifdef	SC95F8617_ENABLED	
void SetExternalIntCallback(intc_callback func)
{
	Intc_Set_Callback(func);
}
#endif		

void Init_Int( void )
{
#ifdef	SC95F8617_ENABLED	
  INTP_Init();
#endif	
}
#endif

