/**
  ******************************************************************************
  * @file    pt32f0xx_tim.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the TIM peripheral:
  *            + TimeBase management
  *            + Output Compare management
  *            + Input Capture management
  *            + Interrupts, flags management
  *            + Clocks management  
  *              
  *  @verbatim
  
 ===============================================================================
                    ##### How to use this driver #####
 ===============================================================================
    [..] This driver provides functions to configure and program the TIM 
         of all PT32F0xx devices These functions are split in 8 groups: 
         (#) TIM TimeBase management: this group includes all needed functions 
             to configure the TM Timebase unit:
             (++) Set/Get Prescaler.
             (++) Set/Get Autoreload.
             (++) Counter modes configuration.
             (++) Set Clock division.
             (++) Select the One Pulse mode.
             (++) Update Request Configuration.
             (++) Update Disable Configuration.
             (++) Auto-Preload Configuration.
             (++) Enable/Disable the counter.
  
         (#) TIM Output Compare management: this group includes all needed 
             functions to configure the Capture/Compare unit used in Output 
             compare mode: 
             (++) Configure each channel, independently, in Output Compare mode.
             (++) Select the output compare modes.
             (++) Select the Polarities of each channel.
             (++) Set/Get the Capture/Compare register values.
             (++) Select the Output Compare Fast mode. 
             (++) Select the Output Compare Forced mode.  
             (++) Output Compare-Preload Configuration. 
             (++) Clear Output Compare Reference.
             (++) Select the OCREF Clear signal.
             (++) Enable/Disable the Capture/Compare Channels.    
  
         (#) TIM Input Capture management: this group includes all needed 
             functions to configure the Capture/Compare unit used in 
             Input Capture mode:
             (++) Configure each channel in input capture mode.
             (++) Configure Channel1/2 in TIM Input mode.
             (++) Set the Input Capture Prescaler.
             (++) Get the Capture/Compare values.        
         (#) TIM clocks management: this group includes all needed functions 
             to configure the clock controller unit:
             (++) Select internal/External clock.
             (++) Select the external clock mode: ETR(Mode1/Mode2), TIx or ITRx.
  
         (#) TIM synchronization management: this group includes all needed. 
             functions to configure the Synchronization unit:
             (++) Select Input Trigger.  
             (++) Select Output Trigger.  
             (++) Select Master Slave Mode. 
             (++) ETR Configuration when used as external trigger.   
         (#) TIM specific remapping management includes the Remapping 
             configuration of specific timers
  
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
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx_tim.h"


/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup TIM 
  * @brief TIM driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup TIM_Private_Functions
  * @{
  */

/** @defgroup TIM_Group1 TimeBase management functions
 *  @brief   TimeBase management functions 
 *
@verbatim
 ===============================================================================
                 ##### TimeBase management functions #####
 ===============================================================================
  
        *** TIM Driver: how to use it in Timing(Time base) Mode ***
 ===============================================================================
    [..] To use the Timer in Timing(Time base) mode, the following steps are 
         mandatory:
         (#) Fill the TIM_TimeBaseInitStruct with the desired parameters.
         (#) Call TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct) to configure 
             the Time Base unit with the corresponding configuration.
         (#) Enable the NVIC if you need to generate the update interrupt. 
         (#) Enable the corresponding interrupt using the function 
             TIM_ITConfig(TIMx, TIM_IT_Update). 
         (#) Call the TIM_Cmd(ENABLE) function to enable the TIM counter.
    [..]
        (@) All other functions can be used seperatly to modify, if needed,
            a specific feature of the Timer. 

@endverbatim
  * @{
  */



/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
	          @arg TIM2
            @arg TIM3
            @arg TIM4
  *         @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  TimeBaseInit: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
	          @param  MatchValue£ºTimer matching value.
						        This parameter is between 0 and 0xFFFF.
						@param  Prescaler£ºTimer prescaler coefficient.
						        This parameter is between 0 and 0xFF.
						@param  CounterMode£ºCount direction control bits.
						        @arg  TIM_CNT_MODE_UP
										@arg  IM_CNT_MODE_DOWN
						@param  OVRSTEN£ºCount reset control bit when TC overflows.
						        @arg  ENABLE
									  @arg  DISABLE
  * @retval None
  */		
