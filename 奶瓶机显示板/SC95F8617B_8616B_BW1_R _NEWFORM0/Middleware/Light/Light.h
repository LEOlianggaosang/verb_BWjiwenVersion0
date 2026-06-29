/**
*******************************************************************************
 * Copyright (c) 2025.4.28
 * 
* @file    Light.h
* @author  lianggaosang@qq.com
* @brief   8616b奶瓶机显示板
* 
*******************************************************************************
*/

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "product_config.h"
#include "LedRamDrv.h"
#if NEWTPE1
   // COM5,//PIN19_P37_disCom5//C7//led//ng
   // COM4,//PIN20_P36_disCom4//C6//pin4
   // COM3,//PIN21_P35_disCom3//C5//pin3
   // COM2,//PIN22_P34_disCom2//C4//pin2
   // //-------------------------------
   // COM1,//PIN23_P33_disCom1//C3//pin1

   // SEG7,//PIN24_P32_disSeg7//S1//pin11
   // SEG3,//PIN29_P12_disSeg3//S6//pin10//ng
   // SEG5,//PIN26_P30_disSeg5//S3//pin9
   // SEG4,//PIN27_P10_disSeg4//S4//pin8
   // SEG6,//PIN25_P31_disSeg6//S2//pin7
   // SEG2,//PIN31_P14_disSeg2//S8//pin6//ng
   // SEG1,//PIN32_P15_disSeg1//S9//pin5
   // SEG8,//PIN33_P16_disSeg8//S10
typedef enum
{
    Com1_SegA,//C3S9
    Com1_SegB,//C3S8
    Com1_SegC,//C3S6
    Com1_SegD,//C3S4
    Com1_SegE,//C3S3
    Com1_SegF,//C3S2
    Com1_SegG,//C3S1

    Com2_SegA,//C4S9
    Com2_SegB,//C4S8
    Com2_SegC,//C4S6
    Com2_SegD,//C4S4
    Com2_SegE,//C4S3
    Com2_SegF,//C4S2
    Com2_SegG,//C4S1

    Com3_SegA,//C5S9
    Com3_SegB,//C5S8
    Com3_SegC,//C5S6
    Com3_SegD,//C5S4
    Com3_SegE,//C5S3
    Com3_SegF,//C5S2
    Com3_SegG,//C5S1

    Com4_Lack,//C6S9
    Com4_Wash,//C6S8
    Com4_Dot1,//C6S6
    Com4_Dot2,//C6S4
    Com4_Sterilize,//C6S3
    Com4_Save,//C6S2
    Com4_Rad,//C6S1

    Com5_Led7,//C7S9
    Com5_Led3,//C7S8
    Com5_Led6,//C7S6
    Com5_Led4,//C7S4
    Com5_Led8,//C7S3
    Com5_Led1,//C7S2
    Com5_Led2,//C7S1
    Com5_Led5,//C7S10
    LED_END
}eLedName;
#else
   // COM5,//PIN19_P37_disCom5//C7//led
   // COM1,//PIN20_P36_disCom1//C6//pin4
   // COM2,//PIN21_P35_disCom2//C5//pin3
   // COM3,//PIN22_P34_disCom3//C4//pin2
	// //-------------------------------
   // COM4,//PIN23_P33_disCom4//C3//pin1

   // SEG1,//PIN24_P32_disSeg1//S1//pin11
   // SEG2,//PIN25_P31_disSeg2//S2//pin10
   // SEG3,//PIN26_P30_disSeg3//S3//pin9
   // SEG4,//PIN27_P10_disSeg4//S4//pin8
   // SEG5,//PIN29_P14_disSeg5//S8//pin7
   // SEG6,//PIN30_P15_disSeg6//S9//pin6
   // SEG7,//PIN31_P16_disSeg7//S10//pin5
