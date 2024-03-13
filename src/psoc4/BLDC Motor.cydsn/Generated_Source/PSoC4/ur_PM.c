/*******************************************************************************
* File Name: ur.c  
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
#include "ur.h"

static ur_BACKUP_STRUCT  ur_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: ur_Sleep
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
*  \snippet ur_SUT.c usage_ur_Sleep_Wakeup
*******************************************************************************/
void ur_Sleep(void)
{
    #if defined(ur__PC)
        ur_backup.pcState = ur_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            ur_backup.usbState = ur_CR1_REG;
            ur_USB_POWER_REG |= ur_USBIO_ENTER_SLEEP;
            ur_CR1_REG &= ur_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ur__SIO)
        ur_backup.sioState = ur_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        ur_SIO_REG &= (uint32)(~ur_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: ur_Wakeup
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
*  Refer to ur_Sleep() for an example usage.
*******************************************************************************/
void ur_Wakeup(void)
{
    #if defined(ur__PC)
        ur_PC = ur_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            ur_USB_POWER_REG &= ur_USBIO_EXIT_SLEEP_PH1;
            ur_CR1_REG = ur_backup.usbState;
            ur_USB_POWER_REG &= ur_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(ur__SIO)
        ur_SIO_REG = ur_backup.sioState;
    #endif
}


/* [] END OF FILE */