void TIM_TimeBaseInit(CMSDK_TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TimeBaseInit)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MATCH(TimeBaseInit->MatchValue));  
  assert_param(IS_TIM_PRESCALER(TimeBaseInit->Prescaler));
  assert_param(IS_TIM_COUNTERMODE(TimeBaseInit->CounterMode));
	assert_param(IS_FUNCTIONAL_STATE(TimeBaseInit->OVRSTEN));

  /* Set the counter match value */
  TIMx->MR0 = TimeBaseInit->MatchValue;
	
  /* Set the Prescaler value */
  TIMx->PR = TimeBaseInit->Prescaler;

  /* Select the Counter Mode */
	TIMx->MCR &= ~TIM_MCR_DIR;
	TIMx->MCR |=  (TimeBaseInit->CounterMode);	
	if((TimeBaseInit->OVRSTEN)==ENABLE)
	{
	 TIMx->MCR |= TIM_MCR_MR0R;
	}
	else
	{
	 TIMx->MCR &= ~TIM_MCR_MR0R;	
	}	

}


/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TimeBaseInit: pointer to a TIM_TimeBaseInitTypeDef structure which will be initialized.
	          @param  MatchValue£ºTimer matching value.
						        This parameter is between 0 and 0xFFFF.
						@param  Prescaler£ºTimer prescaler coefficient.
						        This parameter is between 0 and 0xFF.
						@param  CounterMode£ºCount direction control bits.
						        @arg  TIM_CNT_MODE_UP
										@arg  IM_CNT_MODE_DOWN
						@param  OVRSTEN£ºCount reset control bit when TC overflows.
						        @arg  ENABLE
									  @arg  DISABLE           
  * @retval None
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TimeBaseInit)
{
  /* Set the default configuration */
  TimeBaseInit->MatchValue = 0xFFFF;
  TimeBaseInit->Prescaler = 0x0000;
  TimeBaseInit->CounterMode = TIM_CNT_MODE_UP;
	TimeBaseInit->OVRSTEN = ENABLE;
}


/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral.  
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  Prescaler: specifies the Prescaler Register value (0~255)
            This parameter is between 0 and 0xFF.
  * @note   The Prescaler is loaded at the PC update event or immediatly
  * @retval None
  */
void TIM_PrescalerConfig(CMSDK_TIM_TypeDef* TIMx, uint8_t Prescaler)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALER(Prescaler));
  
  /* Set the Prescaler value */
  TIMx->PR = Prescaler;
}


/**
  * @brief  Configures the TIMx Match Value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  Reload: specifies the Counter reload value (0~65535)
              This parameter is between 0 and 0xFFFF.
  * @note   The value is loaded at the update event or immediatly
  * @retval None
  */
void TIM_SetCounterMatch(CMSDK_TIM_TypeDef* TIMx, uint16_t Reload)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));	
  assert_param( IS_TIM_COUNTER_MATCH(Reload));  

  /* Set the counter reload value */
  TIMx->MR0 = Reload;
}

/**
  * @brief  Configures the TIMx Current Value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  Counter: specifies the Counter register new value.(0~65535)
            This parameter is between 0 and 0xFFFF.
  *         @note   TIM4 is not allowed to set current cnt
  * @retval None
  */
void TIM_SetCounter(CMSDK_TIM_TypeDef* TIMx, uint16_t Counter)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));	
  assert_param(IS_TIM_COUNTER_VALUE(Counter));  
   
  /* Set the Counter Register value */
  TIMx->TC = Counter;
}

/**
  * @brief  Gets the TIMx Counter value at present.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral     
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @retval Counter Register value.
  */
uint16_t TIM_GetCounter(CMSDK_TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  
  /* Get the Counter Register value */
  return  TIMx->TC;
}

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral     
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @retval Prescaler Register value.
  */
uint16_t TIM_GetPrescaler(CMSDK_TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  
  /* Get the Prescaler Register value */
  return  TIMx->PR;
}

/**
  * @brief  Gets the TIMx Prescaler CNT value.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @retval Prescaler Current Register value.
  */
uint16_t TIM_GetPrescalerCnt(CMSDK_TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  
  /* Get the Prescaler Register value */
  return  TIMx->PC;
}

