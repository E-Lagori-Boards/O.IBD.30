/*******************************************************************************
* File Name: PWM_C.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the PWM_C
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_PWM_C_H)
#define CY_TCPWM_PWM_C_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} PWM_C_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  PWM_C_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define PWM_C_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define PWM_C_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define PWM_C_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define PWM_C_QUAD_ENCODING_MODES            (0lu)
#define PWM_C_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define PWM_C_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define PWM_C_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define PWM_C_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define PWM_C_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define PWM_C_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define PWM_C_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define PWM_C_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define PWM_C_TC_RUN_MODE                    (0lu)
#define PWM_C_TC_COUNTER_MODE                (0lu)
#define PWM_C_TC_COMP_CAP_MODE               (2lu)
#define PWM_C_TC_PRESCALER                   (0lu)

/* Signal modes */
#define PWM_C_TC_RELOAD_SIGNAL_MODE          (0lu)
#define PWM_C_TC_COUNT_SIGNAL_MODE           (3lu)
#define PWM_C_TC_START_SIGNAL_MODE           (0lu)
#define PWM_C_TC_STOP_SIGNAL_MODE            (0lu)
#define PWM_C_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_C_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define PWM_C_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define PWM_C_TC_START_SIGNAL_PRESENT        (0lu)
#define PWM_C_TC_STOP_SIGNAL_PRESENT         (0lu)
#define PWM_C_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_C_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define PWM_C_PWM_KILL_EVENT                 (0lu)
#define PWM_C_PWM_STOP_EVENT                 (0lu)
#define PWM_C_PWM_MODE                       (4lu)
#define PWM_C_PWM_OUT_N_INVERT               (0lu)
#define PWM_C_PWM_OUT_INVERT                 (0lu)
#define PWM_C_PWM_ALIGN                      (0lu)
#define PWM_C_PWM_RUN_MODE                   (0lu)
#define PWM_C_PWM_DEAD_TIME_CYCLE            (0lu)
#define PWM_C_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define PWM_C_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define PWM_C_PWM_COUNT_SIGNAL_MODE          (3lu)
#define PWM_C_PWM_START_SIGNAL_MODE          (0lu)
#define PWM_C_PWM_STOP_SIGNAL_MODE           (0lu)
#define PWM_C_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define PWM_C_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define PWM_C_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define PWM_C_PWM_START_SIGNAL_PRESENT       (0lu)
#define PWM_C_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define PWM_C_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define PWM_C_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define PWM_C_TC_PERIOD_VALUE                (65535lu)
#define PWM_C_TC_COMPARE_VALUE               (65535lu)
#define PWM_C_TC_COMPARE_BUF_VALUE           (65535lu)
#define PWM_C_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define PWM_C_PWM_PERIOD_VALUE               (4800lu)
#define PWM_C_PWM_PERIOD_BUF_VALUE           (65535lu)
#define PWM_C_PWM_PERIOD_SWAP                (0lu)
#define PWM_C_PWM_COMPARE_VALUE              (4752lu)
#define PWM_C_PWM_COMPARE_BUF_VALUE          (65535lu)
#define PWM_C_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define PWM_C__LEFT 0
#define PWM_C__RIGHT 1
#define PWM_C__CENTER 2
#define PWM_C__ASYMMETRIC 3

#define PWM_C__X1 0
#define PWM_C__X2 1
#define PWM_C__X4 2

#define PWM_C__PWM 4
#define PWM_C__PWM_DT 5
#define PWM_C__PWM_PR 6

#define PWM_C__INVERSE 1
#define PWM_C__DIRECT 0

#define PWM_C__CAPTURE 2
#define PWM_C__COMPARE 0

#define PWM_C__TRIG_LEVEL 3
#define PWM_C__TRIG_RISING 0
#define PWM_C__TRIG_FALLING 1
#define PWM_C__TRIG_BOTH 2

#define PWM_C__INTR_MASK_TC 1
#define PWM_C__INTR_MASK_CC_MATCH 2
#define PWM_C__INTR_MASK_NONE 0
#define PWM_C__INTR_MASK_TC_CC 3

