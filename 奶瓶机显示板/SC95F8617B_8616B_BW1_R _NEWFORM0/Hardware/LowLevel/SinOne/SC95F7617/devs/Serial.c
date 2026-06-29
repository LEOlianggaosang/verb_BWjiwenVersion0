	/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 *  
 * @file    Serail.c
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
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#endif
#include "Serial.h"
#include "Power\Power.h"

/*UART0*/
//TM2;SBUF
///*SCON*/
//sbit  SM0	  = SCON^7;
//sbit  SM1	  = SCON^6;
//sbit  SM2	  = SCON^5;
//sbit  REN	  = SCON^4;
//sbit  TB8	  = SCON^3;
//sbit  RB8	  = SCON^2;
//sbit  TI	  = SCON^1;
//sbit  RI	  = SCON^0;
#define UART0_RATE_FROM_T1 0
#ifdef SC95F8616B_ENABLED
#define PCON_SMOD_NONE_DIV	0X00
#define PCON_SMOD_16_DIV	0X80
#endif
#define UART0_BAUD_RATE		BAUD_RATE
#define UART0_BAUD_VALUE	(32000000/UART0_BAUD_RATE)

#define US2CON1_COUNT_LOW	LOW_8BITS(USCI2_BAUD_VALUE)
#define US2CON1_COUNT_HIGH	HIGH_8BITS(USCI2_BAUD_VALUE)

/*USCI0*/
/*OTCON*/
#define USCI0_OFF	0x00
#define USCI0_SPI	0x10
#define USCI0_TWI	0x20
#define USCI0_UART	0x30
/*US0CON0*/
#define US0CON0_SM0 0x80
#define US0CON0_SM1	0x40
#define US0CON0_SM2	0x20
#define US0CON0_REN	0x10
#define US0CON0_TB8	0x08
#define US0CON0_RB8	0x04
#define US0CON0_TI	0x02
#define US0CON0_RI	0x01

#define US0CON0_REN_ON (US0CON0 |= US0CON0_REN)
#define US0CON0_REN_OFF (US0CON0 &= ~US0CON0_REN)

#define US0CON0_TI_ON (US0CON0 |= US0CON0_TI)
#define US0CON0_TI_OFF (US0CON0 &= ~US0CON0_TI)

#define US0CON0_RI_ON (US0CON0 |= US0CON0_RI)
#define US0CON0_RI_OFF (US0CON0 &= ~US0CON0_RI)

#define USCI0_BAUD_RATE		BAUD_RATE
#define USCI0_BAUD_VALUE	(32000000/USCI0_BAUD_RATE)

#define US0CON1_COUNT_LOW		LOW_8BITS(USCI0_BAUD_VALUE)
#define US0CON1_COUNT_HIGH	HIGH_8BITS(USCI0_BAUD_VALUE)

/*USCI1*/
/*OTCON*/
#define USCI1_OFF	0x00
#define USCI1_SPI	0x40
#define USCI1_TWI	0x80
#define USCI1_UART	0xC0
/*US1CON0*/
#define US1CON0_SM0 0x80
#define US1CON0_SM1	0x40
#define US1CON0_SM2	0x20
#define US1CON0_REN	0x10
#define US1CON0_TB8	0x08
#define US1CON0_RB8	0x04
#define US1CON0_TI	0x02
#define US1CON0_RI	0x01

#define US1CON0_REN_ON (US1CON0 |= US1CON0_REN)
#define US1CON0_REN_OFF (US1CON0 &= ~US1CON0_REN)

#define US1CON0_TI_ON (US1CON0 |= US1CON0_TI)
#define US1CON0_TI_OFF (US1CON0 &= ~US1CON0_TI)

#define US1CON0_RI_ON (US1CON0 |= US1CON0_RI)
#define US1CON0_RI_OFF (US1CON0 &= ~US1CON0_RI)

#define USCI1_BAUD_RATE		BAUD_RATE
#define USCI1_BAUD_VALUE	(32000000/USCI1_BAUD_RATE)

