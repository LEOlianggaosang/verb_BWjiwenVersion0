/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    Serail.c
 * @author  lianggaosang@qq.com
 * @brief		only for SC92F8463B
 *
 *******************************************************************************
 */

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/

#ifdef SC92F8463B_ENABLED
#include "H/SC92F846XB_C.H"
#include "WashDish\WashDish.h"
#endif
#include "SerialDrv.h"
#include "product_config.h"
/*
*******************************************************************************
**  Global define
*******************************************************************************
*/

/*UART0*///DISPLAY
unsigned char  *gpUART0TxAddress;			/* UART0 transmit buffer address */
unsigned short	gUART0TxCnt;				/* UART0 transmit data number */
unsigned char *gpUART0RxAddress;			/* UART0 receive buffer address */
unsigned short	gUART0RxCnt;				/* UART0 receive data number */
unsigned short	gUART0RxLen;				/* UART0 receive data length */

volatile unsigned char UART0isSendBuzy;
volatile unsigned char UART0hasReceived;
/*UART1*///DISPLAY
unsigned char  *gpUART1TxAddress;			/* UART1 transmit buffer address */
unsigned short	gUART1TxCnt;				/* UART1 transmit data number */
unsigned char *gpUART1RxAddress;			/* UART1 receive buffer address */
unsigned short	gUART1RxCnt;				/* UART1 receive data number */
unsigned short	gUART1RxLen;				/* UART1 receive data length */

volatile unsigned char  UART1isSendBuzy;
volatile unsigned char  UART1hasReceived;
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes UART0//UART1
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
{//显示板
	P1CON &= ~0x0c;   //TX/RX, P13,P12 input mode//SOC 1111 0011
	P1PH |= 0x0c;			//0000 1100
	//**********
	// UART0 set to uart mode1
	SCON |= UART0_SCON_MODE;		//01XX XXXX
	// mode 1: 1 start bit , 8 data, 1 stop bit
	//SCON  |= 0X50;   //设置通信方式为模式一，允许接收
	// enable UART0 receive data
	UART0_REN_OFF;		//xxx1 xxxx
	//**********
	//use timer2
	TMCON	|= TIMER2_INPUT_FSYS_DIVIDE_12;	
	T2MOD = 0X00;
	PCON  = 0X00;				//SMOD=0
	T2CON = (T2CON_RCLK|T2CON_TCLK);		//T2CON = 0X30;
	//**********

	// //baud = 200
	// RCAP2L = UART0_TIMER2_RCAP2L;   //RCAP2H = Freq*1000000/baud/256;
	// RCAP2H = UART0_TIMER2_RCAP2H;   //RCAP2L = Freq*1000000/baud%256;

	//baud = 9600
	RCAP2L = UART0_RCAP2L;   //RCAP2H = Freq*1000000/baud/256;
	RCAP2H = UART0_RCAP2H;   //RCAP2L = Freq*1000000/baud%256;

	//**********
	T2CON	&= ~(T2CON_TR2);//TR2 = 0;
	ET2 = 0;
	EUART = 0;     //disable Uart
	IPUART = 0;
	//**********
	UART0isSendBuzy = 0;
	UART0hasReceived = 0;
	gUART0TxCnt = 0;
	gUART0RxCnt = 0;
//	gpUART0RxAddress = & SendDatasBuf;
}
///*****************************************************
//*函数名称：void Uart0_Init(uint Freq,unsigned long int baud)
//*函数功能：Uart0中断初始化
//*入口参数：Freq-主频，baud-波特率
//*出口参数：void
//*****************************************************/
//void Uart0_Init(uint Freq,unsigned long int baud)    //选择Timer1作为波特率信号发生器
//{
//	P1CON &= 0xF3;   //TX/RX设置为输入带上拉
//	P1PH  |= 0x0C;
//	
//	SCON  |= 0X50;   //设置通信方式为模式一，允许接收
//	TMCON |= 0X02;
//	TMOD  |= 0X20;
//	PCON  |= 0X80;	//SMOD=1
//	TH1 = (Freq*1000000/baud)>>8;	  //波特率为T1的溢出时间；
//	TL1 = Freq*1000000/baud;
//	TR1 = 0;
//	ET1 = 0;
//	EUART = 1;     //开启Uart0中断
//	EA = 1;
//}
///*
//void Uart0_Init(uint Freq,unsigned long int baud)    //选择Timer2作为波特率信号发生器
//{
//    P1CON &= 0xF3;   //TX设置为强推挽输出高，RX设置为输入带上拉
//	P1CON |= 0x08;
//	P1PH  |= 0x04;
//	P13 = 1;

