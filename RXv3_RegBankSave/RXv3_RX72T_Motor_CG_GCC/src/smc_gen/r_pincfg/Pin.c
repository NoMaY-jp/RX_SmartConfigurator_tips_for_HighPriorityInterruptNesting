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
* Device(s)        : R5F572TKGxFB
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

    /* Set AN000 pin */
    MPC.P40PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xFEU;
    PORT4.PDR.BYTE &= 0xFEU;

    /* Set AN001 pin */
    MPC.P41PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xFDU;
    PORT4.PDR.BYTE &= 0xFDU;

    /* Set AN002 pin */
    MPC.P42PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xFBU;
    PORT4.PDR.BYTE &= 0xFBU;

    /* Set AN003 pin */
    MPC.P43PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xF7U;
    PORT4.PDR.BYTE &= 0xF7U;

    /* Set AN100 pin */
    MPC.P44PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xEFU;
    PORT4.PDR.BYTE &= 0xEFU;

    /* Set AN101 pin */
    MPC.P45PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xDFU;
    PORT4.PDR.BYTE &= 0xDFU;

    /* Set AN102 pin */
    MPC.P46PFS.BYTE = 0x80U;
    PORT4.PMR.BYTE &= 0xBFU;
    PORT4.PDR.BYTE &= 0xBFU;

    /* Set MTIOC3B pin */
    MPC.P12PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x04U;

    /* Set MTIOC3D pin */
    MPC.P74PFS.BYTE = 0x01U;
    PORT7.PMR.BYTE |= 0x10U;

    /* Set MTIOC4A pin */
    MPC.P13PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x08U;

    /* Set MTIOC4B pin */
    MPC.P14PFS.BYTE = 0x01U;
    PORT1.PMR.BYTE |= 0x10U;

    /* Set MTIOC4C pin */
    MPC.P75PFS.BYTE = 0x01U;
    PORT7.PMR.BYTE |= 0x20U;

    /* Set MTIOC4D pin */
    MPC.P76PFS.BYTE = 0x01U;
    PORT7.PMR.BYTE |= 0x40U;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