#define US1CON1_COUNT_LOW		LOW_8BITS(USCI1_BAUD_VALUE)
#define US1CON1_COUNT_HIGH	HIGH_8BITS(USCI1_BAUD_VALUE)

/*TMCON*/
#define USCI2_OFF	0x00
#define USCI2_SPI	0x40
#define USCI2_TWI	0x80
#define USCI2_UART	0xC0
/*USCI2*/
#define US2CON0_SM0 0x80
#define US2CON0_SM1	0x40
#define US2CON0_SM2	0x20
#define US2CON0_REN	0x10
#define US2CON0_TB8	0x08
#define US2CON0_RB8	0x04
#define US2CON0_TI	0x02
#define US2CON0_RI	0x01
#ifdef SC95F8616B_ENABLED
/*USXINX*/
#define  USCI2   2
#define  USCI3   3
#define  USCI4   4
#define  USCI5   5
#define USCIX_Mode USCI2
#define USXCON0_REN_ON (USXCON0 |= US2CON0_REN)
#define USXCON0_REN_OFF (USXCON0 &= ~US2CON0_REN)
#define USXCON0_TI_ON (USXCON0 |= US2CON0_TI)
#define USXCON0_TI_OFF (USXCON0 &= ~US2CON0_TI)
#define USXCON0_RI_ON (USXCON0 |= US2CON0_RI)
#define USXCON0_RI_OFF (USXCON0 &= ~US2CON0_RI)
#endif
#define USCI2_BAUD_RATE		BAUD_RATE
#define USCI2_BAUD_VALUE	(32000000/USCI2_BAUD_RATE)

#define US2CON1_COUNT_LOW	LOW_8BITS(USCI2_BAUD_VALUE)
#define US2CON1_COUNT_HIGH	HIGH_8BITS(USCI2_BAUD_VALUE)

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/

/*UART0*/
unsigned char  *gpUART0TxAddress;			/* UART0 transmit buffer address */
unsigned short xdata	gUART0TxCnt;				/* UART0 transmit data number */
unsigned char *gpUART0RxAddress;			/* UART0 receive buffer address */
unsigned short xdata	gUART0RxCnt;				/* UART0 receive data number */
unsigned short xdata	gUART0RxLen;				/* UART0 receive data length */

volatile unsigned char  UART0isSendBuzy;
volatile unsigned char  UART0hasReceived;

/*USCI0*/
unsigned char  *gpUSCI0TxAddress;			/* USCI0 transmit buffer address */
unsigned short xdata	gUSCI0TxCnt;				/* USCI0 transmit data number */
unsigned char *gpUSCI0RxAddress;			/* USCI0 receive buffer address */
unsigned short xdata	gUSCI0RxCnt;				/* USCI0 receive data number */
unsigned short xdata	gUSCI0RxLen;				/* USCI0 receive data length */

volatile unsigned char  USCI0isSendBuzy;
volatile unsigned char  USCI0hasReceived;

/*USCI1*/
unsigned char  *gpUSCI1TxAddress;			/* USCI1 transmit buffer address */
unsigned short xdata	gUSCI1TxCnt;				/* USCI1 transmit data number */
unsigned char *gpUSCI1RxAddress;			/* USCI1 receive buffer address */
unsigned short xdata	gUSCI1RxCnt;				/* USCI1 receive data number */
unsigned short xdata	gUSCI1RxLen;				/* USCI1 receive data length */

volatile unsigned char  USCI1isSendBuzy;
volatile unsigned char  USCI1hasReceived;

/*USCI2*//*USCIX*/
unsigned char  *gpUSCI2TxAddress;			/* USCI2 transmit buffer address */
unsigned short xdata	gUSCI2TxCnt;				/* USCI2 transmit data number */
unsigned char *gpUSCI2RxAddress;			/* USCI2 receive buffer address */
unsigned short xdata	gUSCI2RxCnt;				/* USCI2 receive data number */
unsigned short xdata	gUSCI2RxLen;				/* USCI2 receive data length */

