/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************
* Copyright (C) 2010 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
******************************************************************************
* File Name    : R_PG_Timer_MTU_U0.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
* Limitations  : 
******************************************************************************
* History : 21.09.2012 Version Description
*         :   
******************************************************************************/


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "R_PG_Timer_MTU_U0.h"


/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_StopModule_MTU_U0(void)
*
* Function Name: R_PG_Timer_StopModule_MTU_U0
*
* Description  : Shut down the MTU unit
*
* Arguments    : None
*
* Return Value : true  : Shutting down succeeded.
*              : false : Shutting down failed.
*
* Calling Functions : R_MTU3_Destroy
*
* Details      : Please refer to the Reference Manual.
******************************************************************************/
bool R_PG_Timer_StopModule_MTU_U0(void)
{
	return R_MTU3_Destroy();
}

/******************************************************************************
* ID           : 
*
* Include      : 
*
* Declaration  : bool R_PG_Timer_SynchronouslyStartCount_MTU_U0(bool ch0, bool ch1, bool ch2, bool ch3, bool ch4, bool ch6, bool ch7)
*
* Function Name: R_PG_Timer_SynchronouslyStartCount_MTU_U0
*
* Description  : Synchronously start the MTU count
*
* Arguments    : bool ch0 : Synchronous start setting for MTU3_0.TCNT (1: enabled  0: disabled)
*              : bool ch1 : Synchronous start setting for MTU3_1.TCNT (1: enabled  0: disabled)
*              : bool ch2 : Synchronous start setting for MTU3_2.TCNT (1: enabled  0: disabled)
*              : bool ch3 : Synchronous start setting for MTU3_3.TCNT (1: enabled  0: disabled)
*              : bool ch4 : Synchronous start setting for MTU3_4.TCNT (1: enabled  0: disabled)
*              : bool ch6 : Synchronous start setting for MTU3_6.TCNT (1: enabled  0: disabled)
*              : bool ch7 : Synchronous start setting for MTU3_7.TCNT (1: enabled  0: disabled)
*
* Return Value : true  : Resuming count succeeded.
*              : false : Resuming count failed.
*
* Calling Functions : R_MTU3_ControlUnit
*                   : R_MTU3_ControlUnit_load_defaults
*
* Details      : Please refer to the Reference Manual.
******************************************************************************/
bool R_PG_Timer_SynchronouslyStartCount_MTU_U0(bool ch0, bool ch1, bool ch2, bool ch3, bool ch4, bool ch6, bool ch7)
{
	R_MTU3_ControlUnit_structure parameters;

	R_MTU3_ControlUnit_load_defaults( &parameters );


	if( ch0 ){
		parameters.data2 |= PDL_MTU3_START_CH_0;
	}
	if( ch1 ){
		parameters.data2 |= PDL_MTU3_START_CH_1;
	}
	if( ch2 ){
		parameters.data2 |= PDL_MTU3_START_CH_2;
	}
	if( ch3 ){
		parameters.data2 |= PDL_MTU3_START_CH_3;
	}
	if( ch4 ){
		parameters.data2 |= PDL_MTU3_START_CH_4;
	}
	if( ch6 ){
		parameters.data2 |= PDL_MTU3_START_CH_6;
	}
	if( ch7 ){
		parameters.data2 |= PDL_MTU3_START_CH_7;
	}

	return R_MTU3_ControlUnit(
		0,
		&parameters
	);
}



