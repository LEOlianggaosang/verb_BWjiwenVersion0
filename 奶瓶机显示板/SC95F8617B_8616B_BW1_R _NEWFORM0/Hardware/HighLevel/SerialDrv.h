/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 *  
 * @file    SerialDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _SERIAL_DRV_H_
#define _SERIAL_DRV_H_

#include "Hardware_Config.h"

typedef enum
{
   #if CONFIG_FCT_UART
   SERIAL_FCT,//USCI1
   #endif
   SERIAL_POWER,//USCI2
   SERIAL_END
}eUserSerialName;

void Uart_SendData(eUserSerialName name, unsigned char * txbuf, unsigned int txnum);
void Uart_ReceiveData(eUserSerialName name, unsigned char * rx_buf, unsigned int rx_num);
void Init_Uart(void);
void Uart_Start(eUserSerialName name);
void Uart_Stop(eUserSerialName name);
unsigned char Uart_IsReceivedDataDone(eUserSerialName name);
#endif //_SERIAL_DRV_H_
