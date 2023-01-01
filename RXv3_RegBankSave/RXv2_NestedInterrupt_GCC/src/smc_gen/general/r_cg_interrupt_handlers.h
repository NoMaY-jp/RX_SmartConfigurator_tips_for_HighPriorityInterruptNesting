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
* File Name        : r_cg_interrupt_handlers.h
* Version          : 1.2.111
* Device(s)        : R5F565NEDxFP
* Description      : This file declares interrupt handlers.
***********************************************************************************************************************/

#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* RIIC0 RXI0 */
void r_Config_RIIC0_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(RIIC0,RXI0))));

/* RIIC0 TXI0 */
void r_Config_RIIC0_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(RIIC0,TXI0))));

/* SCI0 RXI0 */
void r_Config_SCI0_receive_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI0,RXI0))));

/* SCI0 TXI0 */
void r_Config_SCI0_transmit_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(SCI0,TXI0))));

/* MTU3 TGIA3 */
void r_Config_MTU3_MTU4_tgia3_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(PERIA,INTA223))));

/* MTU3 TGIB3 */
void r_Config_MTU3_MTU4_tgib3_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(PERIA,INTA224))));

/* MTU4 TGIA4 */
void r_Config_MTU3_MTU4_c4_tgia4_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(PERIA,INTA228))));

/* MTU4 TGIB4 */
void r_Config_MTU3_MTU4_c4_tgib4_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(PERIA,INTA229))));

/* MTU4 TCIV4 */
void r_Config_MTU3_MTU4_c4_tciv4_interrupt(void) __attribute__ ((interrupt(".rvectors",VECT(PERIA,INTA232))));

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