//	SCON  |= 0X50;   //设置通信方式为模式一，允许接收
//	TMCON |= 0X04;
//	T2MOD = 0X00;
//	T2CON = 0X30;
//	RCAP2H = Freq*1000000/baud/256;
//	RCAP2L = Freq*1000000/baud%256;
//	TR2 = 0;
//	ET2 = 0;
//	EUART = 1;     //开启Uart0中断
//	EA = 1;
//}
//*/

#if NEWTYPE1
void UART1_Init( void )
{//显示板
	P2CON &= ~0x03;   //TX2/RX2, P20,P21 input mode//WASHDISH 1111 1100
	P2PH |= 0x03;			//0000 0011
	//**********
	// USCI set to uart mode
	OTCON |= SSMOD_UART;    //串行接口SSI选择Uart通信
	// mode 1: 1 start bit , 8 data, 1 stop bit
	// disable receive data
	SSCON0 &= ~(SSCON0_SM1|SSCON0_SM2|SSCON0_TB8|SSCON0_RB8);
	UART1_REN_OFF;
	SSCON1 = UART_BAUDL;   //波特率低位控制
	SSCON2 = UART_BAUDH;   //波特率高位控制
	//**********
	IE1 |= 0x01;      //开启SSI中断     
	IP1 &= ~(0x01);
	//**********
//	UART1isSendBuzy = 0;
//	UART1hasReceived = 0;
//	gUART1TxCnt = 0;
//	gUART1RxCnt = 0;
}
#else
void UART1_Init( void )
{//关闭串口
	// P2CON &= ~0x03;   //TX2/RX2, P20,P21 input mode//WASHDISH 1111 1100
	// P2PH |= 0x03;			//0000 0011
	// //**********
	// // USCI set to uart mode
	// OTCON |= SSMOD_UART;    //串行接口SSI选择Uart通信
	// // mode 1: 1 start bit , 8 data, 1 stop bit
	// // disable receive data
	// SSCON0 &= ~(SSCON0_SM1|SSCON0_SM2|SSCON0_TB8|SSCON0_RB8);
	// UART1_REN_OFF;
	// SSCON1 = UART_BAUDL;   //波特率低位控制
	// SSCON2 = UART_BAUDH;   //波特率高位控制
	// //**********
	// IE1 |= 0x01;      //开启SSI中断     
	// IP1 &= ~(0x01);
	//**********
	// UART1isSendBuzy = 0;
	// UART1hasReceived = 0;
	// gUART1TxCnt = 0;
	// gUART1RxCnt = 0;
}
#endif
///*****************************************************
//*函数名称：void Uart1_Init(uint Freq,unsigned long int baud)
//*函数功能：Uart1中断初始化
//*入口参数：Freq-主频，baud-波特率
//*出口参数：void
//*****************************************************/
//void Uart1_Init(uint Freq,unsigned long int baud)
//{
//	P2CON &= 0xFC;   //TX/RX设置为输入带上拉
//	P2PH  |= 0x03;
//	
//	OTCON |= 0xC0;    //串行接口SSI选择Uart1通信
//	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
//	SSCON1 = Freq*1000000/baud;   //波特率低位控制
//	SSCON2 = (Freq*1000000/baud)>>8;   //波特率高位控制
//	IE1 |= 0x01;      //开启SSI中断
//    EA = 1;	
//}
void UART0_Start( void )
{
	EUART = 1;
}

void UART0_Stop( void )
{
	EUART = 0;     //disable Uart
}
void UART1_Start( void )
{
	IE1 |= 0X01;
}

void UART1_Stop( void )
{
	IE1 &= ~0X01;     //disable Uart
}