volatile unsigned char  USCI2isSendBuzy;
volatile unsigned char  USCI2hasReceived;

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes UART0//USCI0//USCI1//USCI2
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void UART0_Init( void )
{//T2
	P2CON &= 0xFC;   //TX/RX is set to pull-up Input Mode 
	P2PH  |= 0x03;
	// mode 1: 1 start bit , 8 data, 1 stop bit
	// disable receive data
	SCON |= 0x40;		//0100 0000//Set the communication mode to mode 1 
#if	UART0_RATE_FROM_T1
	TMCON |= 0X02;   //T1频率来自fsys
	TXINX = 0x02;    //指向T2
	TXCON &= (~0x30);    //UART0收发波特率都由T1产生
	TH1 = UART0_BAUD_VALUE>>8;
	TL1 = UART0_BAUD_VALUE;
	TR1 = 0;//T1停止计数
	ET1 = 0;/T1禁止中断
	EUART = 0;     //Disable UART interrupt
#else
	TXINX = 0x02;    	//指向T2
	TXCON |= 0x30;    //UART0收发波特率都由T2产生
	TXMOD |= 0X80;		//T2频率来自fsys，禁止输出，禁止递减
	RCAPXH = (unsigned char)(UART0_BAUD_VALUE>>8);
	RCAPXL = (unsigned char)UART0_BAUD_VALUE;
	TRX = 0;//T2停止计数
	ET2 = 0;//T2禁止中断
	EUART = 0;     //Disable UART interrupt
#endif
	UART0isSendBuzy = 0;
	UART0hasReceived = 0;
	gUART0TxCnt = 0;
	gUART0RxCnt = 0;
}

void USCI0_Init( void )
{
	P0CON &= 0x9f;   //TX/RX, P05,P06 input mode//BLDC 1001 1111
	P0PH |= 0x60;			//0110 0000
	
	// USCI0 set to uart mode
	OTCON |= USCI0_UART;		//xx11 0000

	// mode 1: 1 start bit , 8 data, 1 stop bit
	// disable receive data
	US0CON0 = 0x40;		//0100 0000
	
	US0CON1 = (unsigned char)USCI0_BAUD_VALUE;
	US0CON2 = (unsigned char)(USCI0_BAUD_VALUE>>8);
	
	US0CON0_REN_OFF;
	IE1 &= ~0X01;     //disable Uart

	USCI0isSendBuzy = 0;
	USCI0hasReceived = 0;
	gUSCI0TxCnt = 0;
	gUSCI0RxCnt = 0;
}

void USCI1_Init( void )
{
	P1CON &= 0xF5;    //TX/RX is set to pull-up Input Mode 
	P1PH  |= 0x0A;
	
	OTCON |= USCI1_UART;    //USCI1 Serial interface select UART mode//11xx 0000
	
	US1CON0 = 0x40;   //Set the communication mode to mode 1
	// disable receive data
	
	US1CON1 = (unsigned char)USCI1_BAUD_VALUE;  
	US1CON2 = (unsigned char)(USCI1_BAUD_VALUE>>8);

	US1CON0_REN_OFF;
	IE2 &= ~0x01;      //disable USCI1 interrupt
	
	USCI1isSendBuzy = 0;
	USCI1hasReceived = 0;
	gUSCI1TxCnt = 0;
	gUSCI1RxCnt = 0;
}

void USCI2_Init( void )
{
	#ifdef SC95F8616B_ENABLED
	USXINX = USCIX_Mode;       //USCIX寄存器指向对应的USCI5
	P0CON &= ~0x0C;
 	P0PH |= 0x0C;
	TMCON |= USCI2_UART;    //USCI5 Serial interface select UART mode

	// mode 1: 1 start bit , 8 data, 1 stop bit
	// disable receive data
	USXCON0 = 0x40;
	
	USXCON1 = (unsigned char)USCI2_BAUD_VALUE;
	USXCON2 = (unsigned char)(USCI2_BAUD_VALUE>>8);

	USXCON0_REN_OFF;
	IE2 &= ~(0x01<<(USCIX_Mode-1));     //开启中断
	#endif

	USCI2isSendBuzy = 0;
	USCI2hasReceived = 0;
	gUSCI2TxCnt = 0;
	gUSCI2RxCnt = 0;
}