#define PWM_C__UNCONFIG 8
#define PWM_C__TIMER 1
#define PWM_C__QUAD 3
#define PWM_C__PWM_SEL 7

#define PWM_C__COUNT_UP 0
#define PWM_C__COUNT_DOWN 1
#define PWM_C__COUNT_UPDOWN0 2
#define PWM_C__COUNT_UPDOWN1 3


/* Prescaler */
#define PWM_C_PRESCALE_DIVBY1                ((uint32)(0u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY2                ((uint32)(1u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY4                ((uint32)(2u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY8                ((uint32)(3u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY16               ((uint32)(4u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY32               ((uint32)(5u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY64               ((uint32)(6u << PWM_C_PRESCALER_SHIFT))
#define PWM_C_PRESCALE_DIVBY128              ((uint32)(7u << PWM_C_PRESCALER_SHIFT))

/* TCPWM set modes */
#define PWM_C_MODE_TIMER_COMPARE             ((uint32)(PWM_C__COMPARE         <<  \
                                                                  PWM_C_MODE_SHIFT))
#define PWM_C_MODE_TIMER_CAPTURE             ((uint32)(PWM_C__CAPTURE         <<  \
                                                                  PWM_C_MODE_SHIFT))
#define PWM_C_MODE_QUAD                      ((uint32)(PWM_C__QUAD            <<  \
                                                                  PWM_C_MODE_SHIFT))
#define PWM_C_MODE_PWM                       ((uint32)(PWM_C__PWM             <<  \
                                                                  PWM_C_MODE_SHIFT))
#define PWM_C_MODE_PWM_DT                    ((uint32)(PWM_C__PWM_DT          <<  \
                                                                  PWM_C_MODE_SHIFT))
#define PWM_C_MODE_PWM_PR                    ((uint32)(PWM_C__PWM_PR          <<  \
                                                                  PWM_C_MODE_SHIFT))

/* Quad Modes */
#define PWM_C_MODE_X1                        ((uint32)(PWM_C__X1              <<  \
                                                                  PWM_C_QUAD_MODE_SHIFT))
#define PWM_C_MODE_X2                        ((uint32)(PWM_C__X2              <<  \
                                                                  PWM_C_QUAD_MODE_SHIFT))
#define PWM_C_MODE_X4                        ((uint32)(PWM_C__X4              <<  \
                                                                  PWM_C_QUAD_MODE_SHIFT))

/* Counter modes */
#define PWM_C_COUNT_UP                       ((uint32)(PWM_C__COUNT_UP        <<  \
                                                                  PWM_C_UPDOWN_SHIFT))
#define PWM_C_COUNT_DOWN                     ((uint32)(PWM_C__COUNT_DOWN      <<  \
                                                                  PWM_C_UPDOWN_SHIFT))
#define PWM_C_COUNT_UPDOWN0                  ((uint32)(PWM_C__COUNT_UPDOWN0   <<  \
                                                                  PWM_C_UPDOWN_SHIFT))
#define PWM_C_COUNT_UPDOWN1                  ((uint32)(PWM_C__COUNT_UPDOWN1   <<  \
                                                                  PWM_C_UPDOWN_SHIFT))

/* PWM output invert */
#define PWM_C_INVERT_LINE                    ((uint32)(PWM_C__INVERSE         <<  \
                                                                  PWM_C_INV_OUT_SHIFT))
#define PWM_C_INVERT_LINE_N                  ((uint32)(PWM_C__INVERSE         <<  \
                                                                  PWM_C_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define PWM_C_TRIG_RISING                    ((uint32)PWM_C__TRIG_RISING)
#define PWM_C_TRIG_FALLING                   ((uint32)PWM_C__TRIG_FALLING)
#define PWM_C_TRIG_BOTH                      ((uint32)PWM_C__TRIG_BOTH)
#define PWM_C_TRIG_LEVEL                     ((uint32)PWM_C__TRIG_LEVEL)

