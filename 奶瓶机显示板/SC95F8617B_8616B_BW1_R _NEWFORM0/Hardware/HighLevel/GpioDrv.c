/**
 *******************************************************************************
 * Copyright (c) 2025.4.9
 *  
 * @file    GpioDrv.c
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
#include "GpioDrv.h"


#ifdef SC95F8616B_ENABLED

const Gpio_InitTypeDef xdata tPorts[END_PIN] = 
{

};
#endif



void InitPorts(void)
{
	int i = 0;
#ifdef SC95F8616B_ENABLED
	for (i = 0; i < END_PIN; i++)
	{
		Gpio_Init(&tPorts[i]);
	}		
	SC95F8616B_NIO_Init();
#endif
}

void SetPin(ePinName pin, unsigned char status)
{
	Gpio_Set(&tPorts[pin], status);		
}

unsigned char GetPin(ePinName pin)
{
	unsigned char status = OFF;
	
	status = Gpio_Get(&tPorts[pin]);	

	return status;
}

void ReallocatePin(ePinName pin)
{
	Gpio_Init(&tPorts[pin]);			
}

