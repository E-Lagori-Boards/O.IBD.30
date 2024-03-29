/*******************************************************************************
* File Name: wr.h  
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

#if !defined(CY_PINS_wr_ALIASES_H) /* Pins wr_ALIASES_H */
#define CY_PINS_wr_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define wr_0			(wr__0__PC)
#define wr_0_PS		(wr__0__PS)
#define wr_0_PC		(wr__0__PC)
#define wr_0_DR		(wr__0__DR)
#define wr_0_SHIFT	(wr__0__SHIFT)
#define wr_0_INTR	((uint16)((uint16)0x0003u << (wr__0__SHIFT*2u)))

#define wr_INTR_ALL	 ((uint16)(wr_0_INTR))


#endif /* End Pins wr_ALIASES_H */


/* [] END OF FILE */
