/*******************************************************************************
* File Name: INHC.h  
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

#if !defined(CY_PINS_INHC_ALIASES_H) /* Pins INHC_ALIASES_H */
#define CY_PINS_INHC_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define INHC_0			(INHC__0__PC)
#define INHC_0_PS		(INHC__0__PS)
#define INHC_0_PC		(INHC__0__PC)
#define INHC_0_DR		(INHC__0__DR)
#define INHC_0_SHIFT	(INHC__0__SHIFT)
#define INHC_0_INTR	((uint16)((uint16)0x0003u << (INHC__0__SHIFT*2u)))

#define INHC_INTR_ALL	 ((uint16)(INHC_0_INTR))


#endif /* End Pins INHC_ALIASES_H */


/* [] END OF FILE */
