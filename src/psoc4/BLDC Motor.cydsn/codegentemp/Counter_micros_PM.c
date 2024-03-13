/*******************************************************************************
* File Name: Counter_micros_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_micros.h"

static Counter_micros_backupStruct Counter_micros_backup;


/*******************************************************************************
* Function Name: Counter_micros_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_micros_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_micros_SaveConfig(void) 
{
    #if (!Counter_micros_UsingFixedFunction)

        Counter_micros_backup.CounterUdb = Counter_micros_ReadCounter();

        #if(!Counter_micros_ControlRegRemoved)
            Counter_micros_backup.CounterControlRegister = Counter_micros_ReadControlRegister();
        #endif /* (!Counter_micros_ControlRegRemoved) */

    #endif /* (!Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_micros_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_micros_RestoreConfig(void) 
{      
    #if (!Counter_micros_UsingFixedFunction)

       Counter_micros_WriteCounter(Counter_micros_backup.CounterUdb);

        #if(!Counter_micros_ControlRegRemoved)
            Counter_micros_WriteControlRegister(Counter_micros_backup.CounterControlRegister);
        #endif /* (!Counter_micros_ControlRegRemoved) */

    #endif /* (!Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_micros_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_micros_Sleep(void) 
{
    #if(!Counter_micros_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_micros_CTRL_ENABLE == (Counter_micros_CONTROL & Counter_micros_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_micros_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_micros_backup.CounterEnableState = 0u;
        }
    #else
        Counter_micros_backup.CounterEnableState = 1u;
        if(Counter_micros_backup.CounterEnableState != 0u)
        {
            Counter_micros_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_micros_ControlRegRemoved) */
    
    Counter_micros_Stop();
    Counter_micros_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_micros_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_micros_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_micros_Wakeup(void) 
{
    Counter_micros_RestoreConfig();
    #if(!Counter_micros_ControlRegRemoved)
        if(Counter_micros_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_micros_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_micros_ControlRegRemoved) */
    
}


/* [] END OF FILE */
