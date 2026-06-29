/**
*******************************************************************************
* 
* @file    IoUart_Simulate.c
* @author  lgx
* @version 1.0
* @date    2024.12.7
* @brief   模拟串口通信模块
* 
*/
 /*
 *------------------------------------------------------------------------------
 * include
 *------------------------------------------------------------------------------
 */
#include "IoUart_Simulate.h"
#include "WashDish\WashDish.h"
#if CONFIG_UARTSIMULATE
#if CONFIG_NIGHTLIGHT
#if NEWTYPE1

/*
 *------------------------------------------------------------------------------
 * global
 *------------------------------------------------------------------------------
 */
ByteFlag IoUart_Flags = {0};
/*
 *------------------------------------------------------------------------------
 * static
 *------------------------------------------------------------------------------
 */
 
static ByteFlag IoUartRx_Flags;
#define IoUartRxDate          IoUartRx_Flags.f_byte
#define IoUartRxBit0          IoUartRx_Flags.f_bits.no0
#define IoUartRxBit1          IoUartRx_Flags.f_bits.no1
#define IoUartRxBit2          IoUartRx_Flags.f_bits.no2
#define IoUartRxBit3          IoUartRx_Flags.f_bits.no3
#define IoUartRxBit4          IoUartRx_Flags.f_bits.no4
#define IoUartRxBit5          IoUartRx_Flags.f_bits.no5
#define IoUartRxBit6          IoUartRx_Flags.f_bits.no6
#define IoUartRxBit7          IoUartRx_Flags.f_bits.no7
 
static unsigned char RxByte_Cnt = 0;
static unsigned char TxByte_Cnt = 0;
static unsigned char RxBit_Cnt = 0;
static unsigned char TxBit_Cnt = 0;

/*SimulateUart*/
unsigned char  *gpSimulateUartTxAddress;			/* SimulateUart transmit buffer address */
unsigned short 	gSimulateUartTxLen;				/* SimulateUart receive data length */
unsigned char *gpSimulateUartRxAddress;			/* SimulateUart receive buffer address */
unsigned short	gSimulateUartRxLen;				/* SimulateUart receive data length */

static void Tx_Reload_Rx(bit value);

/*
 *------------------------------------------------------------------------------
 * Function
 *------------------------------------------------------------------------------
 */
void IoUartSimulate_Timer(void)
{//5ms中断调用函数
    if((IoUart_TxStart)&&(0==IoUart_TxHasSand))
    {//TX
        // if(IoUart_RxStart)
        // {//
        //     Tx_Reload_Rx(0);
        //     IoUart_RxStart = 0;
        // }
        // else
        {
            if(IoUart_TxByteStart)
            {//起始位
                IoUart_TxValue = 0;
                IoUart_TxByteStart = 0;
                TxBit_Cnt = 0;
            }
            else
            {
                if(++TxBit_Cnt>8)
                {//停止位
                    if(++TxByte_Cnt>=gSimulateUartTxLen)
                    {
                        IoUart_TxHasSand = 1;
                    }
                    else
                    {
                        IoUart_TxByteStart = 1;
                    }
                    IoUart_TxValue = 1;
                }
                else
                {//数据位
										if((*(gpSimulateUartTxAddress+TxByte_Cnt))&(0x01<<(TxBit_Cnt-1)))
										{
											IoUart_TxValue = 1;
										}
										else
										{
											IoUart_TxValue = 0;
										}
                    // IoUart_TxValue = (bit)((*(gpSimulateUartTxAddress+TxByte_Cnt))>>(TxBit_Cnt-1));
                }
            }
        }   
    
        if((IoUart_TxOutput != IoUart_TxValue)&&(!F_FCTing))//20251115
        {//输出
            IoUart_Location = IoUart_TxOutput = IoUart_TxValue;
        }
    }
    // else
    // {
    //     if(IoUart_TxStart)
    //     {
    //         Tx_Reload_Rx(1);
    //         IoUart_TxStart = 0;
    //     }
    //     else
    //     {
    //         if((IoUart_RxStart)&&(0==IoUart_RxHasReceived))
    //         {
    //             if(IoUart_RxByteStart)
    //             {
    //                 switch(++TxBit_Cnt)
    //                 {
	// 										case 1:
    //                         IoUartRxBit0 = IoUart_Location;
    //                         break;
	// 										case 2:
    //                         IoUartRxBit1 = IoUart_Location;
    //                         break;
	// 										case 3:
    //                         IoUartRxBit2 = IoUart_Location;
    //                         break;
	// 										case 4:
    //                         IoUartRxBit3 = IoUart_Location;
    //                         break;
	// 										case 5:
    //                         IoUartRxBit4 = IoUart_Location;
    //                         break;
	// 										case 6:
    //                         IoUartRxBit5 = IoUart_Location;
    //                         break;
	// 										case 7:
    //                         IoUartRxBit6 = IoUart_Location;
    //                         break;
	// 													case 8:
    //                         IoUartRxBit7 = IoUart_Location;
    //                         break;
    //                     default:
    //                         TxBit_Cnt = 0;
    //                         IoUart_RxByteStart = 0;
    //                         if(IoUart_Location)
    //                         {//停止位
    //                             *(gpSimulateUartRxAddress+RxByte_Cnt) = IoUartRxDate;
    //                             if(++RxByte_Cnt>=gSimulateUartRxLen)
    //                             {
    //                                 IoUart_RxHasReceived = 1;
    //                             }
    //                         }
    //                         break;
    //                 }
    //             }
    //             else
    //             {//起始位
    //                 if(0==IoUart_Location)
    //                 {
    //                     IoUart_RxByteStart = 1;
    //                     IoUartRxDate = 0;
    //                 }
    //             }
    //         }
    //     }
    // }
}
/*
 *------------------------------------------------------------------------------
 * static Function
 *------------------------------------------------------------------------------
 */