/* Interrupt mask */
#define PWM_C_INTR_MASK_TC                   ((uint32)PWM_C__INTR_MASK_TC)
#define PWM_C_INTR_MASK_CC_MATCH             ((uint32)PWM_C__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define PWM_C_CC_MATCH_SET                   (0x00u)
#define PWM_C_CC_MATCH_CLEAR                 (0x01u)
#define PWM_C_CC_MATCH_INVERT                (0x02u)
#define PWM_C_CC_MATCH_NO_CHANGE             (0x03u)
#define PWM_C_OVERLOW_SET                    (0x00u)
#define PWM_C_OVERLOW_CLEAR                  (0x04u)
#define PWM_C_OVERLOW_INVERT                 (0x08u)
#define PWM_C_OVERLOW_NO_CHANGE              (0x0Cu)
#define PWM_C_UNDERFLOW_SET                  (0x00u)
#define PWM_C_UNDERFLOW_CLEAR                (0x10u)
#define PWM_C_UNDERFLOW_INVERT               (0x20u)
#define PWM_C_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define PWM_C_PWM_MODE_LEFT                  (PWM_C_CC_MATCH_CLEAR        |   \
                                                         PWM_C_OVERLOW_SET           |   \
                                                         PWM_C_UNDERFLOW_NO_CHANGE)
#define PWM_C_PWM_MODE_RIGHT                 (PWM_C_CC_MATCH_SET          |   \
                                                         PWM_C_OVERLOW_NO_CHANGE     |   \
                                                         PWM_C_UNDERFLOW_CLEAR)
#define PWM_C_PWM_MODE_ASYM                  (PWM_C_CC_MATCH_INVERT       |   \
                                                         PWM_C_OVERLOW_SET           |   \
                                                         PWM_C_UNDERFLOW_CLEAR)

#if (PWM_C_CY_TCPWM_V2)
    #if(PWM_C_CY_TCPWM_4000)
        #define PWM_C_PWM_MODE_CENTER                (PWM_C_CC_MATCH_INVERT       |   \
                                                                 PWM_C_OVERLOW_NO_CHANGE     |   \
                                                                 PWM_C_UNDERFLOW_CLEAR)
    #else
        #define PWM_C_PWM_MODE_CENTER                (PWM_C_CC_MATCH_INVERT       |   \
                                                                 PWM_C_OVERLOW_SET           |   \
                                                                 PWM_C_UNDERFLOW_CLEAR)
    #endif /* (PWM_C_CY_TCPWM_4000) */
#else
    #define PWM_C_PWM_MODE_CENTER                (PWM_C_CC_MATCH_INVERT       |   \
                                                             PWM_C_OVERLOW_NO_CHANGE     |   \
                                                             PWM_C_UNDERFLOW_CLEAR)
#endif /* (PWM_C_CY_TCPWM_NEW) */

/* Command operations without condition */
#define PWM_C_CMD_CAPTURE                    (0u)
#define PWM_C_CMD_RELOAD                     (8u)
#define PWM_C_CMD_STOP                       (16u)
#define PWM_C_CMD_START                      (24u)

/* Status */
#define PWM_C_STATUS_DOWN                    (1u)
#define PWM_C_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   PWM_C_Init(void);
void   PWM_C_Enable(void);
void   PWM_C_Start(void);
void   PWM_C_Stop(void);

void   PWM_C_SetMode(uint32 mode);
void   PWM_C_SetCounterMode(uint32 counterMode);
void   PWM_C_SetPWMMode(uint32 modeMask);
void   PWM_C_SetQDMode(uint32 qdMode);

void   PWM_C_SetPrescaler(uint32 prescaler);
void   PWM_C_TriggerCommand(uint32 mask, uint32 command);
void   PWM_C_SetOneShot(uint32 oneShotEnable);
uint32 PWM_C_ReadStatus(void);

void   PWM_C_SetPWMSyncKill(uint32 syncKillEnable);
void   PWM_C_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   PWM_C_SetPWMDeadTime(uint32 deadTime);
void   PWM_C_SetPWMInvert(uint32 mask);