void UART0_Start( void )
{
	EUART = 1;
}
void UART0_Stop( void )
{
	EUART = 0;	 //disable Uart
}

void USCI0_Start( void )
{
	IE1 |= 0X01;
}

void USCI0_Stop( void )
{
	IE1 &= ~0X01;     //disable Uart
}

void USCI1_Start( void )
{
	IE2 |= 0X01;
}
void USCI1_Stop( void )
{
	IE2 &= ~0X01;     //disable Uart
}

void USCI2_Start( void )
{
	#ifdef SC95F8616B_ENABLED
	IE2 |= 0x01<<(USCIX_Mode-1);
	#endif
}
void USCI2_Stop( void )
{
	#ifdef SC95F8616B_ENABLED
	IE2 &= ~(0x01<<(USCIX_Mode-1));
	#endif
}

MD_STATUS UART0_ReceiveData( unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;

	if( rxnum < 1 ){
		status = MD_ERROR;
	}
	else {
		UART0hasReceived = 0;
		gUART0RxCnt = 0;
		gUART0RxLen = rxnum;
		gpUART0RxAddress = rxbuf;
		REN = 1;
	}

	return (status);
}

MD_STATUS UART0_SendData( unsigned char* txbuf, unsigned short txnum )
{
	MD_STATUS status = MD_OK;
	if( txnum < 1 )
	{
		status = MD_ERROR;
	}
	else 
	{
		gpUART0TxAddress = txbuf;
		gUART0TxCnt = txnum;
		SBUF = *gpUART0TxAddress;
		gpUART0TxAddress++;
		gUART0TxCnt--;
	}

	return (status);
}

MD_STATUS USCI0_ReceiveData( unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;

	if( rxnum < 1 ){
		status = MD_ERROR;
	}
	else 
	{
		USCI0hasReceived = 0;
		gUSCI0RxCnt = 0;
		gUSCI0RxLen = rxnum;
		gpUSCI0RxAddress = rxbuf;
		US0CON0_REN_ON;
	}

	return (status);
}

MD_STATUS USCI0_SendData( unsigned char* txbuf, unsigned short txnum )
{
	MD_STATUS status = MD_OK;
	if( txnum < 1 )
	{
		status = MD_ERROR;
	}
	else 
	{
		gpUSCI0TxAddress = txbuf;
		gUSCI0TxCnt = txnum;
		US0CON3 = *gpUSCI0TxAddress;
		gpUSCI0TxAddress++;
		gUSCI0TxCnt--;
	}

	return (status);
}

MD_STATUS USCI1_ReceiveData( unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;

	if( rxnum < 1 ){
		status = MD_ERROR;
	}
	else 
	{
		USCI1hasReceived = 0;
		gUSCI1RxCnt = 0; 
		gUSCI1RxLen = rxnum;
		gpUSCI1RxAddress = rxbuf;
		US1CON0_REN_ON;
	}

	return (status);
}

MD_STATUS USCI1_SendData( unsigned char* txbuf, unsigned short txnum )
{
	MD_STATUS status = MD_OK;
	if( txnum < 1 )
	{
		status = MD_ERROR;
	}
	else 
	{
		gpUSCI1TxAddress = txbuf;
		gUSCI1TxCnt = txnum;
		US1CON3 = *gpUSCI1TxAddress;
		gpUSCI1TxAddress++;
		gUSCI1TxCnt--;
	}

	return (status);
}
MD_STATUS USCI2_ReceiveData( unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;

	if( rxnum < 1 ){
		status = MD_ERROR;
	}
	else 
	{
		USCI2hasReceived = 0;
		gUSCI2RxCnt = 0;
		gUSCI2RxLen = rxnum;
		gpUSCI2RxAddress = rxbuf;
		#ifdef SC95F8616B_ENABLED
		USXINX = USCIX_Mode;       //USCIX寄存器指向对应的USCI5
		USXCON0_REN_ON;
		#endif
	}

	return (status);
}

