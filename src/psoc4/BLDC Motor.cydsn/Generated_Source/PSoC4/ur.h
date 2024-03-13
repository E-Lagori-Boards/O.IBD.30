/*******************************************************************************
* File Name: ur.h  
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

#if !defined(CY_PINS_ur_H) /* Pins ur_H */
#define CY_PINS_ur_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ur_aliases.h"


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
} ur_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ur_Read(void);
void    ur_Write(uint8 value);
uint8   ur_ReadDataReg(void);
#if defined(ur__PC) || (CY_PSOC4_4200L) 
    void    ur_SetDriveMode(uint8 mode);
#endif
void    ur_SetInterruptMode(uint16 position, uint16 mode);
uint8   ur_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ur_Sleep(void); 
void ur_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ur__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ur_DRIVE_MODE_BITS        (3)
    #define ur_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ur_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ur_SetDriveMode() function.
         *  @{
         */
        #define ur_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ur_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ur_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ur_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ur_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ur_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ur_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ur_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ur_MASK               ur__MASK
#define ur_SHIFT              ur__SHIFT
#define ur_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ur_SetInterruptMode() function.
     *  @{
     */
        #define ur_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ur_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ur_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ur_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ur__SIO)
    #define ur_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ur__PC) && (CY_PSOC4_4200L)
    #define ur_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ur_USBIO_DISABLE              ((uint32)(~ur_USBIO_ENABLE))
    #define ur_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ur_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ur_USBIO_ENTER_SLEEP          ((uint32)((1u << ur_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ur_USBIO_SUSPEND_DEL_SHIFT)))
    #define ur_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ur_USBIO_SUSPEND_SHIFT)))
    #define ur_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ur_USBIO_SUSPEND_DEL_SHIFT)))
    #define ur_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ur__PC)
    /* Port Configuration */
    #define ur_PC                 (* (reg32 *) ur__PC)
#endif
/* Pin State */
#define ur_PS                     (* (reg32 *) ur__PS)
/* Data Register */
#define ur_DR                     (* (reg32 *) ur__DR)
/* Input Buffer Disable Override */
#define ur_INP_DIS                (* (reg32 *) ur__PC2)

/* Interrupt configuration Registers */
#define ur_INTCFG                 (* (reg32 *) ur__INTCFG)
#define ur_INTSTAT                (* (reg32 *) ur__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ur_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ur__SIO)
    #define ur_SIO_REG            (* (reg32 *) ur__SIO)
#endif /* (ur__SIO_CFG) */

/* USBIO registers */
#if !defined(ur__PC) && (CY_PSOC4_4200L)
    #define ur_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ur_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ur_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ur_DRIVE_MODE_SHIFT       (0x00u)
#define ur_DRIVE_MODE_MASK        (0x07u << ur_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ur_H */


/* [] END OF FILE */