void   PWM_C_SetInterruptMode(uint32 interruptMask);
uint32 PWM_C_GetInterruptSourceMasked(void);
uint32 PWM_C_GetInterruptSource(void);
void   PWM_C_ClearInterrupt(uint32 interruptMask);
void   PWM_C_SetInterrupt(uint32 interruptMask);

void   PWM_C_WriteCounter(uint32 count);
uint32 PWM_C_ReadCounter(void);

uint32 PWM_C_ReadCapture(void);
uint32 PWM_C_ReadCaptureBuf(void);

void   PWM_C_WritePeriod(uint32 period);
uint32 PWM_C_ReadPeriod(void);
void   PWM_C_WritePeriodBuf(uint32 periodBuf);
uint32 PWM_C_ReadPeriodBuf(void);

void   PWM_C_WriteCompare(uint32 compare);
uint32 PWM_C_ReadCompare(void);
void   PWM_C_WriteCompareBuf(uint32 compareBuf);
uint32 PWM_C_ReadCompareBuf(void);

void   PWM_C_SetPeriodSwap(uint32 swapEnable);
void   PWM_C_SetCompareSwap(uint32 swapEnable);

void   PWM_C_SetCaptureMode(uint32 triggerMode);
void   PWM_C_SetReloadMode(uint32 triggerMode);
void   PWM_C_SetStartMode(uint32 triggerMode);
void   PWM_C_SetStopMode(uint32 triggerMode);
void   PWM_C_SetCountMode(uint32 triggerMode);

void   PWM_C_SaveConfig(void);
void   PWM_C_RestoreConfig(void);
void   PWM_C_Sleep(void);
void   PWM_C_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define PWM_C_BLOCK_CONTROL_REG              (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_C_BLOCK_CONTROL_PTR              ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define PWM_C_COMMAND_REG                    (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_C_COMMAND_PTR                    ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define PWM_C_INTRRUPT_CAUSE_REG             (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_C_INTRRUPT_CAUSE_PTR             ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define PWM_C_CONTROL_REG                    (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__CTRL )
#define PWM_C_CONTROL_PTR                    ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__CTRL )
#define PWM_C_STATUS_REG                     (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__STATUS )
#define PWM_C_STATUS_PTR                     ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__STATUS )
#define PWM_C_COUNTER_REG                    (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_C_COUNTER_PTR                    ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__COUNTER )
#define PWM_C_COMP_CAP_REG                   (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__CC )
#define PWM_C_COMP_CAP_PTR                   ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__CC )
#define PWM_C_COMP_CAP_BUF_REG               (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_C_COMP_CAP_BUF_PTR               ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__CC_BUFF )
#define PWM_C_PERIOD_REG                     (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_C_PERIOD_PTR                     ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__PERIOD )
#define PWM_C_PERIOD_BUF_REG                 (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_C_PERIOD_BUF_PTR                 ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define PWM_C_TRIG_CONTROL0_REG              (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_C_TRIG_CONTROL0_PTR              ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define PWM_C_TRIG_CONTROL1_REG              (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_C_TRIG_CONTROL1_PTR              ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define PWM_C_TRIG_CONTROL2_REG              (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_C_TRIG_CONTROL2_PTR              ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define PWM_C_INTERRUPT_REQ_REG              (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR )
#define PWM_C_INTERRUPT_REQ_PTR              ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR )
#define PWM_C_INTERRUPT_SET_REG              (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_C_INTERRUPT_SET_PTR              ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR_SET )
#define PWM_C_INTERRUPT_MASK_REG             (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_C_INTERRUPT_MASK_PTR             ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR_MASK )
#define PWM_C_INTERRUPT_MASKED_REG           (*(reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR_MASKED )
#define PWM_C_INTERRUPT_MASKED_PTR           ( (reg32 *) PWM_C_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define PWM_C_MASK                           ((uint32)PWM_C_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define PWM_C_RELOAD_CC_SHIFT                (0u)
#define PWM_C_RELOAD_PERIOD_SHIFT            (1u)
#define PWM_C_PWM_SYNC_KILL_SHIFT            (2u)
#define PWM_C_PWM_STOP_KILL_SHIFT            (3u)
#define PWM_C_PRESCALER_SHIFT                (8u)
#define PWM_C_UPDOWN_SHIFT                   (16u)
#define PWM_C_ONESHOT_SHIFT                  (18u)
#define PWM_C_QUAD_MODE_SHIFT                (20u)
#define PWM_C_INV_OUT_SHIFT                  (20u)
#define PWM_C_INV_COMPL_OUT_SHIFT            (21u)
#define PWM_C_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define PWM_C_RELOAD_CC_MASK                 ((uint32)(PWM_C_1BIT_MASK        <<  \
                                                                            PWM_C_RELOAD_CC_SHIFT))
#define PWM_C_RELOAD_PERIOD_MASK             ((uint32)(PWM_C_1BIT_MASK        <<  \
                                                                            PWM_C_RELOAD_PERIOD_SHIFT))