static void Tx_Reload_Rx(bit value)
{//P23切换为输入上拉
    
    if(value)
    {//tx->rx
        IoUart_Location = 1;
        P2CON &= ~(0x08);
        P2PH |= 0x08;
    }
    else
    {//rx->tx
        P2CON |= 0x08;
        P2PH &= ~(0x08);
        IoUart_Location = 1;
    }
}
/*
 *------------------------------------------------------------------------------
 * extern Function
 *------------------------------------------------------------------------------
 */
void Init_IoUartSimulate(void)
{

    SetTimerCallback(TIMER_IOUART, IoUartSimulate_Timer);
    StartTimer(TIMER_IOUART);

    IoUartFlag = 0;
    RxByte_Cnt = 0;
    TxByte_Cnt = 0;
    RxBit_Cnt = 0;
    TxBit_Cnt = 0;
    // Tx_Reload_Rx(0);
		IoUart_Location = IoUart_TxOutput = 1;
}

bit IoUart_HasReceived(void)
{
    bit ret = 0;
    unsigned char Sum,len,i = 0;

    ret = 0;
    if(IoUart_RxHasReceived)
    {
        len = *(gpSimulateUartRxAddress+1);
        if((0xaa==(*gpSimulateUartRxAddress))&&(len<=gSimulateUartRxLen))
        {
            for(i = 2,Sum = 0; i < (len-1); i++)
            {
                Sum += *(gpSimulateUartRxAddress + i);
            }

            if(Sum == *(gpSimulateUartRxAddress+(len-1)))
            {
                ret = 1;
            }
        }
    }
    return ret;
}

void IoUart_SandEnable( unsigned char* rxbuf, unsigned short rxnum )
{
    IoUart_TxStart = 1;
    IoUart_TxByteStart = 1;
    TxByte_Cnt = 0;
    TxBit_Cnt = 0;
    IoUart_TxHasSand = 0;
    // Tx_Reload_Rx(0);

    gpSimulateUartTxAddress = rxbuf;
    gSimulateUartTxLen = rxnum;
}

void IoUart_ReceivedEnable( unsigned char* rxbuf, unsigned short rxnum )
{
    IoUart_RxStart = 1;
    IoUart_RxByteStart = 0;
    RxByte_Cnt = 0;
    RxBit_Cnt = 0;
    IoUart_RxHasReceived = 0;

    gSimulateUartRxLen = rxnum;
    gpSimulateUartRxAddress = rxbuf;
}

#endif
#endif
#endif