/**
  * @brief  Specifies the TIMx Counter Mode to be used.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
             @arg TIM2
             @arg TIM3
             @arg TIM4
  * @note   TIM4 is not allowed to set counter mode
  * @param  CounterMode: specifies the Counter Mode to be used.
  *          This parameter can be one of the following values:
  *            @arg TIM_CNT_MODE_UP: TIM Up Counting Mode
  *            @arg TIM_CNT_MODE_DOWN: TIM Down Counting Mode
  * @retval None
  */
void TIM_CounterModeConfig(CMSDK_TIM_TypeDef* TIMx, uint8_t CounterMode)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTERMODE(CounterMode));	
  
  /* Select the Counter Mode */
	TIMx->MCR  &= ~TIM_MCR_DIR;
	TIMx->MCR  |=  CounterMode;
	
}

/**
  * @brief  Enable or Disable update settiongs of the TIMx.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  NewState: This parameter can be ENABLE or DISABLE.
             @arg ENABLE
             @arg DISABLE
  * @retval None
  */
void TIM_UpdateCmd(CMSDK_TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));	

  if (NewState == ENABLE)
  {
    /* Set the update bit */
    TIMx->TCR |= TIM_TCR_UPDATE;
  }
  else
  {
    /* Reset the update bit */
    TIMx->TCR &= (~TIM_TCR_UPDATE);
  }
}

/**
  * @brief  Enable or Disable TIMx Counter.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral  
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  NewState: This parameter can be ENABLE or DISABLE.
             @arg ENABLE
             @arg DISABLE
  * @retval None
  */
void TIM_Cmd(CMSDK_TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));	

  if (NewState == ENABLE)
  {
    /* Set the update bit */
    TIMx->TCR |= TIM_TCR_EN;
  }
  else
  {
    /* Reset the update bit */
    TIMx->TCR &= (~TIM_TCR_EN);
  }
}

/**
  * @brief  Enables or disables the specified TIMx interrupts.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
             @arg TIM2
             @arg TIM3
             @arg TIM4
    @note TIM4 can only TIM_CNT_MODE_UP mode
  * @param  TIM_IT: Specify the TIM interrupts sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *          @arg TIM_INT_MR0 : TIM MR0 value match interrupt
  * @param  NewState: This parameter can be ENABLE or DISABLE.\
             @arg ENABLE
             @arg DISABLE
  * @retval None
  */
void TIM_ITConfig(CMSDK_TIM_TypeDef* TIMx, uint32_t TIM_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_INT(TIM_IT));	
  assert_param(IS_FUNCTIONAL_STATE(NewState));
	

    if (NewState != DISABLE)
    {
      /* Enable the interrupt sources */
      TIMx->MCR |= TIM_IT;
    }
    else
    {
      /* Disable the interrupt sources */
      TIMx->MCR &= ~TIM_IT;
	
	  }
}

/**
  * @brief  Check the interrupt flag bit for register overflow.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
            @arg TIM2
            @arg TIM3
            @arg TIM4
    @note   TIM4 can only TIM_CNT_MODE_UP mode.
  * @param  TIM_FLAG: Specify the flag to be checked.
  *         This parameter can be one of the following values:
  *         @arg TIM_FLAG_MR0       : TIM MR0 value match flag
  * @return FlagStatus of TIM_FLAG (SET or RESET).
  */
FlagStatus TIM_GetFlagStatus(CMSDK_TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_FLAG(TIM_FLAG));	

  if ((TIMx->ISR & TIM_FLAG) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clear the interrupt flag bit of register overflow.
  * @param  TIMx: where x can be 2, 3 and 4 to select the TIM peripheral 
            @arg TIM2
            @arg TIM3
            @arg TIM4
    @note   TIM4 can only TIM_CNT_MODE_UP mode
  * @param  TIM_FLAG: Specify the flag to be cleared.
  *         This parameter can be one of the following values:
  *         @arg TIM_FLAG_MR0: TIM MR0 value match flag
  * @retval None
  */
void TIM_ClearFlag(CMSDK_TIM_TypeDef* TIMx, uint32_t TIM_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_FLAG(TIM_FLAG));	
	
  /* Clear the flags */
  TIMx->ISR = TIM_FLAG;
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

/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/
