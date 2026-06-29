/**
 *******************************************************************************
 * Copyright (c) 2025.4.26

 *  
 * @file    Gpio.c
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC95F8617_ENABLED
#include "..\SC95F861x_C.H"
#endif
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#endif

#include "Gpio.h"

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function configures the gpio.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Gpio_Init(Gpio_InitTypeDef *gpio)
{
	if (gpio == NULL)
	{
		return;
	}

	switch(gpio->port)
	{
		case PORT0:
			if (gpio->mode == GPIO_MODE_INPUT)
			{
				P0CON &= (~gpio->pin);
			}
			else
			{
				P0CON |= gpio->pin;
			}
			if (gpio->pull == GPIO_NO_PULL)
			{
				P0PH &= (~gpio->pin);
			}
			else
			{
				P0PH |= gpio->pin;
			}
			break;
		case PORT1:
			if (gpio->mode == GPIO_MODE_INPUT)
			{
				P1CON &= (~gpio->pin);
			}
			else
			{
				P1CON |= gpio->pin;
			}
			if (gpio->pull == GPIO_NO_PULL)
			{
				P1PH &= (~gpio->pin);
			}
			else
			{
				P1PH |= gpio->pin;
			}		
			break;
		case PORT2:
			if (gpio->mode == GPIO_MODE_INPUT)
			{
				P2CON &= (~gpio->pin);
			}
			else
			{
				P2CON |= gpio->pin;
			}
			if (gpio->pull == GPIO_NO_PULL)
			{
				P2PH &= (~gpio->pin);
			}
			else
			{
				P2PH |= gpio->pin;
			}		
			break;
		case PORT3:
			if (gpio->mode == GPIO_MODE_INPUT)
			{
				P3CON &= (~gpio->pin);
			}
			else
			{
				P3CON |= gpio->pin;
			}
			if (gpio->pull == GPIO_NO_PULL)
			{
				P3PH &= (~gpio->pin);
			}
			else
			{
				P3PH |= gpio->pin;
			}		
			break;
		case PORT4:
			if (gpio->mode == GPIO_MODE_INPUT)
			{
				P4CON &= (~gpio->pin);
			}
			else
			{
				P4CON |= gpio->pin;
			}
			if (gpio->pull == GPIO_NO_PULL)
			{
				P4PH &= (~gpio->pin);
			}
			else
			{
				P4PH |= gpio->pin;
			}			
			break;
		case PORT5:
			if (gpio->mode == GPIO_MODE_INPUT)
			{
				P5CON &= (~gpio->pin);
			}
			else
			{
				P5CON |= gpio->pin;
			}
			if (gpio->pull == GPIO_NO_PULL)
			{
				P5PH &= (~gpio->pin);
			}
			else
			{
				P5PH |= gpio->pin;
			}			
			break;
		default:
			break;												
	}
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function set the gpio.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Gpio_Set(Gpio_InitTypeDef *gpio, unsigned char status)
{
	switch(gpio->port)
	{
		case PORT0:
			if (status == ON)
			{
				P0 |= gpio->pin;
			}
			else
			{
				P0 &= (~gpio->pin);
			}
			break;
		case PORT1:
			if (status == ON)
			{
				P1 |= gpio->pin;
			}
			else
			{
				P1 &= (~gpio->pin);
			}
			break;
		case PORT2:
			if (status == ON)
			{
				P2 |= gpio->pin;
			}
			else
			{
				P2 &= (~gpio->pin);
			}
			break;
		case PORT3:
			if (status == ON)
			{
				P3 |= gpio->pin;
			}
			else
			{
				P3 &= (~gpio->pin);
			}
			break;
		case PORT4:
			if (status == ON)
			{
				P4 |= gpio->pin;
			}
			else
			{
				P4 &= (~gpio->pin);
			}
			break;
		case PORT5:
			if (status == ON)
			{
				P5 |= gpio->pin;
			}
			else
			{
				P5 &= (~gpio->pin);
			}
			break;
		default:
			break;												
	}
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function get the gpio data.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
unsigned char Gpio_Get(Gpio_InitTypeDef *gpio)
{
	unsigned char status;

	switch(gpio->port)
	{
		case PORT0:
			status = P0 & gpio->pin;
			break;
		case PORT1:
			status = P1 & gpio->pin;
			break;
		case PORT2:
			status = P2 & gpio->pin;
			break;
		case PORT3:
			status = P3 & gpio->pin;
			break;
		case PORT4:
			status = P4 & gpio->pin;
			break;
		case PORT5:
			status = P5 & gpio->pin;
			break;
		default:
			break;												
	}
	if (status != OFF)
		status = ON;		
	return status;
}
