/**
  ******************************************************************************
  * @file    pt32f0xx_wdg.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020   
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Independent watchdog (IWDG) peripheral:           
  *           + Prescaler and Counter configuration
  *           + IWDG activation
  *           + Flag management
  *
  *  @verbatim  
  *  
  ============================================================================== 
                          ##### WDG features #####
  ============================================================================== 
    [..] The IWDG can be started by either software or hardware (configurable
         through option byte).
             
    [..] The IWDG is clocked by its own dedicated low-speed clock (LSI) and
         thus stays active even if the main clock fails.
         Once the IWDG is started, the LSI is forced ON and cannot be disabled
         (LSI cannot be disabled too), and the counter starts counting down from 
         the reset value of 0xFFF. When it reaches the end of count value (0x000)
         a system reset is generated.
         The IWDG counter should be reloaded at regular intervals to prevent
         an MCU reset.
                             
    [..] The IWDG is implemented in the VDD voltage domain that is still functional
         in STOP and STANDBY mode (IWDG reset can wake-up from STANDBY).
              
    [..] IWDGRST flag in RCC_CSR register can be used to inform when a IWDG
         reset occurs.
              
    [..] Min-max timeout value @40KHz (LSI): ~0.1ms / ~28.3s
         The IWDG timeout may vary due to LSI frequency dispersion. PT32F0xx
         devices provide the capability to measure the LSI frequency (LSI clock
         should be seleted as RTC clock which is internally connected to TIM10 CH1
         input capture). The measured value can be used to have an IWDG timeout with
         an acceptable accuracy. 
         For more information, please refer to the PT32F0xx Reference manual.
            
                          ##### How to use this driver ##### 
  ============================================================================== 
    [..] This driver allows to use IWDG peripheral with either window option enabled
         or disabled. To do so follow one of the two procedures below.
    (#) Window option is enabled:    
        (++) Start the IWDG using IWDG_Enable() function, when the IWDG is used
             in software mode (no need to enable the LSI, it will be enabled
             by hardware).        
        (++) Enable write access to IWDG_PR and IWDG_RLR registers using
             IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) function.
        (++) Configure the IWDG prescaler using IWDG_SetPrescaler() function.
        (++) Configure the IWDG counter value using IWDG_SetReload() function.
             This value will be loaded in the IWDG counter each time the counter
             is reloaded, then the IWDG will start counting down from this value.
        (++) Wait for the IWDG registers to be updated using IWDG_GetFlagStatus() function.
        (++) Configure the IWDG refresh window using IWDG_SetWindowValue() function.

    (#) Window option is disabled:    
        (++) Enable write access to IWDG_PR and IWDG_RLR registers using
             IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable) function.
        (++) Configure the IWDG prescaler using IWDG_SetPrescaler() function.
        (++) Configure the IWDG counter value using IWDG_SetReload() function.
             This value will be loaded in the IWDG counter each time the counter
             is reloaded, then the IWDG will start counting down from this value.
        (++) Wait for the IWDG registers to be updated using IWDG_GetFlagStatus() function.
        (++) reload the IWDG counter at regular intervals during normal operation 
             to prevent an MCU reset, using IWDG_ReloadCounter() function.
        (++) Start the IWDG using IWDG_Enable() function, when the IWDG is used
             in software mode (no need to enable the LSI, it will be enabled
             by hardware).
              
    @endverbatim
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
#include "pt32f0xx_wdg.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG 
  * @brief IWDG driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------- IWDG registers bit mask ----------------------------*/
/* KR register bit mask */
#define KR_KEY_DISABLE   ((uint16_t)0xFFFFFFFF)
#define KR_KEY_ENABLE    ((uint16_t)0x1ACCE551)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup IWDG_Private_Functions
  * @{
  */

/** @defgroup IWDG_Group1 Prescaler and Counter configuration functions
 *  @brief   Prescaler and Counter configuration functions
 *
@verbatim   
  ==============================================================================
            ##### Prescaler and Counter configuration functions #####
  ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables write access all registers.
	* @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @param  IWDG_WriteAccess: new state of write access to all registers.
  *         This parameter can be one of the following values:
  *         @arg WDG_WriteAccess_Enable
  *         @arg WDG_WriteAccess_Disable
  * @retval None
  */
void WDG_WriteAccessCmd(CMSDK_WDG_TypeDef* WDGx, uint32_t WDG_WriteAccess)
{
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));
  assert_param(IS_WDG_WRITE_ACCESS(WDG_WriteAccess));
  WDGx->KR = WDG_WriteAccess;
}


/**
  * @brief  Sets WDG Reload value.
  * @param  WDGx: specifies watchdog type.
  * @param  Reload: specifies the WDG Reload value.
  *         This parameter must be a number between 0 and 0xFFFFFFFF.
            @arg  IWDG
            @arg  SWDG
  * @retval None
  */
void WDG_SetReload(CMSDK_WDG_TypeDef* WDGx, uint32_t Reload)
{
  /* Check the parameters */
  assert_param(IS_WDG_RELOAD(Reload));
	assert_param(IS_WDG_ALL_PERIPH(WDGx));
  WDGx->RLR = Reload;
}