MD_STATUS UART0_ReceiveData( unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;

	if( rxnum < 1 )
	{
		status = MD_ERROR;
	}
	else 
	{
		UART0hasReceived = 0;
		gUART0RxCnt = 0;
		gUART0RxLen = rxnum;
		gpUART0RxAddress = rxbuf;
		UART0_REN_ON;
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

MD_STATUS UART1_ReceiveData( unsigned char* rxbuf, unsigned short rxnum )
{
	MD_STATUS status = MD_OK;

	if( rxnum < 1 ){
		status = MD_ERROR;
	}
	else {
		UART1hasReceived = 0;
		gUART1RxCnt = 0;
		gUART1RxLen = rxnum;
		gpUART1RxAddress = rxbuf;
		UART1_REN_ON;
	}

	return (status);
}

MD_STATUS UART1_SendData( unsigned char* txbuf, unsigned short txnum )
{
	MD_STATUS status = MD_OK;
	if( txnum < 1 )
	{
		status = MD_ERROR;
	}
	else 
	{
		gpUART1TxAddress = txbuf;
		gUART1TxCnt = txnum;
		SSDAT = *gpUART1TxAddress;
		gpUART1TxAddress++;
		gUART1TxCnt--;
	}

	return (status);
}
//void UART0Int(void) interrupt 4
//{

//	if(TI)//SCON & SCON_TI
//	{
//		TI = 0;//UART0_TI_ON

//		if( gUART0TxCnt > 0 )
//		{
//			SBUF = *gpUART0TxAddress;
//			gpUART0TxAddress++;
//			gUART0TxCnt--;
//		}
//		else
//		{
//			CALL_UART0_Send();
//		}
//	}

//	if(RI)//SCON & SCON_RI
//	{
//		RI = 0;//UART0_RI_ON

//		if(gUART0RxLen > gUART0RxCnt)
//		{
//			*gpUART0RxAddress = SBUF;
//			if (*gpUART0RxAddress == '\n')//20230628 卡时
//			{
//				CALL_UART0_Receive( );
//			}
//			else
//			{
//				gpUART0RxAddress++;
//				gUART0RxCnt++;
//				if(gUART0RxLen == gUART0RxCnt)
//				{
//					CALL_UART0_Receive( );
//				}
//				
//			}
//		}
//	}
//}

#if NEWTYPE1

// void UART0Int(void) interrupt 4
// {//灯板通信
// 	if(TI)//SCON & SCON_TI
// 	{
// 		TI = 0;//UART0_TI_ON

// 		if( gUART0TxCnt > 0 )
// 		{
// 			SBUF = *gpUART0TxAddress;
// 			gpUART0TxAddress++;
// 			gUART0TxCnt--;
// 		}
// 		else
// 		{
// 			CALL_UART0_Send();
// 		}
// 	}

// 	if(RI)//SCON & SCON_RI
// 	{
// 		RI = 0;//UART0_RI_ON

// 		if(gUART0RxLen > gUART0RxCnt)
// 		{
// 			*gpUART0RxAddress = SBUF;
// 			if (*gpUART0RxAddress == '\n')//20230628 卡时
// 			{
// 				CALL_UART0_Receive( );
// 			}
// 			else
// 			{
// 				gpUART0RxAddress++;
// 				gUART0RxCnt++;
// 				if(gUART0RxLen == gUART0RxCnt)
// 				{
// 					CALL_UART0_Receive( );
// 				}
				
// 			}
// 		}
// 	}
// }

void UART0Int(void) interrupt 4
{//FCT启动
	static unsigned char UART0RxBuffer = 0;
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
			UART0RxBuffer = SBUF;
			if(0 == gUART0RxCnt)
			{
				if(0xaa == UART0RxBuffer)
				{
					*gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
			}
			else if(1 == gUART0RxCnt)
			{
				if(0x55 == UART0RxBuffer)
				{
					*gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
				else
				{
					gpUART0RxAddress -= gUART0RxCnt;//20240514
					gUART0RxCnt = 0;
				}
			}
			else if(2 == gUART0RxCnt)
			{
				if(0x40 == UART0RxBuffer)
				{
					*gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
				else
				{
					gpUART0RxAddress -= gUART0RxCnt;//20240514
					gUART0RxCnt = 0;
				}
			}
			else if(3 == gUART0RxCnt)
			{
				if((UART0RxBuffer < MESSAGE_DATA_LENGTH)&&(UART0RxBuffer > 0))
				{
					gUART0RxLen = *gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
				else
				{
					gpUART0RxAddress -= gUART0RxCnt;//20240514
					gUART0RxCnt = 0;
				}
			}
			else
			{
				*gpUART0RxAddress = UART0RxBuffer;
				gpUART0RxAddress++;
				gUART0RxCnt++;
				if(gUART0RxCnt >= gUART0RxLen)
				{
					CALL_UART0_Receive( );
				}
			}
		}
	}
}
#else
void UART0Int(void) interrupt 4
{//显示板
	static unsigned char UART0RxBuffer = 0;
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
			UART0RxBuffer = SBUF;
			if(0 == gUART0RxCnt)
			{
				if(0xa5 == UART0RxBuffer)
				{
					*gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
			}
			else if(1 == gUART0RxCnt)
			{
				if(0x5a == UART0RxBuffer)
				{
					*gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
				else
				{
					gpUART0RxAddress -= gUART0RxCnt;//20240514
					gUART0RxCnt = 0;
				}
			}
			else if(2 == gUART0RxCnt)
			{
				if(0x04 == UART0RxBuffer)
				{
					*gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
				else
				{
					gpUART0RxAddress -= gUART0RxCnt;//20240514
					gUART0RxCnt = 0;
				}
			}
			else if(3 == gUART0RxCnt)
			{
				if((UART0RxBuffer < MESSAGE_DATA_LENGTH)&&(UART0RxBuffer > 0))
				{
					gUART0RxLen = *gpUART0RxAddress = UART0RxBuffer;
					gpUART0RxAddress++;
					gUART0RxCnt++;
				}
				else
				{
					gpUART0RxAddress -= gUART0RxCnt;//20240514
					gUART0RxCnt = 0;
				}
			}
			else
			{
				*gpUART0RxAddress = UART0RxBuffer;
				gpUART0RxAddress++;
				gUART0RxCnt++;
				if(gUART0RxCnt >= gUART0RxLen)
				{
					CALL_UART0_Receive( );
				}
			}
		}
	}
}
#endif

#if NEWTYPE1
void UART1Int(void) interrupt 7
{//显示板
	static unsigned char UART1RxBuffer = 0;
	if(SSCON0 & SSCON0_TI)
	{
		UART1_TI_OFF;
		
		if( gUART1TxCnt > 0 )
		{
			SSDAT = *gpUART1TxAddress;
			gpUART1TxAddress++;
			gUART1TxCnt--;
		}
		else
		{
			CALL_UART1_Send();
		}
	}

	if(SSCON0 & SSCON0_RI)
	{
		UART1_RI_OFF;

		if(gUART1RxLen > gUART1RxCnt)
		{
			UART1RxBuffer = SSDAT;
			if(0 == gUART1RxCnt)
			{
				if((0xa5 == UART1RxBuffer)||(0xaa == UART1RxBuffer))
				{
					*gpUART1RxAddress = UART1RxBuffer;
					gpUART1RxAddress++;
					gUART1RxCnt++;
				}
			}
			else if(1 == gUART1RxCnt)
			{
				if((0x5a == UART1RxBuffer)||(0x55 == UART1RxBuffer))
				{
					*gpUART1RxAddress = UART1RxBuffer;
					gpUART1RxAddress++;
					gUART1RxCnt++;
				}
				else
				{
					gpUART1RxAddress -= gUART1RxCnt;//20240514
					gUART1RxCnt = 0;
				}
			}
			else if(2 == gUART1RxCnt)
			{
				if((0x04 == UART1RxBuffer)||(0x40 == UART1RxBuffer))
				{
					*gpUART1RxAddress = UART1RxBuffer;
					gpUART1RxAddress++;
					gUART1RxCnt++;
				}
				else
				{
					gpUART1RxAddress -= gUART1RxCnt;//20240514
					gUART1RxCnt = 0;
				}
			}
			else if(3 == gUART1RxCnt)
			{
				if((UART1RxBuffer < MESSAGE_DATA_LENGTH)&&(UART1RxBuffer > 0))
				{
					gUART1RxLen = *gpUART1RxAddress = UART1RxBuffer;
					gpUART1RxAddress++;
					gUART1RxCnt++;
				}
				else
				{
					gpUART1RxAddress -= gUART1RxCnt;//20240514
					gUART1RxCnt = 0;
				}
			}
			else
			{
				*gpUART1RxAddress = UART1RxBuffer;
				gpUART1RxAddress++;
				gUART1RxCnt++;
				if(gUART1RxCnt >= gUART1RxLen)
				{
					CALL_UART1_Receive( );
				}
			}
		}
	}
}
#else
void UART1Int(void) interrupt 7
{//关闭串口
	if(SSCON0 & SSCON0_TI)
	{
		UART1_TI_OFF;

		if( gUART1TxCnt > 0 )
		{
			SSDAT = *gpUART1TxAddress;
			gpUART1TxAddress++;
			gUART1TxCnt--;
		}
		else
		{
			CALL_UART1_Send();
		}
	}

	if(SSCON0 & SSCON0_RI)
	{
		UART1_RI_OFF;

		if(gUART1RxLen > gUART1RxCnt)
		{
			*gpUART1RxAddress = SSDAT;
			if (*gpUART1RxAddress == '\n')//20230628 卡时
			{
				CALL_UART1_Receive( );
			}
			else
			{
				gpUART1RxAddress++;
				gUART1RxCnt++;
				if(gUART1RxLen == gUART0RxCnt)
				{
					CALL_UART1_Receive( );
				}
				
			}
		}
	}
}
#endif

// void UART1Int(void) interrupt 7
// {

// 	if(SSCON0 & SSCON0_TI)
// 	{
// 		UART1_TI_OFF;

// 		if( gUART1TxCnt > 0 )
// 		{
// 			SSDAT = *gpUART1TxAddress;
// 			gpUART1TxAddress++;
// 			gUART1TxCnt--;
// 		}
// 		else
// 		{
// 			CALL_UART1_Send();
// 		}
// 	}

// 	if(SSCON0 & SSCON0_RI)
// 	{
// 		UART1_RI_OFF;

// 		if(gUART1RxLen > gUART1RxCnt)
// 		{
// 			*gpUART1RxAddress = SSDAT;
// 			if (*gpUART1RxAddress == '\n')//20230628 卡时
// 			{
// 				CALL_UART1_Receive( );
// 			}
// 			else
// 			{
// 				gpUART1RxAddress++;
// 				gUART1RxCnt++;
// 				if(gUART1RxLen == gUART0RxCnt)
// 				{
// 					CALL_UART1_Receive( );
// 				}
				
// 			}
// 		}
// 	}
// }
unsigned char UART0IsReceivedDone(void)
{
	return UART0hasReceived;
}

void CALL_UART0_Receive( void )
{
	UART0_REN_OFF;
	UART0hasReceived = 1;
}

void CALL_UART0_Send( void )
{
	UART0isSendBuzy = 0;
}
unsigned char UART1IsReceivedDone(void)
{
	return UART1hasReceived;
}

void CALL_UART1_Receive( void )
{
	UART1_REN_OFF;
	UART1hasReceived = 1;
}

void CALL_UART1_Send( void )
{
	UART1isSendBuzy = 0;
}

//#if 0
//char putchar (char c)
//{
//	SBUF = c;      /* output character */	
//		
//	while (!(TI));  /* wait until transmitter ready */
//	TI = 0;

//	return (c);
//}
//#else
//char putchar (char c)
//{
//	while(UART1isSendBuzy);

//	UART1isSendBuzy = 1;
//	SBUF = c;      /* output character */

//	return (c);
//}
//#endif

void Uart_Hardware_Init(eHardwareSerialName name)
{
	switch(name)
	{
		case UART_0:
			UART0_Init();
			break;
		case UART_1:
			UART1_Init();
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
		case UART_1:
			UART1_Start();
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
		case UART_1:
			UART1_Stop();
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
		case UART_1:
			status = UART1_SendData(txbuf, txnum);
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
		case UART_1:
			status = UART1_ReceiveData(rxbuf, rxnum);
			break;
		default:

			break;
	}
	return status;
}