typedef enum
{
    Com1_SegA,//C6S1
    Com1_SegB,//C6S2
    Com1_SegC,//C6S3
    Com1_SegD,//C6S4
    Com1_SegE,//C6S8
    Com1_SegF,//C6S9
    Com1_SegG,//C6S10
    Com2_SegA,//C5S1
    Com2_SegB,//C5S2
    Com2_SegC,//C5S3
    Com2_SegD,//C5S4
    Com2_SegE,//C5S8
    Com2_SegF,//C5S9
    Com2_SegG,//C5S10
    Com3_SegA,//C4S1
    Com3_SegB,//C4S2
    Com3_SegC,//C4S3
    Com3_SegD,//C4S4
    Com3_SegE,//C4S8
    Com3_SegF,//C4S9
    Com3_SegG,//C4S10
    Com4_Lack,//C3S1
    Com4_Dry,//C3S2
    Com4_Dot1,//C3S3
    Com4_Dot2,//C3S4
    Com4_Steam,//C3S8
    Com4_Push,//C3S9
    Com5_Led7,//C7S1
    Com5_Led6,//C7S2
    Com5_Led5,//C7S3
    Com5_Led4,//C7S4
    Com5_Led3,//C7S8
    Com5_Led2,//C7S9
    Com5_Led1,//C7S10
    LED_END
}eLedName;
#endif

#define RAM_SEG0    0
#define RAM_SEG1    1
#define RAM_SEG2    2
#define RAM_SEG3    3
#define RAM_SEG4    4
#define RAM_SEG5    5
#define RAM_SEG6    6
#define RAM_SEG7    7
#define RAM_SEG8    8
#define RAM_SEG9    9
#define RAM_SEG10   10
#define RAM_SEG11   11
#define RAM_SEG12   12
#define RAM_SEG13   13
#define RAM_SEG14   14
#define RAM_SEG15   15
#define RAM_SEG16   16
#define RAM_SEG17   17
#define RAM_SEG18   18
#define RAM_SEG19   19
#define RAM_SEG20   20
#define RAM_SEG21   21
#define RAM_SEG22   22
#define RAM_SEG23   23
#define RAM_SEG24   24
#define RAM_SEG25   25
#define RAM_SEG26   26
#define RAM_SEG27   27

#define RAM_COM0  ((unsigned char)0x01)
#define RAM_COM1  ((unsigned char)0x02)
#define RAM_COM2  ((unsigned char)0x04)
#define RAM_COM3  ((unsigned char)0x08)
#define RAM_COM4  ((unsigned char)0x10)
#define RAM_COM5  ((unsigned char)0x20)
#define RAM_COM6  ((unsigned char)0x40)
#define RAM_COM7  ((unsigned char)0x80)

typedef struct 
{
    /* data */
	unsigned char value:1;
	unsigned char seg:7;
    unsigned char com:8;
}Led_NameTypeDef;
#if NEWTPE1
#define Light_SetBrightness(x) (IOHCON1|=((x)<<4))//P3低四位IOH等级//POWER=P32
#else
#define Light_SetBrightness(x) (IOHCON0|=((x)<<6))//P1高四位IOH等级//POWER=P14
#endif
#define F_Com1_SegA         tLeds[Com1_SegA].value
#define F_Com1_SegB         tLeds[Com1_SegB].value
#define F_Com1_SegC         tLeds[Com1_SegC].value
#define F_Com1_SegD         tLeds[Com1_SegD].value
#define F_Com1_SegE         tLeds[Com1_SegE].value
#define F_Com1_SegF         tLeds[Com1_SegF].value
#define F_Com1_SegG         tLeds[Com1_SegG].value
#define F_Com2_SegA         tLeds[Com2_SegA].value
#define F_Com2_SegB         tLeds[Com2_SegB].value
#define F_Com2_SegC         tLeds[Com2_SegC].value
#define F_Com2_SegD         tLeds[Com2_SegD].value
#define F_Com2_SegE         tLeds[Com2_SegE].value
#define F_Com2_SegF         tLeds[Com2_SegF].value
#define F_Com2_SegG         tLeds[Com2_SegG].value
#define F_Com3_SegA         tLeds[Com3_SegA].value
#define F_Com3_SegB         tLeds[Com3_SegB].value
#define F_Com3_SegC         tLeds[Com3_SegC].value
#define F_Com3_SegD         tLeds[Com3_SegD].value
#define F_Com3_SegE         tLeds[Com3_SegE].value
#define F_Com3_SegF         tLeds[Com3_SegF].value
#define F_Com3_SegG         tLeds[Com3_SegG].value
#if NEWTPE1
#define F_Lack              tLeds[Com4_Lack].value//tLeds[Com4_SegA].value
#define F_Wsah              tLeds[Com4_Wash].value//tLeds[Com4_SegB].value
#define F_Dot1              tLeds[Com4_Dot1].value//tLeds[Com4_SegC].value
#define F_Dot2              tLeds[Com4_Dot2].value//tLeds[Com4_SegD].value
#define F_Sterilize         tLeds[Com4_Sterilize].value//tLeds[Com4_SegE].value
#define F_Save              tLeds[Com4_Save].value//tLeds[Com4_SegF].value
#define F_Lack_Rad          tLeds[Com4_Rad].value//tLeds[Com4_SegG].value

