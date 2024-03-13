/*******************************************************************************
* File Name: INHB.c  
* Version 2.20
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "INHB.h"


#if defined(INHB__PC)
    #define INHB_SetP4PinDriveMode(shift, mode)  \
    do { \
        INHB_PC =   (INHB_PC & \
                                (uint32)(~(uint32)(INHB_DRIVE_MODE_IND_MASK << \
                                (INHB_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << \
                                (INHB_DRIVE_MODE_BITS * (shift))); \
    } while (0)
#else
    #if (CY_PSOC4_4200L)
        #define INHB_SetP4PinDriveMode(shift, mode)  \
        do { \
            INHB_USBIO_CTRL_REG = (INHB_USBIO_CTRL_REG & \
                                    (uint32)(~(uint32)(INHB_DRIVE_MODE_IND_MASK << \
                                    (INHB_DRIVE_MODE_BITS * (shift))))) | \
                                    (uint32)((uint32)(mode) << \
                                    (INHB_DRIVE_MODE_BITS * (shift))); \
        } while (0)
    #endif
#endif
  

#if defined(INHB__PC) || (CY_PSOC4_4200L) 
    /*******************************************************************************
    * Function Name: INHB_SetDriveMode
    ****************************************************************************//**
    *
    * \brief Sets the drive mode for each of the Pins component's pins.
    * 
    * <b>Note</b> This affects all pins in the Pins component instance. Use the
    * Per-Pin APIs if you wish to control individual pin's drive modes.
    *
    * <b>Note</b> USBIOs have limited drive functionality. Refer to the Drive Mode
    * parameter for more information.
    *
    * \param mode
    *  Mode for the selected signals. Valid options are documented in 
    *  \ref driveMode.
    *
    * \return
    *  None
    *
    * \sideeffect
    *  If you use read-modify-write operations that are not atomic, the ISR can
    *  cause corruption of this function. An ISR that interrupts this function 
    *  and performs writes to the Pins component Drive Mode registers can cause 
    *  corrupted port data. To avoid this issue, you should either use the Per-Pin
    *  APIs (primary method) or disable interrupts around this function.
    *
    * \funcusage
    *  \snippet INHB_SUT.c usage_INHB_SetDriveMode
    *******************************************************************************/
    void INHB_SetDriveMode(uint8 mode)
    {
		INHB_SetP4PinDriveMode(INHB__0__SHIFT, mode);
    }
#endif


/*******************************************************************************
* Function Name: INHB_Write
****************************************************************************//**
*
* \brief Writes the value to the physical port (data output register), masking
*  and shifting the bits appropriately. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This function avoids changing 
* other bits in the port by using the appropriate method (read-modify-write or
* bit banding).
*
* <b>Note</b> This function should not be used on a hardware digital output pin 
* as it is driven by the hardware signal attached to it.
*
* \param value
*  Value to write to the component instance.
*
* \return 
*  None 
*
* \sideeffect
*  If you use read-modify-write operations that are not atomic; the Interrupt 
*  Service Routines (ISR) can cause corruption of this function. An ISR that 
*  interrupts this function and performs writes to the Pins component data 
*  register can cause corrupted port data. To avoid this issue, you should 
*  either use the Per-Pin APIs (primary method) or disable interrupts around 
*  this function.
*
* \funcusage
*  \snippet INHB_SUT.c usage_INHB_Write
*******************************************************************************/
void INHB_Write(uint8 value)
{
    uint8 drVal = (uint8)(INHB_DR & (uint8)(~INHB_MASK));
    drVal = (drVal | ((uint8)(value << INHB_SHIFT) & INHB_MASK));
    INHB_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: INHB_Read
****************************************************************************//**
*
* \brief Reads the associated physical port (pin status register) and masks 
*  the required bits according to the width and bit position of the component
*  instance. 
*
* The pin's status register returns the current logic level present on the 
* physical pin.
*
* \return 
*  The current value for the pins in the component as a right justified number.
*
* \funcusage
*  \snippet INHB_SUT.c usage_INHB_Read  
*******************************************************************************/
uint8 INHB_Read(void)
{
    return (uint8)((INHB_PS & INHB_MASK) >> INHB_SHIFT);
}


/*******************************************************************************
* Function Name: INHB_ReadDataReg
****************************************************************************//**
*
* \brief Reads the associated physical port's data output register and masks 
*  the correct bits according to the width and bit position of the component 
*  instance. 
*
* The data output register controls the signal applied to the physical pin in 
* conjunction with the drive mode parameter. This is not the same as the 
* preferred INHB_Read() API because the 
* INHB_ReadDataReg() reads the data register instead of the status 
* register. For output pins this is a useful function to determine the value 
* just written to the pin.
*
* \return 
*  The current value of the data register masked and shifted into a right 
*  justified number for the component instance.
*
* \funcusage
*  \snippet INHB_SUT.c usage_INHB_ReadDataReg 
*******************************************************************************/
uint8 INHB_ReadDataReg(void)
{
    return (uint8)((INHB_DR & INHB_MASK) >> INHB_SHIFT);
}


/*******************************************************************************
* Function Name: INHB_SetInterruptMode
****************************************************************************//**
*
* \brief Configures the interrupt mode for each of the Pins component's
*  pins. Alternatively you may set the interrupt mode for all the pins
*  specified in the Pins component.
*
*  <b>Note</b> The interrupt is port-wide and therefore any enabled pin
*  interrupt may trigger it.
*
* \param position
*  The pin position as listed in the Pins component. You may OR these to be 
*  able to configure the interrupt mode of multiple pins within a Pins 
*  component. Or you may use INHB_INTR_ALL to configure the
*  interrupt mode of all the pins in the Pins component.       
*  - INHB_0_INTR       (First pin in the list)
*  - INHB_1_INTR       (Second pin in the list)
*  - ...
*  - INHB_INTR_ALL     (All pins in Pins component)
*
* \param mode
*  Interrupt mode for the selected pins. Valid options are documented in
*  \ref intrMode.
*
* \return 
*  None
*  
* \sideeffect
*  It is recommended that the interrupt be disabled before calling this 
*  function to avoid unintended interrupt requests. Note that the interrupt
*  type is port wide, and therefore will trigger for any enabled pin on the 
*  port.
*
* \funcusage
*  \snippet INHB_SUT.c usage_INHB_SetInterruptMode
*******************************************************************************/
void INHB_SetInterruptMode(uint16 position, uint16 mode)
{
    uint32 intrCfg;
    
    intrCfg =  INHB_INTCFG & (uint32)(~(uint32)position);
    INHB_INTCFG = intrCfg | ((uint32)position & (uint32)mode);
}


/*******************************************************************************
* Function Name: INHB_ClearInterrupt
****************************************************************************//**
*
* \brief Clears any active interrupts attached with the component and returns 
*  the value of the interrupt status register allowing determination of which
*  pins generated an interrupt event.
*
* \return 
*  The right-shifted current value of the interrupt status register. Each pin 
*  has one bit set if it generated an interrupt event. For example, bit 0 is 
*  for pin 0 and bit 1 is for pin 1 of the Pins component.
*  
* \sideeffect
*  Clears all bits of the physical port's interrupt status register, not just
*  those associated with the Pins component.
*
* \funcusage
*  \snippet INHB_SUT.c usage_INHB_ClearInterrupt
*******************************************************************************/
uint8 INHB_ClearInterrupt(void)
{
	uint8 maskedStatus = (uint8)(INHB_INTSTAT & INHB_MASK);
	INHB_INTSTAT = maskedStatus;
    return maskedStatus >> INHB_SHIFT;
}


/* [] END OF FILE */