/**
  * @brief  Reloads WDG counter with value defined in the reload register
  *   (write access to all registers disabled).
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @retval None
  */
void WDG_ReloadCounter(CMSDK_WDG_TypeDef* WDGx)
{
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));	
  WDGx->FWDG = 0xFFFFFFFF;
}



/**
  * @}
  */

/** @defgroup IWDG_Group2 IWDG activation function
 *  @brief   IWDG activation function 
 *
@verbatim   
 ==============================================================================
                          ##### IWDG activation function #####
 ==============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Enables WDG (write access to all registers disabled).
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @param  NewState: This parameter can be ENABLE or DISABLE.
          	@arg  ENABLE
            @arg  DISABLE
  * @retval None
  */
void WDG_AccessEnable(CMSDK_WDG_TypeDef* WDGx, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));		
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (NewState != DISABLE)
  {
    /* Enable the WDG */
    WDGx->KR = KR_KEY_ENABLE;
  }
  else
  {
    /* Disable the WDG */
    WDGx->KR = KR_KEY_DISABLE;
  }
}

/**
  * @brief  Check the locking status of WDG
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @retval Return the locking status of WDG 
  */
FlagStatus WDG_GetLockStatus(CMSDK_WDG_TypeDef* WDGx)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));		
  if ((WDGx->KR & WDG_KR_LOCK) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}


/**
  * @brief  Enables or disables the specified WDG
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @param  NewState: new state of the WDG. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDG_Cmd(CMSDK_WDG_TypeDef* WDGx, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));	
  assert_param(IS_FUNCTIONAL_STATE(NewState));	
  if (NewState != DISABLE)
  {
    /* Enable the IWDG */
    WDGx->CR |= WDG_CR_INTE;
  }
  else
  {
    /* Disable the IWDG */
    WDGx->CR &= ~WDG_CR_INTE;
  }
}
/**
  * @brief  Enables or disables the WDG RESET.
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @param  NewState: new state of the WDG. 
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDG_RstCmd(CMSDK_WDG_TypeDef* WDGx, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));	
  assert_param(IS_FUNCTIONAL_STATE(NewState));	
  if (NewState != DISABLE)
  {
    /* Enable the IWDG RESET */
    WDGx->CR |= WDG_CR_RSTE;
  }
  else
  {
    /* Disable the IWDG RESET*/
    WDGx->CR &= ~WDG_CR_RSTE;
  }
}

/**
  * @brief  WDG debug pending control
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG
  * @param  NewState: 
  *         @arg  ENABLE  
            @arg  DISABLE
  * @retval None
  */
void WDG_DbgeRunCmd(CMSDK_WDG_TypeDef* WDGx, FunctionalState NewState)
{
  /* Check the parameters */
	assert_param(IS_WDG_ALL_PERIPH(WDGx));	
  assert_param(IS_FUNCTIONAL_STATE(NewState));	
  if (NewState != DISABLE)
  {
    /* Enable the IWDG RESET */
    WDGx->CR |= WDG_CR_DBGE;
  }
  else
  {
    /* Disable the IWDG RESET*/
    WDGx->CR &= ~WDG_CR_DBGE;
  }
}
/**
  * @}
  */

/** @defgroup IWDG_Group3 Flag management function 
 *  @brief  Flag management function  
 *
@verbatim   
 ===============================================================================
                      ##### Flag management function ##### 
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Checks whether the specified WDG flag is set or not.
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG          
  * @param  WDG_FLAG£ºhis parameter can be one of the following values:
  *         @arg  WDG_FLAG_RVU  
  * @retval The new state of WDG_FLAG (SET or RESET).
  */
FlagStatus WDG_GetFlagStatus(CMSDK_WDG_TypeDef* WDGx, uint16_t WDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_WDG_FLAG(WDG_FLAG));
	assert_param(IS_WDG_ALL_PERIPH(WDGx));		
  if ((WDGx->RIS & WDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the flag status */
  return bitstatus;
}

/**
  * @brief  Checks whether the WDG interrupt has occurred or not.
  * @param  WDGx: specifies watchdog type.
            @arg  IWDG
            @arg  SWDG   
  * @param  WDG_IT: specifies the WDG interrupt source to check. 
            @arg    WDG_IT_RVU 
  * @retval The new state of WDG_IT (SET or RESET).
  */

ITStatus WDG_GetITStatus(CMSDK_WDG_TypeDef* WDGx, uint32_t WDG_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_WDG_GET_IT(WDG_IT));
	assert_param(IS_WDG_ALL_PERIPH(WDGx));	
  /* Get the ADC_IT enable bit status */
  enablestatus = (uint32_t)(WDGx->CR & WDG_IT); 

  /* Check the status of the specified WDG interrupt */
  if (((uint32_t)(WDGx->EIS & WDG_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* WDG_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* WDG_IT is reset */
    bitstatus = RESET;
  }
  /* Return the WDG_IT status */
  return  bitstatus;
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
