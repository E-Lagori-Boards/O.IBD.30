/*******************************************************************************
* File Name: w.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_w_ALIASES_H) /* Pins w_ALIASES_H */
#define CY_PINS_w_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define w_0			(w__0__PC)
#define w_0_PS		(w__0__PS)
#define w_0_PC		(w__0__PC)
#define w_0_DR		(w__0__DR)
#define w_0_SHIFT	(w__0__SHIFT)
#define w_0_INTR	((uint16)((uint16)0x0003u << (w__0__SHIFT*2u)))

#define w_INTR_ALL	 ((uint16)(w_0_INTR))


#endif /* End Pins w_ALIASES_H */


/* [] END OF FILE */
