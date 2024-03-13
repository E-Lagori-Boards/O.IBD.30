/*******************************************************************************
* File Name: wf.h  
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

#if !defined(CY_PINS_wf_ALIASES_H) /* Pins wf_ALIASES_H */
#define CY_PINS_wf_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define wf_0			(wf__0__PC)
#define wf_0_PS		(wf__0__PS)
#define wf_0_PC		(wf__0__PC)
#define wf_0_DR		(wf__0__DR)
#define wf_0_SHIFT	(wf__0__SHIFT)
#define wf_0_INTR	((uint16)((uint16)0x0003u << (wf__0__SHIFT*2u)))

#define wf_INTR_ALL	 ((uint16)(wf_0_INTR))


#endif /* End Pins wf_ALIASES_H */


/* [] END OF FILE */
