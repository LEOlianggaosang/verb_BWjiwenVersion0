/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    Gpio.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _GPIO_H_
#define _GPIO_H_

#ifndef NULL
#define NULL    0
#endif

#define ON      1
#define OFF     0

typedef enum 
{
    PORT0 = 0,
    PORT1 = 1,
    PORT2 = 2,
    PORT3 = 3,
    PORT4 = 4,
    PORT5 = 5,
    PORT_NULL
}ePort;

#define GPIO_PIN_0  ((unsigned char)0x01)
#define GPIO_PIN_1  ((unsigned char)0x02)
#define GPIO_PIN_2  ((unsigned char)0x04)
#define GPIO_PIN_3  ((unsigned char)0x08)
#define GPIO_PIN_4  ((unsigned char)0x10)
#define GPIO_PIN_5  ((unsigned char)0x20)
#define GPIO_PIN_6  ((unsigned char)0x40)
#define GPIO_PIN_7  ((unsigned char)0x80)

#define GPIO_MODE_INPUT     ((unsigned char)0x00)
#define GPIO_MODE_OUTPUT    ((unsigned char)0x01)

#define GPIO_NO_PULL     ((unsigned char)0x00)
#define GPIO_PULL_UP     ((unsigned char)0x01)

typedef struct 
{
    /* data */
    ePort port;
    unsigned char pin;
    unsigned char mode;
    unsigned char pull;
}Gpio_InitTypeDef;

//public functions
void Gpio_Init(Gpio_InitTypeDef *gpio);
void Gpio_Set(Gpio_InitTypeDef *gpio, unsigned char status);
unsigned char Gpio_Get(Gpio_InitTypeDef *gpio);
#endif