#define F_Led_Save          tLeds[Com5_Led7].value//tLeds[Com5_SegA].value//LED3
#define F_Led_Sterilize     tLeds[Com5_Led3].value//tLeds[Com5_SegB].value//LED7
#define F_Led_Srandard      tLeds[Com5_Led6].value//tLeds[Com5_SegC].value//LED6
#define F_Led_SelfClean     tLeds[Com5_Led4].value//tLeds[Com5_SegD].value//LED4
#define F_Led_Start         tLeds[Com5_Led8].value//tLeds[Com5_SegE].value//LED8
#define F_Led_Fast          tLeds[Com5_Led1].value//tLeds[Com5_SegF].value//LED1
#define F_Led_Power         tLeds[Com5_Led2].value//tLeds[Com5_SegG].value//LED2
#define F_Led_Light         tLeds[Com5_Led5].value//tLeds[Com5_SegDP].value//LED5

#define F_Steam							F_Sterilize   
#define F_Led_Steam         F_Led_Sterilize   
#define F_Led_Dry           F_Led_Save  
#define F_Led_Inlet         F_Led_Light 
#else
#define F_Lack              tLeds[Com4_Lack].value
#define F_Dry               tLeds[Com4_Dry].value
#define F_Dot1              tLeds[Com4_Dot1].value
#define F_Dot2              tLeds[Com4_Dot2].value
#define F_Steam             tLeds[Com4_Steam].value
#define F_Save              tLeds[Com4_Push].value
#define F_Led_Fast          tLeds[Com5_Led1].value
#define F_Led_Srandard      tLeds[Com5_Led2].value
#define F_Led_Steam         tLeds[Com5_Led3].value
#define F_Led_Dry           tLeds[Com5_Led4].value
#define F_Led_Inlet         tLeds[Com5_Led5].value
#define F_Led_Start         tLeds[Com5_Led6].value
#define F_Led_Power         tLeds[Com5_Led7].value
#endif


