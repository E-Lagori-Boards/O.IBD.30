/*******************************************************************************
* File Name: uf.h  
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

#if !defined(CY_PINS_uf_H) /* Pins uf_H */
#define CY_PINS_uf_H

#include "cytypes.h"
#include "cyfitter.h"
#include "uf_aliases.h"


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
} uf_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   uf_Read(void);
void    uf_Write(uint8 value);
uint8   uf_ReadDataReg(void);
#if defined(uf__PC) || (CY_PSOC4_4200L) 
    void    uf_SetDriveMode(uint8 mode);
#endif
void    uf_SetInterruptMode(uint16 position, uint16 mode);
uint8   uf_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void uf_Sleep(void); 
void uf_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(uf__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define uf_DRIVE_MODE_BITS        (3)
    #define uf_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - uf_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the uf_SetDriveMode() function.
         *  @{
         */
        #define uf_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define uf_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define uf_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define uf_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define uf_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define uf_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define uf_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define uf_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define uf_MASK               uf__MASK
#define uf_SHIFT              uf__SHIFT
#define uf_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in uf_SetInterruptMode() function.
     *  @{
     */
        #define uf_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define uf_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define uf_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define uf_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(uf__SIO)
    #define uf_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(uf__PC) && (CY_PSOC4_4200L)
    #define uf_USBIO_ENABLE               ((uint32)0x80000000u)
    #define uf_USBIO_DISABLE              ((uint32)(~uf_USBIO_ENABLE))
    #define uf_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define uf_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define uf_USBIO_ENTER_SLEEP          ((uint32)((1u << uf_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << uf_USBIO_SUSPEND_DEL_SHIFT)))
    #define uf_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << uf_USBIO_SUSPEND_SHIFT)))
    #define uf_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << uf_USBIO_SUSPEND_DEL_SHIFT)))
    #define uf_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(uf__PC)
    /* Port Configuration */
    #define uf_PC                 (* (reg32 *) uf__PC)
#endif
/* Pin State */
#define uf_PS                     (* (reg32 *) uf__PS)
/* Data Register */
#define uf_DR                     (* (reg32 *) uf__DR)
/* Input Buffer Disable Override */
#define uf_INP_DIS                (* (reg32 *) uf__PC2)

/* Interrupt configuration Registers */
#define uf_INTCFG                 (* (reg32 *) uf__INTCFG)
#define uf_INTSTAT                (* (reg32 *) uf__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define uf_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(uf__SIO)
    #define uf_SIO_REG            (* (reg32 *) uf__SIO)
#endif /* (uf__SIO_CFG) */

/* USBIO registers */
#if !defined(uf__PC) && (CY_PSOC4_4200L)
    #define uf_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define uf_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define uf_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define uf_DRIVE_MODE_SHIFT       (0x00u)
#define uf_DRIVE_MODE_MASK        (0x07u << uf_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins uf_H */


/* [] END OF FILE */
