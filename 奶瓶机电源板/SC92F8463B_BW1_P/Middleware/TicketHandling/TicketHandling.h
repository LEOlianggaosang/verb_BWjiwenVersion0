/**
 *******************************************************************************
 * Copyright (c) 20250117
 *  
 * @file    TicketHandling.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _TICKET_HANDLING_H_
#define _TICKET_HANDLING_H_

#include "product_config.h"

void Init_TicketHandling(void);

extern WordFlag Timer_Flags;
#define  TimerFlag              Timer_Flags.f_word
#define  F_Base1ms              Timer_Flags.f_bits.no0
#define  F_Base10ms             Timer_Flags.f_bits.no1
#define  F_Base100ms            Timer_Flags.f_bits.no2
#define  F_Blink500ms           Timer_Flags.f_bits.no3
#define  F_Base1s               Timer_Flags.f_bits.no4
#define  Flow_FlagBuf           Timer_Flags.f_bits.no5
#define  Buzz_Timer10ms         Timer_Flags.f_bits.no6
#define  Load_Timer10ms         Timer_Flags.f_bits.no7
#define  Read_Timer10ms         Timer_Flags.f_bits.no8
#define  Temp_Timer10ms         Timer_Flags.f_bits.no9
#define  Disp_Timer100ms        Timer_Flags.f_bits.no10
#define  Flow_Timer100ms        Timer_Flags.f_bits.no11
#define  Feedback_FlagBuf       Timer_Flags.f_bits.no12

#endif