#define PWM_C_PWM_SYNC_KILL_MASK             ((uint32)(PWM_C_1BIT_MASK        <<  \
                                                                            PWM_C_PWM_SYNC_KILL_SHIFT))
#define PWM_C_PWM_STOP_KILL_MASK             ((uint32)(PWM_C_1BIT_MASK        <<  \
                                                                            PWM_C_PWM_STOP_KILL_SHIFT))
#define PWM_C_PRESCALER_MASK                 ((uint32)(PWM_C_8BIT_MASK        <<  \
                                                                            PWM_C_PRESCALER_SHIFT))
#define PWM_C_UPDOWN_MASK                    ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                            PWM_C_UPDOWN_SHIFT))
#define PWM_C_ONESHOT_MASK                   ((uint32)(PWM_C_1BIT_MASK        <<  \
                                                                            PWM_C_ONESHOT_SHIFT))
#define PWM_C_QUAD_MODE_MASK                 ((uint32)(PWM_C_3BIT_MASK        <<  \
                                                                            PWM_C_QUAD_MODE_SHIFT))
#define PWM_C_INV_OUT_MASK                   ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                            PWM_C_INV_OUT_SHIFT))
#define PWM_C_MODE_MASK                      ((uint32)(PWM_C_3BIT_MASK        <<  \
                                                                            PWM_C_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define PWM_C_CAPTURE_SHIFT                  (0u)
#define PWM_C_COUNT_SHIFT                    (2u)
#define PWM_C_RELOAD_SHIFT                   (4u)
#define PWM_C_STOP_SHIFT                     (6u)
#define PWM_C_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define PWM_C_CAPTURE_MASK                   ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                  PWM_C_CAPTURE_SHIFT))
#define PWM_C_COUNT_MASK                     ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                  PWM_C_COUNT_SHIFT))
#define PWM_C_RELOAD_MASK                    ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                  PWM_C_RELOAD_SHIFT))
#define PWM_C_STOP_MASK                      ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                  PWM_C_STOP_SHIFT))
#define PWM_C_START_MASK                     ((uint32)(PWM_C_2BIT_MASK        <<  \
                                                                  PWM_C_START_SHIFT))

/* MASK */
#define PWM_C_1BIT_MASK                      ((uint32)0x01u)
#define PWM_C_2BIT_MASK                      ((uint32)0x03u)
#define PWM_C_3BIT_MASK                      ((uint32)0x07u)
#define PWM_C_6BIT_MASK                      ((uint32)0x3Fu)
#define PWM_C_8BIT_MASK                      ((uint32)0xFFu)
#define PWM_C_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define PWM_C_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define PWM_C_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(PWM_C_QUAD_ENCODING_MODES     << PWM_C_QUAD_MODE_SHIFT))       |\
         ((uint32)(PWM_C_CONFIG                  << PWM_C_MODE_SHIFT)))

#define PWM_C_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(PWM_C_PWM_STOP_EVENT          << PWM_C_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(PWM_C_PWM_OUT_INVERT          << PWM_C_INV_OUT_SHIFT))         |\
         ((uint32)(PWM_C_PWM_OUT_N_INVERT        << PWM_C_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(PWM_C_PWM_MODE                << PWM_C_MODE_SHIFT)))

