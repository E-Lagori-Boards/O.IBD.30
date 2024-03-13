/*******************************************************************************
* File Name: Clock_micros.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_micros_H)
#define CY_CLOCK_Clock_micros_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clock_micros_StartEx(uint32 alignClkDiv);
#define Clock_micros_Start() \
    Clock_micros_StartEx(Clock_micros__PA_DIV_ID)

#else

void Clock_micros_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clock_micros_Stop(void);

void Clock_micros_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_micros_GetDividerRegister(void);
uint8  Clock_micros_GetFractionalDividerRegister(void);

#define Clock_micros_Enable()                         Clock_micros_Start()
#define Clock_micros_Disable()                        Clock_micros_Stop()
#define Clock_micros_SetDividerRegister(clkDivider, reset)  \
    Clock_micros_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_micros_SetDivider(clkDivider)           Clock_micros_SetDividerRegister((clkDivider), 1u)
#define Clock_micros_SetDividerValue(clkDivider)      Clock_micros_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clock_micros_DIV_ID     Clock_micros__DIV_ID

#define Clock_micros_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clock_micros_CTRL_REG   (*(reg32 *)Clock_micros__CTRL_REGISTER)
#define Clock_micros_DIV_REG    (*(reg32 *)Clock_micros__DIV_REGISTER)

#define Clock_micros_CMD_DIV_SHIFT          (0u)
#define Clock_micros_CMD_PA_DIV_SHIFT       (8u)
#define Clock_micros_CMD_DISABLE_SHIFT      (30u)
#define Clock_micros_CMD_ENABLE_SHIFT       (31u)

#define Clock_micros_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clock_micros_CMD_DISABLE_SHIFT))
#define Clock_micros_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clock_micros_CMD_ENABLE_SHIFT))

#define Clock_micros_DIV_FRAC_MASK  (0x000000F8u)
#define Clock_micros_DIV_FRAC_SHIFT (3u)
#define Clock_micros_DIV_INT_MASK   (0xFFFFFF00u)
#define Clock_micros_DIV_INT_SHIFT  (8u)

#else 

#define Clock_micros_DIV_REG        (*(reg32 *)Clock_micros__REGISTER)
#define Clock_micros_ENABLE_REG     Clock_micros_DIV_REG
#define Clock_micros_DIV_FRAC_MASK  Clock_micros__FRAC_MASK
#define Clock_micros_DIV_FRAC_SHIFT (16u)
#define Clock_micros_DIV_INT_MASK   Clock_micros__DIVIDER_MASK
#define Clock_micros_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clock_micros_H) */

/* [] END OF FILE */
