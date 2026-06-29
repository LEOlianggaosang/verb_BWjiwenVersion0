/**
 *******************************************************************************
 * Copyright (c) 2024.8.5
 *  
 * @file    TicketHandling.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _TICKET_HANDLING_H_
#define _TICKET_HANDLING_H_

#include "TimerDrv.h"
#include "product_config.h"

void Init_TicketHandling(void);

extern WordFlag Timer_Flags;
#define  TimerFlag              Timer_Flags.f_word
#define  F_Base1ms              Timer_Flags.f_bits.no0
#define  F_Base10ms             Timer_Flags.f_bits.no1
#define  F_Base100ms            Timer_Flags.f_bits.no2
#define  F_Blink500ms           Timer_Flags.f_bits.no3
#define  F_Base1s               Timer_Flags.f_bits.no4
#define  F_Light10ms            Timer_Flags.f_bits.no5
#define  F_TK10ms               Timer_Flags.f_bits.no6
#define  F_Work1s               Timer_Flags.f_bits.no7
#define  F_Display100ms         Timer_Flags.f_bits.no8
#define  F_Error1s              Timer_Flags.f_bits.no9
#define  F_Power100ms           Timer_Flags.f_bits.no10


#endif
