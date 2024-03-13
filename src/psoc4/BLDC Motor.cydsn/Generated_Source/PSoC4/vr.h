/*******************************************************************************
* File Name: vr.h  
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

#if !defined(CY_PINS_vr_H) /* Pins vr_H */
#define CY_PINS_vr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "vr_aliases.h"


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
} vr_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   vr_Read(void);
void    vr_Write(uint8 value);
uint8   vr_ReadDataReg(void);
#if defined(vr__PC) || (CY_PSOC4_4200L) 
    void    vr_SetDriveMode(uint8 mode);
#endif
void    vr_SetInterruptMode(uint16 position, uint16 mode);
uint8   vr_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void vr_Sleep(void); 
void vr_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(vr__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define vr_DRIVE_MODE_BITS        (3)
    #define vr_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - vr_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the vr_SetDriveMode() function.
         *  @{
         */
        #define vr_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define vr_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define vr_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define vr_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define vr_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define vr_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define vr_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define vr_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define vr_MASK               vr__MASK
#define vr_SHIFT              vr__SHIFT
#define vr_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vr_SetInterruptMode() function.
     *  @{
     */
        #define vr_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define vr_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define vr_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define vr_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(vr__SIO)
    #define vr_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(vr__PC) && (CY_PSOC4_4200L)
    #define vr_USBIO_ENABLE               ((uint32)0x80000000u)
    #define vr_USBIO_DISABLE              ((uint32)(~vr_USBIO_ENABLE))
    #define vr_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define vr_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define vr_USBIO_ENTER_SLEEP          ((uint32)((1u << vr_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << vr_USBIO_SUSPEND_DEL_SHIFT)))
    #define vr_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << vr_USBIO_SUSPEND_SHIFT)))
    #define vr_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << vr_USBIO_SUSPEND_DEL_SHIFT)))
    #define vr_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(vr__PC)
    /* Port Configuration */
    #define vr_PC                 (* (reg32 *) vr__PC)
#endif
/* Pin State */
#define vr_PS                     (* (reg32 *) vr__PS)
/* Data Register */
#define vr_DR                     (* (reg32 *) vr__DR)
/* Input Buffer Disable Override */
#define vr_INP_DIS                (* (reg32 *) vr__PC2)

/* Interrupt configuration Registers */
#define vr_INTCFG                 (* (reg32 *) vr__INTCFG)
#define vr_INTSTAT                (* (reg32 *) vr__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define vr_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(vr__SIO)
    #define vr_SIO_REG            (* (reg32 *) vr__SIO)
#endif /* (vr__SIO_CFG) */

/* USBIO registers */
#if !defined(vr__PC) && (CY_PSOC4_4200L)
    #define vr_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define vr_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define vr_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define vr_DRIVE_MODE_SHIFT       (0x00u)
#define vr_DRIVE_MODE_MASK        (0x07u << vr_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins vr_H */


/* [] END OF FILE */
