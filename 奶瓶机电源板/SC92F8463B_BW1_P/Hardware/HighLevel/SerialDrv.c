/**
 *******************************************************************************
 * Copyright (c) 20250423
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
#include "Hardware_Config.h"
#include "SerialDrv.h"


#ifdef SC92F8463B_ENABLED
Serial_InitTypeDef tSerials[SERIAL_END] = {
	#if NEWTYPE1
	{UART_0, 0},//SERIAL_FCT
	{UART_1, 0},//DISPLAY
	#else
	{UART_0, 0},//DISPLAY
	#endif
};
#endif



void Init_Uart(void)
{
   int i = 0;
#ifdef SC92F8463B_ENABLED
	for (i = 0; i < SERIAL_END; i++)
	{
		Uart_Hardware_Init(tSerials[i].name);
	}
#endif
}

void Uart_Start(eUserSerialName name)
{
#ifdef SC92F8463B_ENABLED
   Uart_Hardware_Start(tSerials[name].name);
#endif
}

void Uart_SendData(eUserSerialName name, unsigned char * txbuf, unsigned int txnum)
{
#ifdef SC92F8463B_ENABLED	
   Uart_Hardware_SendData(tSerials[name].name, txbuf, txnum);
#endif
}

void Uart_ReceiveData(eUserSerialName name, unsigned char * rx_buf, unsigned int rx_num)
{
#ifdef SC92F8463B_ENABLED
   Uart_Hardware_ReceiveData(tSerials[name].name, rx_buf, rx_num);
#endif
}

unsigned char Uart_IsReceivedDataDone(eUserSerialName name)
{
   unsigned char status = 0;

#ifdef SC92F8463B_ENABLED
	switch(name)
	{
		#if NEWTYPE1
		case SERIAL_FCT:
   			status = UART0IsReceivedDone();
			break;
		case SERIAL_DISPLAY:
   			status = UART1IsReceivedDone();
			break;
		#else
		case SERIAL_DISPLAY:
   			status = UART0IsReceivedDone();
			break;
		#endif
		default:
			break;
	}
#endif
	
   return status;
}
