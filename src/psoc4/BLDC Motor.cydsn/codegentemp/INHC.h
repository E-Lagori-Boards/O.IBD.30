/*******************************************************************************
* File Name: INHC.h  
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

#if !defined(CY_PINS_INHC_H) /* Pins INHC_H */
#define CY_PINS_INHC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "INHC_aliases.h"


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
} INHC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   INHC_Read(void);
void    INHC_Write(uint8 value);
uint8   INHC_ReadDataReg(void);
#if defined(INHC__PC) || (CY_PSOC4_4200L) 
    void    INHC_SetDriveMode(uint8 mode);
#endif
void    INHC_SetInterruptMode(uint16 position, uint16 mode);
uint8   INHC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void INHC_Sleep(void); 
void INHC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(INHC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define INHC_DRIVE_MODE_BITS        (3)
    #define INHC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - INHC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the INHC_SetDriveMode() function.
         *  @{
         */
        #define INHC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define INHC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define INHC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define INHC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define INHC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define INHC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define INHC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define INHC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define INHC_MASK               INHC__MASK
#define INHC_SHIFT              INHC__SHIFT
#define INHC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in INHC_SetInterruptMode() function.
     *  @{
     */
        #define INHC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define INHC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define INHC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define INHC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(INHC__SIO)
    #define INHC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(INHC__PC) && (CY_PSOC4_4200L)
    #define INHC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define INHC_USBIO_DISABLE              ((uint32)(~INHC_USBIO_ENABLE))
    #define INHC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define INHC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define INHC_USBIO_ENTER_SLEEP          ((uint32)((1u << INHC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << INHC_USBIO_SUSPEND_DEL_SHIFT)))
    #define INHC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << INHC_USBIO_SUSPEND_SHIFT)))
    #define INHC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << INHC_USBIO_SUSPEND_DEL_SHIFT)))
    #define INHC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(INHC__PC)
    /* Port Configuration */
    #define INHC_PC                 (* (reg32 *) INHC__PC)
#endif
/* Pin State */
#define INHC_PS                     (* (reg32 *) INHC__PS)
/* Data Register */
#define INHC_DR                     (* (reg32 *) INHC__DR)
/* Input Buffer Disable Override */
#define INHC_INP_DIS                (* (reg32 *) INHC__PC2)

/* Interrupt configuration Registers */
#define INHC_INTCFG                 (* (reg32 *) INHC__INTCFG)
#define INHC_INTSTAT                (* (reg32 *) INHC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define INHC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(INHC__SIO)
    #define INHC_SIO_REG            (* (reg32 *) INHC__SIO)
#endif /* (INHC__SIO_CFG) */

/* USBIO registers */
#if !defined(INHC__PC) && (CY_PSOC4_4200L)
    #define INHC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define INHC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define INHC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define INHC_DRIVE_MODE_SHIFT       (0x00u)
#define INHC_DRIVE_MODE_MASK        (0x07u << INHC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins INHC_H */


/* [] END OF FILE */
