/**
  ******************************************************************************
  * @file    pt32f0xx_pwr.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Power Controller (PWR) peripheral:
  *           + Backup Domain Access
  *           + PVD configuration
  *           + WakeUp pins configuration
  *           + Low Power modes configuration
  *           + Flags management
  *
  ******************************************************************************
  * @attention
  *
  *
  *
  * 
  * 
  *
  *
  *      
  *
  *
  * 
  *
  *
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx_pwr.h"
#include "pt32f0xx_ana.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup PWR 
  * @brief PWR driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* ------------------ PWR registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_DS_MASK               ((uint32_t)0xFFFFFFFC)
#define CR_PLS_MASK              ((uint32_t)0xFFFFFFFE)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup PWR_Private_Functions
  * @{
  */


/** @defgroup PWR_Group2 PVD configuration functions
 *  @brief   PVD configuration functions 
 *
@verbatim
  ==============================================================================
                    ##### PVD configuration functions #####
  ==============================================================================
  [..]
  (+) The PVD is used to monitor the VDD power supply by comparing it to a threshold
      selected by the PVD Level (PLS[2:0] bits in the PWR_CR).
  (+) A PVDO flag is available to indicate if VDD/VDDA is higher or lower than the 
      PVD threshold. This event is internally connected to the EXTI line16
      and can generate an interrupt if enabled through the EXTI registers.
  (+) The PVD is stopped in Standby mode.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the voltage threshold detected by the Power Voltage Detector(PVD).
  * @param  PWR_PVDLevel: specifies the PVD detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_PVDLevel_0
  *             @arg PWR_PVDLevel_1
  *             @arg PWR_PVDLevel_2
  *             @arg PWR_PVDLevel_3
  *             @arg PWR_PVDLevel_4
  *             @arg PWR_PVDLevel_5
  *             @arg PWR_PVDLevel_6
  *             @arg PWR_PVDLevel_7
  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each 
  *         detection level.
  * @retval None
  */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
  uint32_t tmpreg = 0;
  
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));
  
  tmpreg = CMSDK_ANAMIX->VDD_LVD_CON;
  
  tmpreg &= CR_PLS_MASK;
  
  tmpreg |= PWR_PVDLevel;
  
  /* Store the new value */
  CMSDK_ANAMIX->VDD_LVD_CON = tmpreg;
}

/**
  * @brief  Configures the voltage threshold detected by the LDO Voltage Detector(LVD).
  * @param  PWR_LVDLevel: specifies the LVD detection level
  *          This parameter can be one of the following values:
  *             @arg PWR_LVDLevel_0
  *             @arg PWR_LVDLevel_1
  *             @arg PWR_LVDLevel_2

  * @note   Refer to the electrical characteristics of your device datasheet for
  *         more details about the voltage threshold corresponding to each 
  *         detection level.
  * @retval None
  */
void PWR_LVDLevelConfig(uint32_t PWR_LVDLevel)
{
  
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_LVDLevel));  
  /* Store the new value */
  CMSDK_ANAMIX->LDO_LVD_CON = PWR_LVDLevel;
}

/**
  * @brief  Enables or disables the Power Voltage Detector(PVD).
  * @note   This function is not applicable for STM32F030 devices.    
  * @param  NewState: new state of the PVD.
  *          This parameter can be: ENABLE or DISABLE.
            @arg ENABLE
            @arg DISABLE
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the PVD */
    CMSDK_ANAMIX->VDD_LVD_CON |= ANAMIX_VDDLVDCTRL_EN;
  }
  else
  {
    /* Disable the PVD */
    CMSDK_ANAMIX->VDD_LVD_CON &= (uint32_t)~((uint32_t)ANAMIX_VDDLVDCTRL_EN);
  } 
}

/**
  * @}
  */



/** @defgroup PWR_Group4 Low Power modes configuration functions
 *  @brief   Low Power modes configuration functions 
 *
@verbatim
  ==============================================================================
              ##### Low Power modes configuration functions #####
  ==============================================================================

    [..] The devices feature three low-power modes:
    (+) Sleep mode: Cortex-M0 core stopped, peripherals kept running.
    (+) Standby mode: VCORE domain powered off

  *** Sleep mode *** 
  ==================
  [..] 
    (+) Entry:
        (++) The Sleep mode is entered by executing the WFE() or WFI() instructions.
    (+) Exit:
        (++) Any peripheral interrupt acknowledged by the nested vectored interrupt 
             controller (NVIC) can wake up the device from Sleep mode.

  *** Standby mode *** 
  ====================
  [..] The Standby mode allows to achieve the lowest power consumption. It is based 
       on the Cortex-M0 deepsleep mode, with the voltage regulator disabled. 
       The VCORE domain is consequently powered off. the HSI
       oscillator and the HSE oscillator are also switched off. SRAM and register 
       contents are lost except for the Backup domain
   
  [..] The voltage regulator is OFF.

    (+) Entry:
        (++) The Standby mode is entered using the PWR_EnterSTANDBYMode() function.
    (+) Exit:
        (++) WKUP pin rising edge, tamper event, time-stamp event, external reset in NRST pin, IWDG reset.

  *** Auto-wakeup (AWU) from low-power mode *** 
  =============================================
  [..] The MCU can be woken up from low-power mode by a time-stamp event, 
	     or a comparator event, without depending on an external interrupt (Auto-wakeup mode).
			 
@endverbatim
  * @{
  */

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in Run mode.
  * @param  PWR_SLEEPEntry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *             @arg PWR_SLEEPEntry_WFI: enter SLEEP mode with WFI instruction
  *             @arg PWR_SLEEPEntry_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSleepMode(uint8_t PWR_SLEEPEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_SLEEP_ENTRY(PWR_SLEEPEntry));

  /* Clear SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);
  
  /* Select SLEEP mode entry -------------------------------------------------*/
  if(PWR_SLEEPEntry == PWR_SLEEPEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __SEV();
    __WFE(); 
    __WFE();
  }
}



/**
  * @brief  Enters STANDBY mode.
    @param  PWR_DeepStandbyEntry: Select standby mode.
  *             @arg PWR_STANDBYEntry_WFI: enter DEEPSLEEP mode with WFI instruction
  *             @arg PWR_STANDBYEntry_WFE: enter DEEPSLEEP mode with WFE instruction
  * @retval None
  */
void PWR_EnterSTANDBYMode(uint8_t PWR_DeepStandbyEntry)
{
  /* Check the parameters */
  assert_param(IS_PWR_STANDBY_ENTRY(PWR_DeepStandbyEntry));
  /* Set SLEEPDEEP bit of Cortex-M0 System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

  /* Request Wait For Interrupt */
	  /* Select SLEEP mode entry -------------------------------------------------*/
  if(PWR_DeepStandbyEntry == PWR_STANDBYEntry_WFI)
  {
    /* Request Wait For Interrupt */
    __WFI();
  }
  else
  {
    /* Request Wait For Event */
    __WFE(); 
    __WFE();
  }
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/