MD_STATUS USCI2_SendData( unsigned char* txbuf, unsigned short txnum )
{
	MD_STATUS status = MD_OK;
	if( txnum < 1 )
	{
		status = MD_ERROR;
	}
	else 
	{
		gpUSCI2TxAddress = txbuf;
		gUSCI2TxCnt = txnum;
		#ifdef SC95F8616B_ENABLED
		USXINX = USCIX_Mode;       //USCIX寄存器指向对应的USCI5
		USXCON3 = *gpUSCI2TxAddress;
		#endif
		gpUSCI2TxAddress++;
		gUSCI2TxCnt--;
	}

	return (status);
}

void UartUART0Int(void) interrupt 4
{
	if(TI)
	{
		TI = 0;	
		if( gUART0TxCnt > 0 )
		{
			SBUF = *gpUART0TxAddress;
			gpUART0TxAddress++;
			gUART0TxCnt--;
		}
		else
		{
			CALL_UART0_Send();
		}
	}
	if(RI)
	{
		RI = 0;	
		if(gUART0RxLen > gUART0RxCnt)
		{
			*gpUART0RxAddress = SBUF;
			gpUART0RxAddress++;
			gUART0RxCnt++;
			if(gUART0RxLen == gUART0RxCnt)
			{
				CALL_UART0_Receive( );
			}
		}
	}	
}

