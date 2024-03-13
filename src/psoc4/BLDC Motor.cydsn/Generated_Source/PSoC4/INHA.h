/*******************************************************************************
* File Name: INHA.h  
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

#if !defined(CY_PINS_INHA_H) /* Pins INHA_H */
#define CY_PINS_INHA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "INHA_aliases.h"


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
} INHA_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   INHA_Read(void);
void    INHA_Write(uint8 value);
uint8   INHA_ReadDataReg(void);
#if defined(INHA__PC) || (CY_PSOC4_4200L) 
    void    INHA_SetDriveMode(uint8 mode);
#endif
void    INHA_SetInterruptMode(uint16 position, uint16 mode);
uint8   INHA_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void INHA_Sleep(void); 
void INHA_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(INHA__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define INHA_DRIVE_MODE_BITS        (3)
    #define INHA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - INHA_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the INHA_SetDriveMode() function.
         *  @{
         */
        #define INHA_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define INHA_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define INHA_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define INHA_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define INHA_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define INHA_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define INHA_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define INHA_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define INHA_MASK               INHA__MASK
#define INHA_SHIFT              INHA__SHIFT
#define INHA_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in INHA_SetInterruptMode() function.
     *  @{
     */
        #define INHA_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define INHA_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define INHA_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define INHA_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(INHA__SIO)
    #define INHA_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(INHA__PC) && (CY_PSOC4_4200L)
    #define INHA_USBIO_ENABLE               ((uint32)0x80000000u)
    #define INHA_USBIO_DISABLE              ((uint32)(~INHA_USBIO_ENABLE))
    #define INHA_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define INHA_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define INHA_USBIO_ENTER_SLEEP          ((uint32)((1u << INHA_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << INHA_USBIO_SUSPEND_DEL_SHIFT)))
    #define INHA_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << INHA_USBIO_SUSPEND_SHIFT)))
    #define INHA_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << INHA_USBIO_SUSPEND_DEL_SHIFT)))
    #define INHA_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(INHA__PC)
    /* Port Configuration */
    #define INHA_PC                 (* (reg32 *) INHA__PC)
#endif
/* Pin State */
#define INHA_PS                     (* (reg32 *) INHA__PS)
/* Data Register */
#define INHA_DR                     (* (reg32 *) INHA__DR)
/* Input Buffer Disable Override */
#define INHA_INP_DIS                (* (reg32 *) INHA__PC2)

/* Interrupt configuration Registers */
#define INHA_INTCFG                 (* (reg32 *) INHA__INTCFG)
#define INHA_INTSTAT                (* (reg32 *) INHA__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define INHA_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(INHA__SIO)
    #define INHA_SIO_REG            (* (reg32 *) INHA__SIO)
#endif /* (INHA__SIO_CFG) */

/* USBIO registers */
#if !defined(INHA__PC) && (CY_PSOC4_4200L)
    #define INHA_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define INHA_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define INHA_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define INHA_DRIVE_MODE_SHIFT       (0x00u)
#define INHA_DRIVE_MODE_MASK        (0x07u << INHA_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins INHA_H */


/* [] END OF FILE */
