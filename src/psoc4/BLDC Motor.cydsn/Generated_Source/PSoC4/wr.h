/*******************************************************************************
* File Name: wr.h  
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

#if !defined(CY_PINS_wr_H) /* Pins wr_H */
#define CY_PINS_wr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "wr_aliases.h"


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
} wr_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   wr_Read(void);
void    wr_Write(uint8 value);
uint8   wr_ReadDataReg(void);
#if defined(wr__PC) || (CY_PSOC4_4200L) 
    void    wr_SetDriveMode(uint8 mode);
#endif
void    wr_SetInterruptMode(uint16 position, uint16 mode);
uint8   wr_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void wr_Sleep(void); 
void wr_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(wr__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define wr_DRIVE_MODE_BITS        (3)
    #define wr_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - wr_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the wr_SetDriveMode() function.
         *  @{
         */
        #define wr_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define wr_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define wr_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define wr_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define wr_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define wr_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define wr_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define wr_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define wr_MASK               wr__MASK
#define wr_SHIFT              wr__SHIFT
#define wr_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in wr_SetInterruptMode() function.
     *  @{
     */
        #define wr_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define wr_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define wr_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define wr_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(wr__SIO)
    #define wr_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(wr__PC) && (CY_PSOC4_4200L)
    #define wr_USBIO_ENABLE               ((uint32)0x80000000u)
    #define wr_USBIO_DISABLE              ((uint32)(~wr_USBIO_ENABLE))
    #define wr_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define wr_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define wr_USBIO_ENTER_SLEEP          ((uint32)((1u << wr_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << wr_USBIO_SUSPEND_DEL_SHIFT)))
    #define wr_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << wr_USBIO_SUSPEND_SHIFT)))
    #define wr_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << wr_USBIO_SUSPEND_DEL_SHIFT)))
    #define wr_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(wr__PC)
    /* Port Configuration */
    #define wr_PC                 (* (reg32 *) wr__PC)
#endif
/* Pin State */
#define wr_PS                     (* (reg32 *) wr__PS)
/* Data Register */
#define wr_DR                     (* (reg32 *) wr__DR)
/* Input Buffer Disable Override */
#define wr_INP_DIS                (* (reg32 *) wr__PC2)

/* Interrupt configuration Registers */
#define wr_INTCFG                 (* (reg32 *) wr__INTCFG)
#define wr_INTSTAT                (* (reg32 *) wr__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define wr_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(wr__SIO)
    #define wr_SIO_REG            (* (reg32 *) wr__SIO)
#endif /* (wr__SIO_CFG) */

/* USBIO registers */
#if !defined(wr__PC) && (CY_PSOC4_4200L)
    #define wr_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define wr_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define wr_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define wr_DRIVE_MODE_SHIFT       (0x00u)
#define wr_DRIVE_MODE_MASK        (0x07u << wr_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins wr_H */


/* [] END OF FILE */
