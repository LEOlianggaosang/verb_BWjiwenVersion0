/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 *  
 * @file    SerialDrv.c
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
#include "SerialDrv.h"

Serial_InitTypeDef xdata tSerials[SERIAL_END] = 
{
	#ifdef SC95F8616B_ENABLED
	#if CONFIG_FCT_UART
	{USCI_1, 0},
	#endif
	{USCI_2, 0},
	#endif
};


void Init_Uart(void)
{
   int i = 0;
   #ifdef SC95F8616B_ENABLED
	for (i = 0; i < SERIAL_END; i++)
	{
		Uart_Hardware_Init(tSerials[i].name);
	}
	#endif
}

void Uart_Start(eUserSerialName name)
{
	#ifdef SC95F8616B_ENABLED
	Uart_Hardware_Start(tSerials[name].name);
	#endif
}

void Uart_Stop(eUserSerialName name)
{
	#ifdef SC95F8616B_ENABLED
	Uart_Hardware_Stop(tSerials[name].name);
	#endif
}

void Uart_SendData(eUserSerialName name, unsigned char * txbuf, unsigned int txnum)
{
	#ifdef SC95F8616B_ENABLED
	Uart_Hardware_SendData(tSerials[name].name, txbuf, txnum);
	#endif
}

void Uart_ReceiveData(eUserSerialName name, unsigned char * rx_buf, unsigned int rx_num)
{
	#ifdef SC95F8616B_ENABLED
	Uart_Hardware_ReceiveData(tSerials[name].name, rx_buf, rx_num);
	#endif
}

unsigned char Uart_IsReceivedDataDone(eUserSerialName name)
{
   unsigned char status = 0;
   #ifdef SC95F8616B_ENABLED
	switch(name)
	{
		#if CONFIG_FCT_UART
		case SERIAL_FCT:
   			status = USCI1IsReceivedDone();
			break;
		#endif
		case SERIAL_POWER:
   			status = USCI2IsReceivedDone();
			break;
		default:
			break;
	}
   return status;
   #endif
}
