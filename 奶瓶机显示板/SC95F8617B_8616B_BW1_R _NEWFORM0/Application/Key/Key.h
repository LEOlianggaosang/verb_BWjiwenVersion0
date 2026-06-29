/**
 *******************************************************************************
 * Copyright (c) 2025.5.12
 * 
 * @file    Key.h
 * @author  lianggaosang@qq.com
 * @brief   lianggaosang@qq.com
 * @brief   8616b奶瓶机显示板
 *
 *******************************************************************************
 */

#ifndef _KEY_H_
#define _KEY_H_

#include "product_config.h"
#include "TK\TK.h"
/* Key code define ---------------------------------------------------------- */
#define	KEY_NULL								(KEY_CODE_NONE == Key_Code)
#define	KEY_TEST                                (KEY_CODE_BOTH_TEST == Key_Code)
#define	KEY_VER                                 (KEY_CODE_BOTH_VER == Key_Code)

#define	KEY_ACT_SHORT                           (Key_ActionType == KEY_ACTION_SHORT)
#define	KEY_ACT_LONG                            (Key_ActionType == KEY_ACTION_LONG)
#define	KEY_ACT_LONGLONG                        (Key_ActionType == KEY_ACTION_LONG_LONG)
#define	KEY_ACT_NULL                            (Key_ActionType == KEY_ACTION_LEAVE)
#if NEWTPE1
#define	KEY_FAST                                (KEY_CODE_FAST == Key_Code)//key1
#define	KEY_POWER                               (KEY_CODE_POWER == Key_Code)//key2
#define	KEY_STERILIZE                           (KEY_CODE_STERILIZE == Key_Code)//key3
#define	KEY_SELFCLEAN                           (KEY_CODE_SELFCLEAN == Key_Code)//key4
#define	KEY_LIGHT                               (KEY_CODE_LIGHT == Key_Code)//key5
#define	KEY_STANDARD                            (KEY_CODE_STANDARD == Key_Code)//key6
#define	KEY_SAVE                                (KEY_CODE_SAVE == Key_Code)//key7
#define	KEY_START                               (KEY_CODE_START == Key_Code)//key8

#define	KEY_STEAM                               KEY_STERILIZE
#define	KEY_DRY                                 KEY_SAVE
#define	KEY_INLET                               KEY_LIGHT
#else
#define	KEY_FAST                                (KEY_CODE_FAST == Key_Code)
#define	KEY_STANDARD                            (KEY_CODE_STANDARD == Key_Code)
#define	KEY_STEAM                               (KEY_CODE_STEAM == Key_Code)
#define	KEY_DRY                                 (KEY_CODE_DRY == Key_Code)
#define	KEY_INLET                               (KEY_CODE_INLET == Key_Code)
#define	KEY_START                               (KEY_CODE_START == Key_Code)
#define	KEY_POWER                               (KEY_CODE_POWER == Key_Code)
#endif
extern UCHAR_XDATA TestKeyCnt;
extern UCHAR_XDATA FctKeyCnt;

#if NEWTPE1
extern WordFlag TestKeyAction_Flags;
#define  TestKeyActionFlag              TestKeyAction_Flags.f_word
#define  Key_TestEnter                  TestKeyAction_Flags.f_bits.no0
#define  Key_FastMune                   TestKeyAction_Flags.f_bits.no1
#define  Key_PowerCommand               TestKeyAction_Flags.f_bits.no2
#define  Key_SterilizeFunc              TestKeyAction_Flags.f_bits.no3
#define  Key_SelfCleanMune              TestKeyAction_Flags.f_bits.no4
#define  Key_LightCommand               TestKeyAction_Flags.f_bits.no5
#define  Key_SrandardMune               TestKeyAction_Flags.f_bits.no6
#define  Key_SaveFunc                   TestKeyAction_Flags.f_bits.no7
#define  Key_StartCommand               TestKeyAction_Flags.f_bits.no8

#define	Key_SteamFunc                   Key_SterilizeFunc
#define	Key_DryFunc                     Key_SaveFunc
#define	Key_InletCommand                Key_LightCommand
#else
extern WordFlag TestKeyAction_Flags;
#define  TestKeyActionFlag              TestKeyAction_Flags.f_word
#define  Key_TestEnter                  TestKeyAction_Flags.f_bits.no0
#define  Key_FastMune                   TestKeyAction_Flags.f_bits.no1
#define  Key_SrandardMune               TestKeyAction_Flags.f_bits.no2
#define  Key_SteamFunc                  TestKeyAction_Flags.f_bits.no3
#define  Key_DryFunc                    TestKeyAction_Flags.f_bits.no4
#define  Key_InletCommand               TestKeyAction_Flags.f_bits.no5
#define  Key_StartCommand               TestKeyAction_Flags.f_bits.no6
#define  Key_PowerCommand               TestKeyAction_Flags.f_bits.no7
#endif
// *******************************************************************************

#if NEWTPE1
extern WordFlag FctKeyAction_Flags;//17.FCT模式
#define  FctActionFlag                  FctKeyAction_Flags.f_word
#define  Fcting                         FctKeyAction_Flags.f_bits.no0
#define  Fct_FastMune                   FctKeyAction_Flags.f_bits.no1
#define  Fct_PowerCommand               FctKeyAction_Flags.f_bits.no2
#define  Fct_SterilizeFunc              FctKeyAction_Flags.f_bits.no3
#define  Fct_SelfCleanMune              FctKeyAction_Flags.f_bits.no4
#define  Fct_LightCommand               FctKeyAction_Flags.f_bits.no5
#define  Fct_SrandardMune               FctKeyAction_Flags.f_bits.no6
#define  Fct_SaveFunc                   FctKeyAction_Flags.f_bits.no7
#define  Fct_StartCommand               FctKeyAction_Flags.f_bits.no8

#define	Fct_SteamFunc                   Fct_SterilizeFunc
#define	Fct_DryFunc                     Fct_SaveFunc
#define	Fct_InletCommand                Fct_LightCommand
#else
extern WordFlag FctKeyAction_Flags;//17.FCT模式
#define  FctActionFlag                  FctKeyAction_Flags.f_word
#define  Fcting                         FctKeyAction_Flags.f_bits.no0
#define  Fct_FastMune                   FctKeyAction_Flags.f_bits.no1
#define  Fct_SrandardMune               FctKeyAction_Flags.f_bits.no2
#define  Fct_SteamFunc                  FctKeyAction_Flags.f_bits.no3
#define  Fct_DryFunc                    FctKeyAction_Flags.f_bits.no4
#define  Fct_InletCommand               FctKeyAction_Flags.f_bits.no5
#define  Fct_StartCommand               FctKeyAction_Flags.f_bits.no6
#define  Fct_PowerCommand               FctKeyAction_Flags.f_bits.no7
#endif
void Key_Control(void);
void Init_Key(void);

#endif
