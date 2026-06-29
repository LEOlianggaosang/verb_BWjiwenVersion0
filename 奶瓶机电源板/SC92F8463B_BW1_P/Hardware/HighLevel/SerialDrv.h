/**
 *******************************************************************************
 * Copyright (c) 20250423
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
#include "product_config.h"

extern void IntSR0Service(unsigned char IntSR0Service_Buf);
extern unsigned char IntST0Service(void);
extern unsigned char IntST0Service_cntbuffer;
//20240620
#ifdef SC92F8463B_ENABLED
typedef enum
{
   #if NEWTYPE1
   SERIAL_FCT,
   SERIAL_DISPLAY,
   #else
   SERIAL_DISPLAY,
   #endif
   SERIAL_END
}eUserSerialName;
#endif

void Uart_SendData(eUserSerialName name, unsigned char * txbuf, unsigned int txnum);
void Uart_ReceiveData(eUserSerialName name, unsigned char * rx_buf, unsigned int rx_num);
void Init_Uart(void);
void Uart_Start(eUserSerialName name);
void Uart_Stop(eUserSerialName name);
extern unsigned char Uart_IsReceivedDataDone(eUserSerialName name);
#endif //_SERIAL_DRV_H_
