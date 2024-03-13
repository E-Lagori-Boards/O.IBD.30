/*******************************************************************************
* File Name: INHB.h  
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

#if !defined(CY_PINS_INHB_ALIASES_H) /* Pins INHB_ALIASES_H */
#define CY_PINS_INHB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define INHB_0			(INHB__0__PC)
#define INHB_0_PS		(INHB__0__PS)
#define INHB_0_PC		(INHB__0__PC)
#define INHB_0_DR		(INHB__0__DR)
#define INHB_0_SHIFT	(INHB__0__SHIFT)
#define INHB_0_INTR	((uint16)((uint16)0x0003u << (INHB__0__SHIFT*2u)))

#define INHB_INTR_ALL	 ((uint16)(INHB_0_INTR))


#endif /* End Pins INHB_ALIASES_H */


/* [] END OF FILE */
