/*******************************************************************************
* File Name: vr.c  
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
#include "vr.h"

static vr_BACKUP_STRUCT  vr_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: vr_Sleep
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
*  \snippet vr_SUT.c usage_vr_Sleep_Wakeup
*******************************************************************************/
void vr_Sleep(void)
{
    #if defined(vr__PC)
        vr_backup.pcState = vr_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            vr_backup.usbState = vr_CR1_REG;
            vr_USB_POWER_REG |= vr_USBIO_ENTER_SLEEP;
            vr_CR1_REG &= vr_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(vr__SIO)
        vr_backup.sioState = vr_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        vr_SIO_REG &= (uint32)(~vr_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: vr_Wakeup
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
*  Refer to vr_Sleep() for an example usage.
*******************************************************************************/
void vr_Wakeup(void)
{
    #if defined(vr__PC)
        vr_PC = vr_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            vr_USB_POWER_REG &= vr_USBIO_EXIT_SLEEP_PH1;
            vr_CR1_REG = vr_backup.usbState;
            vr_USB_POWER_REG &= vr_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(vr__SIO)
        vr_SIO_REG = vr_backup.sioState;
    #endif
}


/* [] END OF FILE */
