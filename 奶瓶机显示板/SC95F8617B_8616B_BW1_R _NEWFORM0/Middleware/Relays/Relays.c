/**
 *******************************************************************************
 * Copyright (c) 2022
 *
 * @file    Relays.c
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief   继电器控制
 *
 *******************************************************************************
 */

#include "Relays.h"

ByteFlag Relay_Enables = {0};
ByteFlag Relay_buf_Enables = { 0 };//故障修改2.16  继电器闭合和断开延时


//故障修改2.16  继电器闭合和断开延时
#define  RELAY_BUF_HEAT_ENABLE    Relay_buf_Enables.f_bits.no0    ///<加热器使能
#define  RELAY_BUF_WP_ENABLE      Relay_buf_Enables.f_bits.no1    ///<洗涤使能
#define  RELAY_BUF_DR_ENABLE      Relay_buf_Enables.f_bits.no2    ///<排水使能
#define  RELAY_BUF_IV_ENABLE      Relay_buf_Enables.f_bits.no3    ///<进水使能
#define  RELAY_BUF_PTC_ENABLE     Relay_buf_Enables.f_bits.no4    ///<PTC 使能
#define  RELAY_BUF_SV_ENABLE      Relay_buf_Enables.f_bits.no5    ///<软水器使能
#define  RELAY_BUF_DV_ENABLE      Relay_buf_Enables.f_bits.no6    ///<分配器使能
#define  RELAY_BUF_HALF_ENABLE    Relay_buf_Enables.f_bits.no7    ///<半载阀使能

//故障修改2.16  继电器闭合和断开延时
void Relay_Drive(void)
{
    RELAY_BUF_WP_ENABLE = RELAY_WP_ENABLE;
    RELAY_BUF_DR_ENABLE = RELAY_DR_ENABLE;
    RELAY_BUF_IV_ENABLE = RELAY_IV_ENABLE;
    RELAY_BUF_PTC_ENABLE = RELAY_PTC_ENABLE;
    RELAY_BUF_SV_ENABLE = RELAY_SV_ENABLE;
    RELAY_BUF_DV_ENABLE = RELAY_DV_ENABLE;
}

//4ms执行一次  注意自检主循环也要加上
void Relay_Drive_4ms_do(void)//故障修改2.16  继电器闭合和断开延时
{
    static UCHAR_XDATA index = 0;
    ++index;
    if (index < 5)
        SetPin(WASHING_PUMP_OUTPUT, RELAY_BUF_WP_ENABLE);
    else if (index < 10)
        SetPin(DRAIN_PUMP_OUTPUT, RELAY_BUF_DR_ENABLE);
    else if (index < 15)
        SetPin(IV_OUTPUT, RELAY_BUF_IV_ENABLE);
    else if (index < 20)
        SetPin(SV_OUTPUT, RELAY_BUF_SV_ENABLE);
    else if (index < 25)
        SetPin(DV_OUTPUT, RELAY_BUF_DV_ENABLE);
    else if (index < 30)
        PORT_PTC = RELAY_BUF_PTC_ENABLE;		
    else
        index = 0;
}

void Init_Relays(void)
{

}
