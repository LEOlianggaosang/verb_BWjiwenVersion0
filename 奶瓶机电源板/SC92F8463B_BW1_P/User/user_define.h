/**
 *******************************************************************************
 * Copyright (c) 2023 
 * 
 * @file    user_define.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */

#ifndef _USER_DEFINE_H_
#define _USER_DEFINE_H_
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#include "stdio.h"
#include "intrins.h"
//define data type for application
typedef	unsigned long	ULONG;
typedef	signed long	SLONG;

typedef	unsigned int	UINT;
typedef	signed int	SINT;

typedef	unsigned short	USHORT;
typedef	signed short	SHORT;

typedef	unsigned char	UCHAR;
typedef	signed char	SCHAR;

typedef	unsigned char	BOOL;
//typedef	unsigned short xdata	MD_STATUS;

typedef	unsigned long xdata	ULONG_XDATA;
typedef	signed long	xdata SLONG_XDATA;

typedef	unsigned int xdata	UINT_XDATA;
typedef	signed int xdata	SINT_XDATA;

typedef	unsigned short xdata	USHORT_XDATA;
typedef	signed short xdata	SHORT_XDATA;

typedef	unsigned char xdata	UCHAR_XDATA;
typedef	signed char xdata	SCHAR_XDATA;

typedef	unsigned char xdata	BOOL_XDATA;

#define uchar unsigned char
#define uint unsigned int
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

#define NOP _nop_

#define	MD_ON		1
#define	MD_OFF		0

#define	MD_TRUE		1
#define	MD_FALSE	0

#define	TRUE		1
#define	FALSE	0

//#define	START		1
//#define	STOP		0

#define     BIT0    (0x0001)
#define     BIT1    (0x0002) 
#define     BIT2    (0x0004)
#define     BIT3    (0x0008)
#define     BIT4    (0x0010)
#define     BIT5    (0x0020)
#define     BIT6    (0x0040)
#define     BIT7    (0x0080)
#define     BIT8    (0x0100)
#define     BIT9    (0x0200) 
#define     BIT10   (0x0400)
#define     BIT11   (0x0800)
#define     BIT12   (0x1000)
#define     BIT13   (0x2000)
#define     BIT14   (0x4000)
#define     BIT15   (0x8000)

#define     _BIT0   (~BIT0)
#define     _BIT1   (~BIT1)
#define     _BIT2   (~BIT2)
#define     _BIT3   (~BIT3)
#define     _BIT4   (~BIT4)
#define     _BIT5   (~BIT5)
#define     _BIT6   (~BIT6)
#define     _BIT7   (~BIT7)
#define     _BIT8   (~BIT8)
#define     _BIT9   (~BIT9)
#define     _BIT10  (~BIT10)
#define     _BIT11  (~BIT11)
#define     _BIT12  (~BIT12)
#define     _BIT13  (~BIT13)
#define     _BIT14  (~BIT14)
#define     _BIT15  (~BIT15)

#define     Bit_0    (0x01)
#define     Bit_1    (0x02) 
#define     Bit_2    (0x04)
#define     Bit_3    (0x08)
#define     Bit_4    (0x10)
#define     Bit_5    (0x20)
#define     Bit_6    (0x40)
#define     Bit_7    (0x80)

#define     Bit_0_N    (~Bit_0)
#define     Bit_1_N    (~Bit_1) 
#define     Bit_2_N    (~Bit_2)
#define     Bit_3_N    (~Bit_3)
#define     Bit_4_N    (~Bit_4)
#define     Bit_5_N    (~Bit_5)
#define     Bit_6_N    (~Bit_6)
#define     Bit_7_N    (~Bit_7)

#define HIGH_8BITS(x) ((unsigned char)((x) >> 8))
#define LOW_8BITS(x) ((unsigned char)(x))
#define COMBINE_2BYTE(h,l)  (((h) << 8) + (l))
#define COMBINE_4BYTE(hh,hl,lh,ll)  (((hh) << 24) + ((hl) << 16) + ((lh) << 8) + (ll))
#define CHECK_DEC(x)   if(x!=0)--x
#define CHECK_BIGGER(a,b,c)   if(a>=b){c=a;}else c=b
//*************************************************
typedef union
{
  unsigned char f_byte;
  struct
  {
     unsigned char no0:1, no1:1, no2:1, no3:1, no4:1, no5:1, no6:1, no7:1;
  }f_bits;
}ByteFlag;
 typedef union
 {
   unsigned int f_word;
   struct
   {
      unsigned int no0:1, no1:1, no2:1, no3:1, no4:1, no5:1, no6:1, no7:1,no8:1, no9:1, no10:1, no11:1, no12:1, no13:1, no14:1, no15:1;
   }f_bits;
 }WordFlag;
//*************************************************
typedef void(*FunctionPt)(void);
//*************************************************
//typedef union
//{
//	unsigned char		Byte;
//	struct
//	{
//		unsigned char	Bit0	:1;
//		unsigned char	Bit1	:1;
//		unsigned char	Bit2	:1;
//		unsigned char	Bit3	:1;
//		unsigned char	Bit4	:1;
//		unsigned char	Bit5	:1;
//		unsigned char	Bit6	:1;
//		unsigned char	Bit7	:1;
//	}Bits;
//}Byte_Bits;
////*************************************************
//typedef union
//{
//	unsigned int		Word;
//	struct
//	{
//		unsigned int	Bit0	:1;
//		unsigned int	Bit1	:1;
//		unsigned int	Bit2	:1;
//		unsigned int	Bit3	:1;
//		unsigned int	Bit4	:1;
//		unsigned int	Bit5	:1;
//		unsigned int	Bit6	:1;
//		unsigned int	Bit7	:1;
//		unsigned int	Bit8	:1;
//		unsigned int	Bit9	:1;
//		unsigned int	Bit10	:1;
//		unsigned int	Bit11	:1;
//		unsigned int	Bit12	:1;
//		unsigned int	Bit13	:1;
//		unsigned int	Bit14	:1;
//		unsigned int	Bit15	:1;
//	}Bits;
//}Word_Bits;
//*************************************************
#endif
