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
* Copyright (C) 2022 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_MTU3_MTU4.c
* Component Version: 1.11.0
* Device(s)        : R5F565NEDxFP
* Description      : This file implements device driver for Config_MTU3_MTU4.
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
#include "Config_MTU3_MTU4.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MTU3_MTU4_Create
* Description  : This function initializes the MTU3 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU3_MTU4_Create(void)
{
    /* Release MTU channel 3 from stop state */
    MSTP(MTU3) = 0U;

    /* Enable read/write to MTU3, MTU4 registers */
    MTU.TRWERA.BIT.RWE = 1U;

    /* Stop MTU channel 3 counter */
    MTU.TSTRA.BIT.CST3 = 0U;
    MTU.TSTRA.BIT.CST4 = 0U;

    /* Set TGIA3 interrupt priority level */
    ICU.SLIAR223.BYTE = 0x10U;
    IPR(PERIA, INTA223) = _0F_MTU_PRIORITY_LEVEL15;

    /* Set TGIB3 interrupt priority level */
    ICU.SLIAR224.BYTE = 0x11U;
    IPR(PERIA, INTA224) = _0F_MTU_PRIORITY_LEVEL15;

    /* Set TGIA4 interrupt priority level */
    ICU.SLIAR228.BYTE = 0x15U;
    IPR(PERIA, INTA228) = _0F_MTU_PRIORITY_LEVEL15;

    /* Set TGIB4 interrupt priority level */
    ICU.SLIAR229.BYTE = 0x16U;
    IPR(PERIA, INTA229) = _0F_MTU_PRIORITY_LEVEL15;

    /* Set TCIV4 interrupt priority level */
    ICU.SLIAR232.BYTE = 0x19U;
    IPR(PERIA, INTA232) = _0F_MTU_PRIORITY_LEVEL15;

    /* MTU channel 3 is used as complementary PWM mode 1 */
    MTU3.TIER.BYTE = 0x00U;
    MTU4.TIER.BYTE = 0x00U;
    MTU.TITCR1A.BIT.T3AEN = 0U;
    MTU.TITCR1A.BIT.T4VEN = 0U;
    MTU3.TCR.BYTE = _00_MTU_PCLK_1 | _00_MTU_CKCL_DIS;
    MTU4.TCR.BYTE = _00_MTU_PCLK_1;
    MTU3.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU4.TCR2.BYTE = _00_MTU_PCLK_1;
    MTU.TGCRA.BYTE = _80_MTU_BDC_OUT;
    MTU3.TCNT = _04B0_3TCNT_VALUE;
    MTU4.TCNT = 0x0000U;
    MTU.TSYRA.BIT.SYNC3 = 0U;
    MTU.TSYRA.BIT.SYNC4 = 0U;
    MTU3.TGRB = _0064_3TGRB_VALUE;
    MTU3.TGRD = _0064_3TGRB_VALUE;
    MTU4.TGRA = _0064_4TGRA_VALUE;
    MTU4.TGRC = _0064_4TGRA_VALUE;
    MTU4.TGRB = _0064_4TGRB_VALUE;
    MTU4.TGRD = _0064_4TGRB_VALUE;
    MTU.TDERA.BIT.TDER = 1U;
    MTU.TDDRA = _04B0_TDDRA_VALUE;
    MTU.TCDRA = _2EE0_TCDRA_VALUE;
    MTU.TCBRA = _2EE0_TCDRA_VALUE;
    MTU3.TGRA = _1C20_SUM_VALUE;
    MTU3.TGRC = _1C20_SUM_VALUE;
    MTU.TOCR1A.BYTE = _00_MTU_PSYE_DISABLE | _08_MTU_TOCL_DISABLE | _04_MTU_TOCS_TOCR2;
    MTU.TOCR2A.BYTE = _00_MTU_TOLBR_DIS | _00_MTU_OLS3N_HL | _00_MTU_OLS3P_HL | _00_MTU_OLS2N_HL | _00_MTU_OLS2P_HL | 
                      _00_MTU_OLS1N_HL | _00_MTU_OLS1P_HL;
    MTU.TOLBRA.BYTE = MTU.TOCR2A.BYTE & 0x3FU;
    MTU3.TIER.BYTE = _01_MTU_TGIEA_ENABLE | _02_MTU_TGIEB_ENABLE | _00_MTU_TTGE_DISABLE;
    MTU4.TIER.BYTE = _01_MTU_TGIEA_ENABLE | _02_MTU_TGIEB_ENABLE | _10_MTU_TCIEV_ENABLE | _00_MTU_TTGE2_DISABLE;
    MTU.TITMRA.BIT.TITM = 0U;
    MTU.TITCR1A.BYTE = _00_MTU_TACOR_3_6_SKIP_COUNT_0 | _00_MTU_TVCOR_4_7_SKIP_COUNT_0;
    MTU3.TMDR1.BYTE = _0D_MTU_CMT1 | _10_MTU_BFA_BUFFER | _20_MTU_BFB_BUFFER;
    MTU.TOERA.BYTE = _E0_MTU_OE4D_ENABLE | _D0_MTU_OE4C_ENABLE | _C8_MTU_OE3D_ENABLE | _C4_MTU_OE4B_ENABLE | 
                     _C2_MTU_OE4A_ENABLE | _C1_MTU_OE3B_ENABLE;

    /* Disable read/write to MTU3, MTU4 registers */
    MTU.TRWERA.BIT.RWE = 0U;

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

    R_Config_MTU3_MTU4_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU3_MTU4_Start
* Description  : This function starts the MTU3 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU3_MTU4_Start(void)
{
    /* Enable TGIA3 interrupt in ICU */
    IEN(PERIA, INTA223) = 1U;

    /* Enable TGIB3 interrupt in ICU */
    IEN(PERIA, INTA224) = 1U;

    /* Enable TGIA4 interrupt in ICU */
    IEN(PERIA, INTA228) = 1U;

    /* Enable TGIB4 interrupt in ICU */
    IEN(PERIA, INTA229) = 1U;

    /* Enable TCIV4 interrupt in ICU */
    IEN(PERIA, INTA232) = 1U;

    /* Start MTU3, MTU4 channel counter */
    MTU.TSTRA.BYTE |= (_40_MTU_CST3_ON | _80_MTU_CST4_ON);
}

/***********************************************************************************************************************
* Function Name: R_Config_MTU3_MTU4_Stop
* Description  : This function stops the MTU3 channel counter
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_MTU3_MTU4_Stop(void)
{
    /* Disable TGIA3 interrupt in ICU */
    IEN(PERIA, INTA223) = 0U;

    /* Disable TGIB3 interrupt in ICU */
    IEN(PERIA, INTA224) = 0U;

    /* Disable TGIA4 interrupt in ICU */
    IEN(PERIA, INTA228) = 0U;

    /* Disable TGIB4 interrupt in ICU */
    IEN(PERIA, INTA229) = 0U;

    /* Disable TCIV4 interrupt in ICU */
    IEN(PERIA, INTA232) = 0U;

    /* Stop MTU3, MTU4 channel counter */
    MTU.TSTRA.BIT.CST3 = 0U;
    MTU.TSTRA.BIT.CST4 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