#define PWM_C_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(PWM_C_PWM_RUN_MODE         << PWM_C_ONESHOT_SHIFT))
            
#define PWM_C_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(PWM_C_PWM_ALIGN            << PWM_C_UPDOWN_SHIFT))

#define PWM_C_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(PWM_C_PWM_KILL_EVENT      << PWM_C_PWM_SYNC_KILL_SHIFT))

#define PWM_C_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(PWM_C_PWM_DEAD_TIME_CYCLE  << PWM_C_PRESCALER_SHIFT))

#define PWM_C_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(PWM_C_PWM_PRESCALER        << PWM_C_PRESCALER_SHIFT))

#define PWM_C_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(PWM_C_TC_PRESCALER            << PWM_C_PRESCALER_SHIFT))       |\
         ((uint32)(PWM_C_TC_COUNTER_MODE         << PWM_C_UPDOWN_SHIFT))          |\
         ((uint32)(PWM_C_TC_RUN_MODE             << PWM_C_ONESHOT_SHIFT))         |\
         ((uint32)(PWM_C_TC_COMP_CAP_MODE        << PWM_C_MODE_SHIFT)))
        
#define PWM_C_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(PWM_C_QUAD_PHIA_SIGNAL_MODE   << PWM_C_COUNT_SHIFT))           |\
         ((uint32)(PWM_C_QUAD_INDEX_SIGNAL_MODE  << PWM_C_RELOAD_SHIFT))          |\
         ((uint32)(PWM_C_QUAD_STOP_SIGNAL_MODE   << PWM_C_STOP_SHIFT))            |\
         ((uint32)(PWM_C_QUAD_PHIB_SIGNAL_MODE   << PWM_C_START_SHIFT)))

#define PWM_C_PWM_SIGNALS_MODES                                                              \
        (((uint32)(PWM_C_PWM_SWITCH_SIGNAL_MODE  << PWM_C_CAPTURE_SHIFT))         |\
         ((uint32)(PWM_C_PWM_COUNT_SIGNAL_MODE   << PWM_C_COUNT_SHIFT))           |\
         ((uint32)(PWM_C_PWM_RELOAD_SIGNAL_MODE  << PWM_C_RELOAD_SHIFT))          |\
         ((uint32)(PWM_C_PWM_STOP_SIGNAL_MODE    << PWM_C_STOP_SHIFT))            |\
         ((uint32)(PWM_C_PWM_START_SIGNAL_MODE   << PWM_C_START_SHIFT)))

#define PWM_C_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(PWM_C_TC_CAPTURE_SIGNAL_MODE  << PWM_C_CAPTURE_SHIFT))         |\
         ((uint32)(PWM_C_TC_COUNT_SIGNAL_MODE    << PWM_C_COUNT_SHIFT))           |\
         ((uint32)(PWM_C_TC_RELOAD_SIGNAL_MODE   << PWM_C_RELOAD_SHIFT))          |\
         ((uint32)(PWM_C_TC_STOP_SIGNAL_MODE     << PWM_C_STOP_SHIFT))            |\
         ((uint32)(PWM_C_TC_START_SIGNAL_MODE    << PWM_C_START_SHIFT)))
        
#define PWM_C_TIMER_UPDOWN_CNT_USED                                                          \
                ((PWM_C__COUNT_UPDOWN0 == PWM_C_TC_COUNTER_MODE)                  ||\
                 (PWM_C__COUNT_UPDOWN1 == PWM_C_TC_COUNTER_MODE))

#define PWM_C_PWM_UPDOWN_CNT_USED                                                            \
                ((PWM_C__CENTER == PWM_C_PWM_ALIGN)                               ||\
                 (PWM_C__ASYMMETRIC == PWM_C_PWM_ALIGN))               
        
#define PWM_C_PWM_PR_INIT_VALUE              (1u)
#define PWM_C_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_PWM_C_H */

/* [] END OF FILE */
