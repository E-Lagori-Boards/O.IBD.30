/*******************************************************************************
* File Name: v.h  
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

#if !defined(CY_PINS_v_ALIASES_H) /* Pins v_ALIASES_H */
#define CY_PINS_v_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define v_0			(v__0__PC)
#define v_0_PS		(v__0__PS)
#define v_0_PC		(v__0__PC)
#define v_0_DR		(v__0__DR)
#define v_0_SHIFT	(v__0__SHIFT)
#define v_0_INTR	((uint16)((uint16)0x0003u << (v__0__SHIFT*2u)))

#define v_INTR_ALL	 ((uint16)(v_0_INTR))


#endif /* End Pins v_ALIASES_H */


/* [] END OF FILE */
