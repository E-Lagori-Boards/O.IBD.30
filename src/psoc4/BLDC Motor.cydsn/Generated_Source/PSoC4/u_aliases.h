/*******************************************************************************
* File Name: u.h  
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

#if !defined(CY_PINS_u_ALIASES_H) /* Pins u_ALIASES_H */
#define CY_PINS_u_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define u_0			(u__0__PC)
#define u_0_PS		(u__0__PS)
#define u_0_PC		(u__0__PC)
#define u_0_DR		(u__0__DR)
#define u_0_SHIFT	(u__0__SHIFT)
#define u_0_INTR	((uint16)((uint16)0x0003u << (u__0__SHIFT*2u)))

#define u_INTR_ALL	 ((uint16)(u_0_INTR))


#endif /* End Pins u_ALIASES_H */


/* [] END OF FILE */
