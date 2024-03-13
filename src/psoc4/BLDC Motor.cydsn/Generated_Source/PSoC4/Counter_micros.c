/*******************************************************************************
* File Name: Counter_micros.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_micros.h"

uint8 Counter_micros_initVar = 0u;


/*******************************************************************************
* Function Name: Counter_micros_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Counter_micros_Init(void) 
{
        #if (!Counter_micros_UsingFixedFunction && !Counter_micros_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!Counter_micros_UsingFixedFunction && !Counter_micros_ControlRegRemoved) */
        
        #if(!Counter_micros_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_micros_interruptState;
        #endif /* (!Counter_micros_UsingFixedFunction) */
        
        #if (Counter_micros_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Counter_micros_CONTROL &= Counter_micros_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                Counter_micros_CONTROL2 &= ((uint8)(~Counter_micros_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                Counter_micros_CONTROL3 &= ((uint8)(~Counter_micros_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Counter_micros_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                Counter_micros_CONTROL |= Counter_micros_ONESHOT;
            #endif /* (Counter_micros_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            Counter_micros_CONTROL2 |= Counter_micros_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            Counter_micros_RT1 &= ((uint8)(~Counter_micros_RT1_MASK));
            Counter_micros_RT1 |= Counter_micros_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            Counter_micros_RT1 &= ((uint8)(~Counter_micros_SYNCDSI_MASK));
            Counter_micros_RT1 |= Counter_micros_SYNCDSI_EN;

        #else
            #if(!Counter_micros_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Counter_micros_CONTROL & ((uint8)(~Counter_micros_CTRL_CMPMODE_MASK));
            Counter_micros_CONTROL = ctrl | Counter_micros_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Counter_micros_CONTROL & ((uint8)(~Counter_micros_CTRL_CAPMODE_MASK));
            
            #if( 0 != Counter_micros_CAPTURE_MODE_CONF)
                Counter_micros_CONTROL = ctrl | Counter_micros_DEFAULT_CAPTURE_MODE;
            #else
                Counter_micros_CONTROL = ctrl;
            #endif /* 0 != Counter_micros_CAPTURE_MODE */ 
            
            #endif /* (!Counter_micros_ControlRegRemoved) */
        #endif /* (Counter_micros_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!Counter_micros_UsingFixedFunction)
            Counter_micros_ClearFIFO();
        #endif /* (!Counter_micros_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        Counter_micros_WritePeriod(Counter_micros_INIT_PERIOD_VALUE);
        #if (!(Counter_micros_UsingFixedFunction && (CY_PSOC5A)))
            Counter_micros_WriteCounter(Counter_micros_INIT_COUNTER_VALUE);
        #endif /* (!(Counter_micros_UsingFixedFunction && (CY_PSOC5A))) */
        Counter_micros_SetInterruptMode(Counter_micros_INIT_INTERRUPTS_MASK);
        
        #if (!Counter_micros_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)Counter_micros_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            Counter_micros_WriteCompare(Counter_micros_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Counter_micros_interruptState = CyEnterCriticalSection();
            
            Counter_micros_STATUS_AUX_CTRL |= Counter_micros_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_micros_interruptState);
            
        #endif /* (!Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void Counter_micros_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Counter_micros_UsingFixedFunction)
        Counter_micros_GLOBAL_ENABLE |= Counter_micros_BLOCK_EN_MASK;
        Counter_micros_GLOBAL_STBY_ENABLE |= Counter_micros_BLOCK_STBY_EN_MASK;
    #endif /* (Counter_micros_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Counter_micros_ControlRegRemoved || Counter_micros_UsingFixedFunction)
        Counter_micros_CONTROL |= Counter_micros_CTRL_ENABLE;                
    #endif /* (!Counter_micros_ControlRegRemoved || Counter_micros_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: Counter_micros_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  Counter_micros_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Counter_micros_Start(void) 
{
    if(Counter_micros_initVar == 0u)
    {
        Counter_micros_Init();
        
        Counter_micros_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    Counter_micros_Enable();        
}


/*******************************************************************************
* Function Name: Counter_micros_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Counter_micros_Stop(void) 
{
    /* Disable Counter */
    #if(!Counter_micros_ControlRegRemoved || Counter_micros_UsingFixedFunction)
        Counter_micros_CONTROL &= ((uint8)(~Counter_micros_CTRL_ENABLE));        
    #endif /* (!Counter_micros_ControlRegRemoved || Counter_micros_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (Counter_micros_UsingFixedFunction)
        Counter_micros_GLOBAL_ENABLE &= ((uint8)(~Counter_micros_BLOCK_EN_MASK));
        Counter_micros_GLOBAL_STBY_ENABLE &= ((uint8)(~Counter_micros_BLOCK_STBY_EN_MASK));
    #endif /* (Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void Counter_micros_SetInterruptMode(uint8 interruptsMask) 
{
    Counter_micros_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: Counter_micros_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   Counter_micros_ReadStatusRegister(void) 
{
    return Counter_micros_STATUS;
}


#if(!Counter_micros_ControlRegRemoved)
/*******************************************************************************
* Function Name: Counter_micros_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   Counter_micros_ReadControlRegister(void) 
{
    return Counter_micros_CONTROL;
}


/*******************************************************************************
* Function Name: Counter_micros_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    Counter_micros_WriteControlRegister(uint8 control) 
{
    Counter_micros_CONTROL = control;
}

#endif  /* (!Counter_micros_ControlRegRemoved) */


#if (!(Counter_micros_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: Counter_micros_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void Counter_micros_WriteCounter(uint32 counter) \
                                   
{
    #if(Counter_micros_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (Counter_micros_GLOBAL_ENABLE & Counter_micros_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        Counter_micros_GLOBAL_ENABLE |= Counter_micros_BLOCK_EN_MASK;
        CY_SET_REG16(Counter_micros_COUNTER_LSB_PTR, (uint16)counter);
        Counter_micros_GLOBAL_ENABLE &= ((uint8)(~Counter_micros_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(Counter_micros_COUNTER_LSB_PTR, counter);
    #endif /* (Counter_micros_UsingFixedFunction) */
}
#endif /* (!(Counter_micros_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: Counter_micros_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 Counter_micros_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Counter_micros_UsingFixedFunction)
		(void)CY_GET_REG16(Counter_micros_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(Counter_micros_COUNTER_LSB_PTR_8BIT);
	#endif/* (Counter_micros_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Counter_micros_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Counter_micros_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(Counter_micros_STATICCOUNT_LSB_PTR));
    #endif /* (Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 Counter_micros_ReadCapture(void) 
{
    #if(Counter_micros_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Counter_micros_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(Counter_micros_STATICCOUNT_LSB_PTR));
    #endif /* (Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void Counter_micros_WritePeriod(uint32 period) 
{
    #if(Counter_micros_UsingFixedFunction)
        CY_SET_REG16(Counter_micros_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(Counter_micros_PERIOD_LSB_PTR, period);
    #endif /* (Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 Counter_micros_ReadPeriod(void) 
{
    #if(Counter_micros_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Counter_micros_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(Counter_micros_PERIOD_LSB_PTR));
    #endif /* (Counter_micros_UsingFixedFunction) */
}


#if (!Counter_micros_UsingFixedFunction)
/*******************************************************************************
* Function Name: Counter_micros_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void Counter_micros_WriteCompare(uint32 compare) \
                                   
{
    #if(Counter_micros_UsingFixedFunction)
        CY_SET_REG16(Counter_micros_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(Counter_micros_COMPARE_LSB_PTR, compare);
    #endif /* (Counter_micros_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_micros_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 Counter_micros_ReadCompare(void) 
{
    return (CY_GET_REG32(Counter_micros_COMPARE_LSB_PTR));
}


#if (Counter_micros_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Counter_micros_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Counter_micros_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    Counter_micros_CONTROL &= ((uint8)(~Counter_micros_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    Counter_micros_CONTROL |= compareMode;
}
#endif  /* (Counter_micros_COMPARE_MODE_SOFTWARE) */


#if (Counter_micros_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Counter_micros_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Counter_micros_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    Counter_micros_CONTROL &= ((uint8)(~Counter_micros_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    Counter_micros_CONTROL |= ((uint8)((uint8)captureMode << Counter_micros_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (Counter_micros_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: Counter_micros_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void Counter_micros_ClearFIFO(void) 
{

    while(0u != (Counter_micros_ReadStatusRegister() & Counter_micros_STATUS_FIFONEMP))
    {
        (void)Counter_micros_ReadCapture();
    }

}
#endif  /* (!Counter_micros_UsingFixedFunction) */


/* [] END OF FILE */

