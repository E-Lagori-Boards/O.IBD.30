/*******************************************************************************
* File Name: vr.h  
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

#if !defined(CY_PINS_vr_ALIASES_H) /* Pins vr_ALIASES_H */
#define CY_PINS_vr_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define vr_0			(vr__0__PC)
#define vr_0_PS		(vr__0__PS)
#define vr_0_PC		(vr__0__PC)
#define vr_0_DR		(vr__0__DR)
#define vr_0_SHIFT	(vr__0__SHIFT)
#define vr_0_INTR	((uint16)((uint16)0x0003u << (vr__0__SHIFT*2u)))

#define vr_INTR_ALL	 ((uint16)(vr_0_INTR))


#endif /* End Pins vr_ALIASES_H */


/* [] END OF FILE */
