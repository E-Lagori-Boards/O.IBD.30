/*******************************************************************************
* File Name: PWM_C_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_C.h"

static PWM_C_BACKUP_STRUCT PWM_C_backup;


/*******************************************************************************
* Function Name: PWM_C_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_C_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_C_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_C_Sleep(void)
{
    if(0u != (PWM_C_BLOCK_CONTROL_REG & PWM_C_MASK))
    {
        PWM_C_backup.enableState = 1u;
    }
    else
    {
        PWM_C_backup.enableState = 0u;
    }

    PWM_C_Stop();
    PWM_C_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_C_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_C_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: PWM_C_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void PWM_C_Wakeup(void)
{
    PWM_C_RestoreConfig();

    if(0u != PWM_C_backup.enableState)
    {
        PWM_C_Enable();
    }
}


/* [] END OF FILE */
