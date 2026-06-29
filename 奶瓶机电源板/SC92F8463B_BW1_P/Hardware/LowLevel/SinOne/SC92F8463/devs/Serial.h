/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    Serail.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _MDSERIAL_
#define _MDSERIAL_
#include "macrodriver.h"
#include "user_define.h"

#define BAUD_RATE	9600
#define BAUD_VALUE	(12000000/9600)
#define UART0_RCAP2L		LOW_8BITS(BAUD_VALUE)		//UART0_COUNT_LOW	//007A
#define UART0_RCAP2H		HIGH_8BITS(BAUD_VALUE)	//UART0_COUNT_HIGH	//1200

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
//enum TransferMode { SEND, RECEIVE };

typedef void (* serial_callback)(void);

#ifdef SC92F8463B_ENABLED
typedef enum 
{
    UART_0,
    UART_1,
    UART_ENUM_END
}eHardwareSerialName;
#endif

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


#ifdef SC92F8463B_ENABLED

/*UART0*///仿真口 暂不用UART
/*SCON*/
#define SCON_SM0 	0x80
#define SCON_SM1	0x40
#define SCON_SM2	0x20
#define SCON_REN	0x10
#define SCON_TB8	0x08
#define SCON_RB8	0x04
#define SCON_TI		0x02
#define SCON_RI		0x01

#define UART0_SCON_MODE	SCON_SM1
#define UART0_REN_ON (SCON |= SCON_REN)
#define UART0_REN_OFF (SCON &= ~SCON_REN)

#define UART0_TI_ON (SCON |= SCON_TI)
#define UART0_TI_OFF (SCON &= ~SCON_TI)

#define UART0_RI_ON (SCON |= SCON_RI)
#define UART0_RI_OFF (SCON &= ~SCON_RI)
/*SBUF*/
/*PCON*/
#define PCON_SMOD_12DIV 	0x80
#define PCON_SMOD_4DIV 		0x00
//**************
///*UART0-TIMER2*/
///*T2CON*/
//#define T2CON_RCLK	0x20
//#define T2CON_TCLK	0x10	
//#define T2CON_TR2		0x04
//#define T2CON_CLK		(T2CON_RCLK|T2CON_TCLK|T2CON_TR2)		//0011 0100
///*T2MOD*/
//#define T2MOD_DCEN	0x01		
//#define T2MOD_T2OE	0x02		//0

#define UART0_BAUD_RATE		200	//007A 1200
#define UART0_BAUD_VALUE	(12000000/UART0_BAUD_RATE)//24M-12M-1M(16000000/UART_BAUD_RATE)

#define UART0_TIMER2_RCAP2L		LOW_8BITS(UART0_BAUD_VALUE)		//UART0_COUNT_LOW	//007A
#define UART0_TIMER2_RCAP2H		HIGH_8BITS(UART0_BAUD_VALUE)	//UART0_COUNT_HIGH	//1200
//*******************************************************************************
/*UART1*/
/*OTCON*/
#define SSMOD_NONE 	0x00	//UART1_MODE_UART 1100 0000
#define SSMOD_SPI 	0x40
#define SSMOD_TWI 	0x80
#define SSMOD_UART 	0xC0

/*SSCON0*/
#define SSCON0_SM1	0x80
#define SSCON0_SM2	0x20
#define SSCON0_REN	0x10
#define SSCON0_TB8	0x08
#define SSCON0_RB8	0x04
#define SSCON0_TI	0x02
#define SSCON0_RI	0x01
/*SSCON1*///L
/*SSCON2*///H
/*SSDAT*///SBUF
#define UART1_REN_ON (SSCON0 |= SSCON0_REN)
#define UART1_REN_OFF (SSCON0 &= ~SSCON0_REN)

#define UART1_TI_ON (SSCON0 |= SSCON0_TI)
#define UART1_TI_OFF (SSCON0 &= ~SSCON0_TI)

#define UART1_RI_ON (SSCON0 |= SSCON0_RI)
#define UART1_RI_OFF (SSCON0 &= ~SSCON0_RI)

#define UART_BAUD_RATE		9600
#define UART_BAUD_VALUE	(12000000/UART_BAUD_RATE)//24M-12M(16000000/UART_BAUD_RATE)

#define UART_BAUDL	LOW_8BITS(UART_BAUD_VALUE)		//UART_COUNT_LOW
#define UART_BAUDH	HIGH_8BITS(UART_BAUD_VALUE)	//UART_COUNT_HIGH

//*******************************************************************************
extern unsigned char  UART0hasReceived;
void UART0_Init( void );
void UART0_Start( void );
void UART0_Stop( void );
MD_STATUS UART0_SendData( unsigned char* txbuf, unsigned short txnum );
MD_STATUS UART0_ReceiveData( unsigned char* rxbuf, unsigned short rxnum );
void CALL_UART0_Receive( void );
void CALL_UART0_Send( void );
unsigned char	UART0IsReceivedDone(void);
extern unsigned char  UART1hasReceived;
void UART1_Init( void );
void UART1_Start( void );
void UART1_Stop( void );
MD_STATUS UART1_SendData( unsigned char* txbuf, unsigned short txnum );
MD_STATUS UART1_ReceiveData( unsigned char* rxbuf, unsigned short rxnum );
void CALL_UART1_Receive( void );
void CALL_UART1_Send( void );
unsigned char UART1IsReceivedDone(void);

#endif

#endif
