/*******************************************************************************
* File Name: vf.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_vf_H) /* Pins vf_H */
#define CY_PINS_vf_H

#include "cytypes.h"
#include "cyfitter.h"
#include "vf_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} vf_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   vf_Read(void);
void    vf_Write(uint8 value);
uint8   vf_ReadDataReg(void);
#if defined(vf__PC) || (CY_PSOC4_4200L) 
    void    vf_SetDriveMode(uint8 mode);
#endif
void    vf_SetInterruptMode(uint16 position, uint16 mode);
uint8   vf_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void vf_Sleep(void); 
void vf_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(vf__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define vf_DRIVE_MODE_BITS        (3)
    #define vf_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - vf_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the vf_SetDriveMode() function.
         *  @{
         */
        #define vf_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define vf_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define vf_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define vf_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define vf_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define vf_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define vf_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define vf_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define vf_MASK               vf__MASK
#define vf_SHIFT              vf__SHIFT
#define vf_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vf_SetInterruptMode() function.
     *  @{
     */
        #define vf_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define vf_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define vf_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define vf_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(vf__SIO)
    #define vf_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(vf__PC) && (CY_PSOC4_4200L)
    #define vf_USBIO_ENABLE               ((uint32)0x80000000u)
    #define vf_USBIO_DISABLE              ((uint32)(~vf_USBIO_ENABLE))
    #define vf_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define vf_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define vf_USBIO_ENTER_SLEEP          ((uint32)((1u << vf_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << vf_USBIO_SUSPEND_DEL_SHIFT)))
    #define vf_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << vf_USBIO_SUSPEND_SHIFT)))
    #define vf_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << vf_USBIO_SUSPEND_DEL_SHIFT)))
    #define vf_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(vf__PC)
    /* Port Configuration */
    #define vf_PC                 (* (reg32 *) vf__PC)
#endif
/* Pin State */
#define vf_PS                     (* (reg32 *) vf__PS)
/* Data Register */
#define vf_DR                     (* (reg32 *) vf__DR)
/* Input Buffer Disable Override */
#define vf_INP_DIS                (* (reg32 *) vf__PC2)

/* Interrupt configuration Registers */
#define vf_INTCFG                 (* (reg32 *) vf__INTCFG)
#define vf_INTSTAT                (* (reg32 *) vf__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define vf_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(vf__SIO)
    #define vf_SIO_REG            (* (reg32 *) vf__SIO)
#endif /* (vf__SIO_CFG) */

/* USBIO registers */
#if !defined(vf__PC) && (CY_PSOC4_4200L)
    #define vf_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define vf_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define vf_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define vf_DRIVE_MODE_SHIFT       (0x00u)
#define vf_DRIVE_MODE_MASK        (0x07u << vf_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins vf_H */


/* [] END OF FILE */
