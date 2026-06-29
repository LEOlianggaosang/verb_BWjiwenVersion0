/**
 *******************************************************************************
 * Copyright (c) 2024.8.3
 *  
 * @file    System.c
 * @author  lianggaosang@qq.com
 * @brief
 *******************************************************************************
 */
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "..\SC95F861x_C.H"
#include "System.h"

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function process of Reset.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
unsigned char CG_ReadResetSource( void )
{
  unsigned char resetflag = 0;
  /* Start user code. Do not edit comment generated here */
  return resetflag;
  /* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits the system.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
unsigned char System_Init(void)
{

	return CG_ReadResetSource();
}
