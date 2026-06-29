/**
 *******************************************************************************
 * Copyright (c) 2022
 *  
 * @file    Serail.h
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief
 *
 *******************************************************************************
 */
#ifndef _MDSTATUS_
#define _MDSTATUS_
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/

typedef	unsigned short	MD_STATUS;

#define	MD_TRUE		1
#define	MD_FALSE	0

/* Status list definition */
#define	MD_STATUSBASE		0x00
#define	MD_OK				MD_STATUSBASE+0x0	/* register setting OK */
#define	MD_RESET			MD_STATUSBASE+0x1	/* reset input */
#define	MD_SENDCOMPLETE		MD_STATUSBASE+0x2	/* send data complete */
#define	MD_OVF				MD_STATUSBASE+0x3	/* timer count overflow */
#define	MD_SPT				MD_STATUSBASE+0x8	/* IIC stop */
#define	MD_NACK				MD_STATUSBASE+0x9	/* IIC no ACK */
#define	MD_SLAVE_SEND_END	MD_STATUSBASE+0x10	/* IIC slave send end */
#define	MD_SLAVE_RCV_END	MD_STATUSBASE+0x11	/* IIC slave receive end */
#define	MD_MASTER_SEND_END	MD_STATUSBASE+0x12	/* IIC master send end */
#define	MD_MASTER_RCV_END	MD_STATUSBASE+0x13	/* IIC master receive end */
#define	MD_BUSY				MD_STATUSBASE+0x14	/* IIC is busy */

/* Error list definition */
#define	MD_ERRORBASE		0x80
#define	MD_ERROR			MD_ERRORBASE+0x0	/* error */
#define	MD_RESOURCEERROR	MD_ERRORBASE+0x1	/* no resource available */
#define	MD_PARITYERROR		MD_ERRORBASE+0x2	/* UARTn parity error */
#define	MD_OVERRUNERROR		MD_ERRORBASE+0x3	/* UARTn overrun error */
#define	MD_FRAMEERROR		MD_ERRORBASE+0x4	/* UARTn frame error */
#define	MD_ARGERROR			MD_ERRORBASE+0x5	/* Error agrument input error */
#define	MD_TIMINGERROR		MD_ERRORBASE+0x6	/* Error timing operation error */
#define	MD_SETPROHIBITED	MD_ERRORBASE+0x7	/* setting prohibited */
#define	MD_DATAEXISTS		MD_ERRORBASE+0x8	/* Data to be transferred next exists in TXBn register */

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
#endif
