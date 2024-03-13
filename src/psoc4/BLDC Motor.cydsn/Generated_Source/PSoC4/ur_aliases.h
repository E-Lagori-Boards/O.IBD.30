/*******************************************************************************
* File Name: ur.h  
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

#if !defined(CY_PINS_ur_ALIASES_H) /* Pins ur_ALIASES_H */
#define CY_PINS_ur_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ur_0			(ur__0__PC)
#define ur_0_PS		(ur__0__PS)
#define ur_0_PC		(ur__0__PC)
#define ur_0_DR		(ur__0__DR)
#define ur_0_SHIFT	(ur__0__SHIFT)
#define ur_0_INTR	((uint16)((uint16)0x0003u << (ur__0__SHIFT*2u)))

#define ur_INTR_ALL	 ((uint16)(ur_0_INTR))


#endif /* End Pins ur_ALIASES_H */


/* [] END OF FILE */
