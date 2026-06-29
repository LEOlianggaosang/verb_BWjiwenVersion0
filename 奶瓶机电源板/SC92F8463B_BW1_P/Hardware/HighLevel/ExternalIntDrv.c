/**
 *******************************************************************************
 * Copyright (c) 20240624
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

#ifdef	EXTERNAL_INT_ENABLED

#ifdef SC92F8463B_ENABLED
Intc_InitTypeDef tEXInt[END_INTC] = {
	#if (CONFIG_INT_CHECK&&NEWTYPE1)
	{INT2, INT_NUM_3, INT_FALL_ENABLE, INT_RISE_ENABLE, INT_LOW_PRIORITY, 0},//FM
	{INT2, INT_NUM_2, INT_FALL_ENABLE, INT_RISE_ENABLE, INT_LOW_PRIORITY, 0},//FB
	#endif
};
#endif

void SetEXIntCallback(eEXIntName name, intc_callback func)
{
	Intc_Set_Callback(tEXInt[name].name, func);
}

void EX_Init(void)
{
	int i = 0;
#ifdef SC92F8463B_ENABLED
	for (i = 0; i < END_INTC; i++)
	{
		Intc_Init(&tEXInt[i]);
	}
#endif
}

void StartEXInt(eEXIntName name)
{
#ifdef SC92F8463B_ENABLED
	Intc_Start(tEXInt[name].name);
#endif
}

void StopEXInt(eEXIntName name)
{
#ifdef SC92F8463B_ENABLED
	Intc_Stop(tEXInt[name].name);
#endif
}

#else


//void SetExternalIntCallback(intc_callback func)
//{
//	
//	INTP_Init();
//	Intc_Set_Callback(func);
//	
//}

#endif