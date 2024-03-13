/*******************************************************************************
* File Name: u.h  
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

#if !defined(CY_PINS_u_H) /* Pins u_H */
#define CY_PINS_u_H

#include "cytypes.h"
#include "cyfitter.h"
#include "u_aliases.h"


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
} u_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   u_Read(void);
void    u_Write(uint8 value);
uint8   u_ReadDataReg(void);
#if defined(u__PC) || (CY_PSOC4_4200L) 
    void    u_SetDriveMode(uint8 mode);
#endif
void    u_SetInterruptMode(uint16 position, uint16 mode);
uint8   u_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void u_Sleep(void); 
void u_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(u__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define u_DRIVE_MODE_BITS        (3)
    #define u_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - u_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the u_SetDriveMode() function.
         *  @{
         */
        #define u_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define u_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define u_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define u_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define u_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define u_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define u_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define u_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define u_MASK               u__MASK
#define u_SHIFT              u__SHIFT
#define u_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in u_SetInterruptMode() function.
     *  @{
     */
        #define u_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define u_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define u_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define u_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(u__SIO)
    #define u_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(u__PC) && (CY_PSOC4_4200L)
    #define u_USBIO_ENABLE               ((uint32)0x80000000u)
    #define u_USBIO_DISABLE              ((uint32)(~u_USBIO_ENABLE))
    #define u_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define u_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define u_USBIO_ENTER_SLEEP          ((uint32)((1u << u_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << u_USBIO_SUSPEND_DEL_SHIFT)))
    #define u_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << u_USBIO_SUSPEND_SHIFT)))
    #define u_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << u_USBIO_SUSPEND_DEL_SHIFT)))
    #define u_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(u__PC)
    /* Port Configuration */
    #define u_PC                 (* (reg32 *) u__PC)
#endif
/* Pin State */
#define u_PS                     (* (reg32 *) u__PS)
/* Data Register */
#define u_DR                     (* (reg32 *) u__DR)
/* Input Buffer Disable Override */
#define u_INP_DIS                (* (reg32 *) u__PC2)

/* Interrupt configuration Registers */
#define u_INTCFG                 (* (reg32 *) u__INTCFG)
#define u_INTSTAT                (* (reg32 *) u__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define u_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(u__SIO)
    #define u_SIO_REG            (* (reg32 *) u__SIO)
#endif /* (u__SIO_CFG) */

/* USBIO registers */
#if !defined(u__PC) && (CY_PSOC4_4200L)
    #define u_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define u_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define u_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define u_DRIVE_MODE_SHIFT       (0x00u)
#define u_DRIVE_MODE_MASK        (0x07u << u_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins u_H */


/* [] END OF FILE */
