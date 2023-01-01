/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Pin.c
* Version          : 1.0.2
* Device(s)        : R5F566NNHxFP
* Description      : This file implements SMC pin code generation.
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Pins_Create
* Description  : This function initializes Smart Configurator pins
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Pins_Create(void)
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* Set MTIOC3B pin */
    MPC.P22PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x04U;

    /* Set MTIOC3D pin */
    MPC.P23PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x08U;

    /* Set MTIOC4A pin */
    MPC.P24PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x10U;

    /* Set MTIOC4B pin */
    MPC.P17PFS.BYTE = 0x08U;
    PORT1.PMR.BYTE |= 0x80U;

    /* Set MTIOC4C pin */
    MPC.P25PFS.BYTE = 0x01U;
    PORT2.PMR.BYTE |= 0x20U;

    /* Set MTIOC4D pin */
    MPC.P31PFS.BYTE = 0x01U;
    PORT3.PMR.BYTE |= 0x02U;

    /* Set SCL0 pin */
    MPC.P12PFS.BYTE = 0x0FU;
    PORT1.PMR.BYTE |= 0x04U;

    /* Set SCL1 pin */
    MPC.P21PFS.BYTE = 0x0FU;
    PORT2.PMR.BYTE |= 0x02U;

    /* Set SDA0 pin */
    MPC.P13PFS.BYTE = 0x0FU;
    PORT1.PMR.BYTE |= 0x08U;

    /* Set SDA1 pin */
    MPC.P20PFS.BYTE = 0x0FU;
    PORT2.PMR.BYTE |= 0x01U;

    /* Set SSCL0 pin */
    MPC.P33PFS.BYTE = 0x0BU;
    PORT3.PMR.BYTE |= 0x08U;

    /* Set SSCL1 pin */
    MPC.P30PFS.BYTE = 0x0AU;
    PORT3.PMR.BYTE |= 0x01U;

    /* Set SSDA0 pin */
    MPC.P32PFS.BYTE = 0x0BU;
    PORT3.PMR.BYTE |= 0x04U;

    /* Set SSDA1 pin */
    MPC.P26PFS.BYTE = 0x0AU;
    PORT2.PMR.BYTE |= 0x40U;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