void UartUSCI0Int(void) interrupt 7
{

	if(US0CON0 & US0CON0_TI)
	{
		#ifdef SC95F8617_ENABLED
		US0CON0_TI_OFF;
		#endif
		#ifdef SC95F8616B_ENABLED
		US0CON0_TI_ON;//写1清零
		#endif

		if( gUSCI0TxCnt > 0 )
		{
			US0CON3 = *gpUSCI0TxAddress;
			gpUSCI0TxAddress++;
			gUSCI0TxCnt--;
		}
		else
		{
			CALL_USCI0_Send();
		}
	}

	if(US0CON0 & US0CON0_RI)
	{
		#ifdef SC95F8617_ENABLED
		US0CON0_RI_OFF;
		#endif
		#ifdef SC95F8616B_ENABLED
		US0CON0_RI_ON;//写1清零
		#endif

		if(gUSCI0RxLen > gUSCI0RxCnt)
		{
			*gpUSCI0RxAddress = US0CON3;

			gpUSCI0RxAddress++;
			gUSCI0RxCnt++;
			if(gUSCI0RxLen == gUSCI0RxCnt)
			{
				CALL_USCI0_Receive( );
			}
		}
	}
}
#if CONFIG_FCT_UART
void UartUSCI1Int(void) interrupt 15
{
	static unsigned char USCI1RxBuffer = 0;
	static unsigned char bSUM = 0;//保留低8位

	if(US1CON0 & US1CON0_TI)
	{
		#ifdef SC95F8617_ENABLED
		US1CON0_TI_OFF;
		#endif
		#ifdef SC95F8616B_ENABLED
		US1CON0_TI_ON;//写1清零
		#endif
		if( gUSCI1TxCnt > 0 )
		{
			US1CON3 = *gpUSCI1TxAddress;
			gpUSCI1TxAddress++;
			gUSCI1TxCnt--;
		}
		else
		{
			CALL_USCI1_Send();
		}
	}
	if(US1CON0 & US1CON0_RI)
	{
		#ifdef SC95F8617_ENABLED
		US1CON0_RI_OFF;
		#endif
		#ifdef SC95F8616B_ENABLED
		US1CON0_RI_ON;//写1清零
		#endif	
		if(gUSCI1RxLen > gUSCI1RxCnt)
		{
			USCI1RxBuffer = US1CON3;
			if(0 == gUSCI1RxCnt)
			{
				if(0xa5 == USCI1RxBuffer)
				{
					*gpUSCI1RxAddress = USCI1RxBuffer;
					bSUM = USCI1RxBuffer;
					gpUSCI1RxAddress++;
					gUSCI1RxCnt++;
				}
				else
				{
					bSUM = 0;
					gUSCI1RxLen = POWER_DATA_LENGTH;
				}
			}
			else if(1 == gUSCI1RxCnt)
			{
				if(0x5a == USCI1RxBuffer)
				{
					*gpUSCI1RxAddress = USCI1RxBuffer;
					bSUM += USCI1RxBuffer;
					gpUSCI1RxAddress++;
					gUSCI1RxCnt++;
				}
				else
				{
					gpUSCI1RxAddress -= gUSCI1RxCnt;
					gUSCI1RxCnt = 0;
					bSUM = 0;
					gUSCI1RxLen = POWER_DATA_LENGTH;
				}
			}
			else if(2 == gUSCI1RxCnt)
			{
				if(0x04 == USCI1RxBuffer)
				{
					*gpUSCI1RxAddress = USCI1RxBuffer;
					bSUM += USCI1RxBuffer;
					gpUSCI1RxAddress++;
					gUSCI1RxCnt++;
				}
				else
				{
					gpUSCI1RxAddress -= gUSCI1RxCnt;
					gUSCI1RxCnt = 0;
					bSUM = 0;
					gUSCI1RxLen = POWER_DATA_LENGTH;
				}
			}
			else if(3 == gUSCI1RxCnt)
			{
				if((USCI1RxBuffer < gUSCI1RxLen)&&(USCI1RxBuffer > 0))
				{
					gUSCI1RxLen = *gpUSCI1RxAddress = USCI1RxBuffer;
					bSUM += USCI1RxBuffer;
					gpUSCI1RxAddress++;
					gUSCI1RxCnt++;
				}
				else
				{
					gpUSCI1RxAddress -= gUSCI1RxCnt;
					gUSCI1RxCnt = 0;
					bSUM = 0;
					gUSCI1RxLen = POWER_DATA_LENGTH;
				}
			}
			else
			{
				if(gUSCI1RxCnt == gUSCI1RxLen-1)
				{
					if(bSUM == USCI1RxBuffer)
					{
						*gpUSCI1RxAddress = USCI1RxBuffer;
						CALL_USCI1_Receive( );
					}
					else
					{
						gpUSCI1RxAddress -= gUSCI1RxCnt;
						gUSCI1RxCnt = 0;
						bSUM = 0;
						USCI1RxBuffer = 0;
						gUSCI1RxLen = POWER_DATA_LENGTH;
					}
				}
				else
				{
					*gpUSCI1RxAddress = USCI1RxBuffer;
					bSUM += USCI1RxBuffer;
					gpUSCI1RxAddress++;
					gUSCI1RxCnt++;
				}
			}
		}
	}	
}
#else
void UartUSCI1Int(void) interrupt 15
{
	if(US1CON0 & US1CON0_TI)
	{
		#ifdef SC95F8617_ENABLED
		US1CON0_TI_OFF;
		#endif
		#ifdef SC95F8616B_ENABLED
		US1CON0_TI_ON;//写1清零
		#endif
		if( gUSCI1TxCnt > 0 )
		{
			US1CON3 = *gpUSCI1TxAddress;
			gpUSCI1TxAddress++;
			gUSCI1TxCnt--;
		}
		else
		{
			CALL_USCI1_Send();
		}
	}
	if(US1CON0 & US1CON0_RI)
	{
		#ifdef SC95F8617_ENABLED
		US1CON0_RI_OFF;
		#endif
		#ifdef SC95F8616B_ENABLED
		US1CON0_RI_ON;//写1清零
		#endif	
		if(gUSCI1RxLen > gUSCI1RxCnt)
		{
			*gpUSCI1RxAddress = US1CON3;
			gpUSCI1RxAddress++;
			gUSCI1RxCnt++;
			if(gUSCI1RxLen == gUSCI1RxCnt)
			{
				CALL_USCI1_Receive( );
			}
		}
	}	
}
#endif

