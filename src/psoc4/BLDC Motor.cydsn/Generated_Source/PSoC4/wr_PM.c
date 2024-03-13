/*******************************************************************************
* File Name: wr.c  
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
#include "wr.h"

static wr_BACKUP_STRUCT  wr_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: wr_Sleep
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
*  \snippet wr_SUT.c usage_wr_Sleep_Wakeup
*******************************************************************************/
void wr_Sleep(void)
{
    #if defined(wr__PC)
        wr_backup.pcState = wr_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            wr_backup.usbState = wr_CR1_REG;
            wr_USB_POWER_REG |= wr_USBIO_ENTER_SLEEP;
            wr_CR1_REG &= wr_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(wr__SIO)
        wr_backup.sioState = wr_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        wr_SIO_REG &= (uint32)(~wr_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: wr_Wakeup
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
*  Refer to wr_Sleep() for an example usage.
*******************************************************************************/
void wr_Wakeup(void)
{
    #if defined(wr__PC)
        wr_PC = wr_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            wr_USB_POWER_REG &= wr_USBIO_EXIT_SLEEP_PH1;
            wr_CR1_REG = wr_backup.usbState;
            wr_USB_POWER_REG &= wr_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(wr__SIO)
        wr_SIO_REG = wr_backup.sioState;
    #endif
}


/* [] END OF FILE */
