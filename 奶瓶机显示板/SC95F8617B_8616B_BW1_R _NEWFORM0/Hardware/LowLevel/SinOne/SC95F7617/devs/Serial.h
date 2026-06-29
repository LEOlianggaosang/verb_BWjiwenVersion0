/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 *  
 * @file    Serail.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _SERIAL_
#define _SERIAL_
#include "macrodriver.h"
#include "product_config.h"

#define BAUD_RATE	9600
#define BAUD_VALUE	(32000000/BAUD_RATE)
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/

typedef void (* serial_callback)(void);

typedef enum 
{
    UART_0,
    USCI_0,
    USCI_1,
    USCI_2,
    UART_ENUM_END
}eHardwareSerialName;

typedef struct 
{
    /* data */
    eHardwareSerialName name;
    serial_callback  func;
}Serial_InitTypeDef;

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void Uart_Hardware_Init(eHardwareSerialName name);
void Uart_Hardware_Start(eHardwareSerialName name);
void Uart_Hardware_Stop(eHardwareSerialName name);
MD_STATUS Uart_Hardware_SendData(eHardwareSerialName name,  unsigned char* txbuf, unsigned short txnum );
MD_STATUS Uart_Hardware_ReceiveData(eHardwareSerialName name,  unsigned char* rxbuf, unsigned short rxnum );

void UART0_Init( void );
void UART0_Start( void );
void UART0_Stop( void );
MD_STATUS UART0_SendData( unsigned char* txbuf, unsigned short txnum );
MD_STATUS UART0_ReceiveData( unsigned char* rxbuf, unsigned short rxnum );
void CALL_UART0_Receive( void );
void CALL_UART0_Send( void );

void USCI0_Init( void );
void USCI0_Start( void );
void USCI0_Stop( void );
MD_STATUS USCI0_SendData( unsigned char* txbuf, unsigned short txnum );
MD_STATUS USCI0_ReceiveData( unsigned char* rxbuf, unsigned short rxnum );
void CALL_USCI0_Receive( void );
void CALL_USCI0_Send( void );

void USCI1_Init( void );
void USCI1_Start( void );
void USCI1_Stop( void );
MD_STATUS USCI1_SendData( unsigned char* txbuf, unsigned short txnum );
MD_STATUS USCI1_ReceiveData( unsigned char* rxbuf, unsigned short rxnum );
void CALL_USCI1_Receive( void );
void CALL_USCI1_Send( void );


void USCI2_Init( void );
void USCI2_Start( void );
void USCI2_Stop( void );
MD_STATUS USCI2_SendData( unsigned char* txbuf, unsigned short txnum );
MD_STATUS USCI2_ReceiveData( unsigned char* rxbuf, unsigned short rxnum );
void CALL_USCI2_Receive( void );
void CALL_USCI2_Send( void );

unsigned char UART0IsReceivedDone(void);
unsigned char USCI2IsReceivedDone(void);
unsigned char USCI1IsReceivedDone(void);
unsigned char USCI0IsReceivedDone(void);

#endif
