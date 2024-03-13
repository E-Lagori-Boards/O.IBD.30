/*******************************************************************************
* File Name: INHB.h  
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

#if !defined(CY_PINS_INHB_H) /* Pins INHB_H */
#define CY_PINS_INHB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "INHB_aliases.h"


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
} INHB_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   INHB_Read(void);
void    INHB_Write(uint8 value);
uint8   INHB_ReadDataReg(void);
#if defined(INHB__PC) || (CY_PSOC4_4200L) 
    void    INHB_SetDriveMode(uint8 mode);
#endif
void    INHB_SetInterruptMode(uint16 position, uint16 mode);
uint8   INHB_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void INHB_Sleep(void); 
void INHB_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(INHB__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define INHB_DRIVE_MODE_BITS        (3)
    #define INHB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - INHB_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the INHB_SetDriveMode() function.
         *  @{
         */
        #define INHB_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define INHB_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define INHB_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define INHB_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define INHB_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define INHB_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define INHB_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define INHB_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define INHB_MASK               INHB__MASK
#define INHB_SHIFT              INHB__SHIFT
#define INHB_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in INHB_SetInterruptMode() function.
     *  @{
     */
        #define INHB_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define INHB_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define INHB_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define INHB_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(INHB__SIO)
    #define INHB_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(INHB__PC) && (CY_PSOC4_4200L)
    #define INHB_USBIO_ENABLE               ((uint32)0x80000000u)
    #define INHB_USBIO_DISABLE              ((uint32)(~INHB_USBIO_ENABLE))
    #define INHB_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define INHB_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define INHB_USBIO_ENTER_SLEEP          ((uint32)((1u << INHB_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << INHB_USBIO_SUSPEND_DEL_SHIFT)))
    #define INHB_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << INHB_USBIO_SUSPEND_SHIFT)))
    #define INHB_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << INHB_USBIO_SUSPEND_DEL_SHIFT)))
    #define INHB_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(INHB__PC)
    /* Port Configuration */
    #define INHB_PC                 (* (reg32 *) INHB__PC)
#endif
/* Pin State */
#define INHB_PS                     (* (reg32 *) INHB__PS)
/* Data Register */
#define INHB_DR                     (* (reg32 *) INHB__DR)
/* Input Buffer Disable Override */
#define INHB_INP_DIS                (* (reg32 *) INHB__PC2)

/* Interrupt configuration Registers */
#define INHB_INTCFG                 (* (reg32 *) INHB__INTCFG)
#define INHB_INTSTAT                (* (reg32 *) INHB__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define INHB_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(INHB__SIO)
    #define INHB_SIO_REG            (* (reg32 *) INHB__SIO)
#endif /* (INHB__SIO_CFG) */

/* USBIO registers */
#if !defined(INHB__PC) && (CY_PSOC4_4200L)
    #define INHB_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define INHB_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define INHB_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define INHB_DRIVE_MODE_SHIFT       (0x00u)
#define INHB_DRIVE_MODE_MASK        (0x07u << INHB_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins INHB_H */


/* [] END OF FILE */
