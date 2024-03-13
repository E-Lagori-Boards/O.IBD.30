/*******************************************************************************
* File Name: wf.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "wf.h"

static wf_BACKUP_STRUCT  wf_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: wf_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet wf_SUT.c usage_wf_Sleep_Wakeup
*******************************************************************************/
void wf_Sleep(void)
{
    #if defined(wf__PC)
        wf_backup.pcState = wf_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            wf_backup.usbState = wf_CR1_REG;
            wf_USB_POWER_REG |= wf_USBIO_ENTER_SLEEP;
            wf_CR1_REG &= wf_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(wf__SIO)
        wf_backup.sioState = wf_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        wf_SIO_REG &= (uint32)(~wf_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: wf_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to wf_Sleep() for an example usage.
*******************************************************************************/
void wf_Wakeup(void)
{
    #if defined(wf__PC)
        wf_PC = wf_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            wf_USB_POWER_REG &= wf_USBIO_EXIT_SLEEP_PH1;
            wf_CR1_REG = wf_backup.usbState;
            wf_USB_POWER_REG &= wf_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(wf__SIO)
        wf_SIO_REG = wf_backup.sioState;
    #endif
}


/* [] END OF FILE */