#ifdef SC95F8616B_ENABLED
void UartUSCI2Int(void) interrupt 19
{
	static unsigned char *USCI2RxAddress;//监控接收缓存数组menory
	static unsigned char USCI2RxBuffer = 0;
	static unsigned char bSUM = 0;//保留低8位
	if(USXCON0 & US2CON0_TI)
	{
		USXINX = USCIX_Mode;       //USCIX寄存器指向对应的USCI5
		USXCON0_TI_ON;//写1清零
//		USXCON0_TI_OFF;
		if( gUSCI2TxCnt > 0 )
		{
			USXCON3 = *gpUSCI2TxAddress;
			gpUSCI2TxAddress++;
			gUSCI2TxCnt--;
		}
		else
		{
			CALL_USCI2_Send();
		}
	}

	if(USXCON0 & US2CON0_RI)
	{
		USXINX = USCIX_Mode;       //USCIX寄存器指向对应的USCI5
		USXCON0_RI_ON;//写1清零
//		USXCON0_RI_OFF;
		if(gUSCI2RxLen > gUSCI2RxCnt)
		{
			// *gpUSCI2RxAddress = USXCON3;
			// gpUSCI2RxAddress++;
			// gUSCI2RxCnt++;
			// if(gUSCI2RxLen == gUSCI2RxCnt)
			// {
			// 	CALL_USCI2_Receive( );
			// }
			USCI2RxBuffer = USXCON3;
			if(0 == gUSCI2RxCnt)
			{
				if((0xa5 == USCI2RxBuffer)||(0xaa == USCI2RxBuffer))
				{
					*gpUSCI2RxAddress = USCI2RxBuffer;
					bSUM = USCI2RxBuffer;
					USCI2RxAddress = gpUSCI2RxAddress;//监控接收缓存数组menory
					gpUSCI2RxAddress++;
					gUSCI2RxCnt++;
				}
				else
				{
					bSUM = 0;
					gUSCI2RxLen = POWER_DATA_LENGTH;
				}
			}
			else if(1 == gUSCI2RxCnt)
			{
				if((0x5a == USCI2RxBuffer)||(0x55 == USCI2RxBuffer))
				{
					*gpUSCI2RxAddress = USCI2RxBuffer;
					bSUM += USCI2RxBuffer;
					gpUSCI2RxAddress++;
					gUSCI2RxCnt++;
				}
				else
				{
					gpUSCI2RxAddress -= gUSCI2RxCnt;
					gUSCI2RxCnt = 0;
					bSUM = 0;
					gUSCI2RxLen = POWER_DATA_LENGTH;
				}
			}
			else if(2 == gUSCI2RxCnt)
			{
				if((0x04 == USCI2RxBuffer)||(0x40 == USCI2RxBuffer)||(0x41 == USCI2RxBuffer))
				{
					*gpUSCI2RxAddress = USCI2RxBuffer;
					bSUM += USCI2RxBuffer;
					gpUSCI2RxAddress++;
					gUSCI2RxCnt++;
				}
				else
				{
					gpUSCI2RxAddress -= gUSCI2RxCnt;
					gUSCI2RxCnt = 0;
					bSUM = 0;
					gUSCI2RxLen = POWER_DATA_LENGTH;
				}
			}
			else if(3 == gUSCI2RxCnt)
			{
				if((USCI2RxBuffer < gUSCI2RxLen)&&(USCI2RxBuffer > 0))
				{
					gUSCI2RxLen = *gpUSCI2RxAddress = USCI2RxBuffer;
					bSUM += USCI2RxBuffer;
					gpUSCI2RxAddress++;
					gUSCI2RxCnt++;
				}
				else
				{
					gpUSCI2RxAddress -= gUSCI2RxCnt;
					gUSCI2RxCnt = 0;
					bSUM = 0;
					gUSCI2RxLen = POWER_DATA_LENGTH;
				}
			}
			else
			{
				if(gUSCI2RxCnt == gUSCI2RxLen-1)
				{
					if(bSUM == USCI2RxBuffer)
					{
						*gpUSCI2RxAddress = USCI2RxBuffer;
						CALL_USCI2_Receive( );
					}
					else
					{
						gpUSCI2RxAddress -= gUSCI2RxCnt;
						gUSCI2RxCnt = 0;
						bSUM = 0;
						USCI2RxBuffer = 0;
						gUSCI2RxLen = POWER_DATA_LENGTH;
					}
				}
				else
				{
					*gpUSCI2RxAddress = USCI2RxBuffer;
					bSUM += USCI2RxBuffer;
					gpUSCI2RxAddress++;
					gUSCI2RxCnt++;
				}
			}
		}
	}
}
#endif
unsigned char UART0IsReceivedDone(void)
{
	return UART0hasReceived;
}