#define		SEG_NULL				0x00
#define		SEG_A					Bit_0
#define		SEG_B					Bit_1
#define		SEG_C					Bit_2
#define		SEG_D					Bit_3
#define		SEG_E					Bit_4
#define		SEG_F					Bit_5
#define		SEG_G					Bit_6
#define		SEG_DP					Bit_7
//*************************************
#define     DISP_PART_NULL          (SEG_NULL)
#define     DISP_NUM0_PART1         (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define     DISP_NUM1_PART1         (SEG_B | SEG_C)
#define     DISP_NUM2_PART1         (SEG_A | SEG_B | SEG_D | SEG_E | SEG_G)
#define     DISP_NUM3_PART1         (SEG_A | SEG_B | SEG_C | SEG_D | SEG_G)
#define     DISP_NUM4_PART1         (SEG_B | SEG_C | SEG_F | SEG_G)
#define     DISP_NUM5_PART1         (SEG_A | SEG_C | SEG_D | SEG_F | SEG_G)
#define     DISP_NUM6_PART1         (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define     DISP_NUM7_PART1         (SEG_A | SEG_B | SEG_C )
#define     DISP_NUM8_PART1         (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define     DISP_NUM9_PART1         (SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)
//*************************************
#define     DISP_CHAR_E_PART1       (SEG_A | SEG_D | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_H_PART1       (SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_C_PART1       (SEG_A | SEG_D | SEG_E | SEG_F)
#define     DISP_CHAR_O_PART1      	(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define     DISP_CHAR_P_PART1      	(SEG_A | SEG_B | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_L_PART1       (SEG_E | SEG_F | SEG_D )
#define     DISP_CHAR_U_PART1       (SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)
#define     DISP_CHAR_N_PART1       (SEG_A | SEG_B | SEG_C | SEG_E | SEG_F)
#define     DISP_CHAR_A_PART1       (SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_F_PART1       (SEG_A | SEG_E | SEG_F | SEG_G)
//*************************************
#define     DISP_CHAR_n_PART1       (SEG_C | SEG_E | SEG_G)
#define     DISP_CHAR_u_PART1       (SEG_C | SEG_D | SEG_E)
#define     DISP_CHAR_d_PART1       (SEG_B | SEG_C | SEG_D | SEG_E | SEG_G)
#define     DISP_CHAR_l_PART1       (SEG_E | SEG_F)
#define     DISP_CHAR_ll_PART1      (SEG_B | SEG_C | SEG_E | SEG_F)
#define     DISP_CHAR_h_PART1       (SEG_C | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_b_PART1       (SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_t_PART1       (SEG_D | SEG_E | SEG_F | SEG_G)
#define     DISP_CHAR_BAR_PART1     (SEG_G)   //-
#define     DISP_CHAR_DOT_PART1     (SEG_DP)    //.
//*************************************
#define     DISP_CHAR_NULL          10
#define     DISP_CHAR_E             11
#define     DISP_CHAR_H             12
#define     DISP_CHAR_C             13
#define     DISP_CHAR_BAR           14
#define     DISP_CHAR_DOT           15
#define     DISP_CHAR_n             16
#define     DISP_CHAR_N             17
#define     DISP_CHAR_u             18
#define     DISP_CHAR_U             19
#define     DISP_CHAR_d             20
#define     DISP_CHAR_l             21
#define     DISP_CHAR_L             22
#define     DISP_CHAR_ll            23
#define     DISP_CHAR_O           	24
#define     DISP_CHAR_P           	25
#define     DISP_CHAR_A           	26
#define     DISP_CHAR_F           	27
#define     DISP_CHAR_h           	28
#define     DISP_CHAR_b           	29
#define     DISP_CHAR_t           	30
//extern*****************************************************************
extern  UCHAR_XDATA  Com1_Buf;
extern  UCHAR_XDATA  Com2_Buf;
extern  UCHAR_XDATA  Com3_Buf;
// extern  UCHAR_XDATA  Com4_Buf;
// extern  UCHAR_XDATA  Leds_Buf;
//STATE_INDEX*************************************************************
#define DIGITAL_ALL_OFF         0
#define DIGITAL_ALL_ON		    1
#define LED_ALL_OFF             2
#define LED_ALL_ON              3
#define DIGITAL_STATE			4
#define LED_TESTTING			5
#define LED_PROG_STANDBY		6
#define LED_PROG_WORK           7
#define LED_POWER_OFF			8
#define LED_POWER_ON			9
#define DIGITAL_NULL           10
//void*******************************************************************
UCHAR code segNumsPart1[];
extern Led_NameTypeDef xdata tLeds[];
extern void Leds_Flesh(void);
extern void Trant_LED_Index(UCHAR_XDATA LED_Func_Index);
extern void Dot_Set(bit value);
#endif