void CALL_UART0_Receive( void )
{
	REN = 0;
	UART0hasReceived = 1;
}

void CALL_UART0_Send( void )
{
	UART0isSendBuzy = 0;
}

unsigned char USCI0IsReceivedDone(void)
{
	return USCI0hasReceived;
}

void CALL_USCI0_Receive( void )
{
	US0CON0_REN_OFF;
	USCI0hasReceived = 1;
}

void CALL_USCI0_Send( void )
{
	USCI0isSendBuzy = 0;
}

unsigned char USCI1IsReceivedDone(void)
{
	return USCI1hasReceived;
}
void CALL_USCI1_Receive( void )
{
	US1CON0_REN_OFF;
	USCI1hasReceived = 1;
}
void CALL_USCI1_Send( void )
{
	USCI1isSendBuzy = 0;
}

unsigned char USCI2IsReceivedDone(void)
{
	return USCI2hasReceived;
}

void CALL_USCI2_Receive( void )
{
	#ifdef SC95F8616B_ENABLED
	USXINX = USCIX_Mode;       //USCIX寄存器指向对应的USCI5
	USXCON0_REN_OFF;
	#endif
	USCI2hasReceived = 1;
}

void CALL_USCI2_Send( void )
{
	USCI2isSendBuzy = 0;
}


void Uart_Hardware_Init(eHardwareSerialName name)
{
	switch(name)
	{
		case UART_0:
			UART0_Init();
			break;
		case USCI_0:
			USCI0_Init();
			break;
		case USCI_1:
			USCI1_Init();
			break;
		case USCI_2:
			USCI2_Init();
			break;
		default:
			break;
	}
		 
}

void Uart_Hardware_Start(eHardwareSerialName name)
{
	switch(name)
	{
		case UART_0:
			UART0_Start();
			break;
		case USCI_0:
			USCI0_Start();
			break;
		case USCI_1:
			USCI1_Start();
			break;
		case USCI_2:
			USCI2_Start();
			break;
		default:

			break;
	}
}

void Uart_Hardware_Stop(eHardwareSerialName name)
{
	switch(name)
	{
		case UART_0:
			UART0_Stop();
			break;
		case USCI_0:
			USCI0_Stop();
			break;
		case USCI_1:
			USCI1_Stop();
			break;
		case USCI_2:
			USCI2_Stop();
			break;
		default:

			break;
	}
}

MD_STATUS Uart_Hardware_SendData(eHardwareSerialName name,  unsigned char* txbuf, unsigned short txnum )
{
	MD_STATUS status = MD_OK;
	switch(name)
	{
		case UART_0:
			status = UART0_SendData(txbuf, txnum);
			break;
		case USCI_0:
			status = USCI0_SendData(txbuf, txnum);
			break;
		case USCI_1:
			status = USCI1_SendData(txbuf, txnum);
			break;
		case USCI_2:
			status = USCI2_SendData(txbuf, txnum);
			break;
		default:

			break;
	}
	return status;
}

MD_STATUS Uart_Hardware_ReceiveData(eHardwareSerialName name,  unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;
	switch(name)
	{
		case UART_0:
			status = UART0_ReceiveData(rxbuf, rxnum);
			break;
		case USCI_0:
			status = USCI0_ReceiveData(rxbuf, rxnum);
			break;
		case USCI_1:
			status = USCI1_ReceiveData(rxbuf, rxnum);
			break;
		case USCI_2:
			status = USCI2_ReceiveData(rxbuf, rxnum);
			break;
		default:

			break;
	}
	return status;
}


