/**
  ******************************************************************************
  * @file    pt32f0xx_adc.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020 
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the Analog to Digital Convertor (ADC) peripheral:
  *           + Initialization and Configuration
  *           + ADC Channels Configuration
  *           + Interrupts and flags management
  *
  *  @verbatim
================================================================================
                      ##### How to use this driver #####
================================================================================
    [..]
    (#) ADC pins configuration
       (++) Configure these ADC pins in analog mode using GPIO_PinAFConfig();  
    (#) Configure the ADC HighSpeedSampMode,data alignment,external
        trigger,and Enable/Disable the continuous mode
        using the ADC_Init() function.
    (#) Activate the ADC peripheral using ADC_Cmd() function.

    *** ADC channels group configuration ***
    ============================================
    [..] 
    (+) To configure the ADC channels features, use ADC_Init() and 
        ADC_ChannelConfig() functions.
    (+) To activate the continuous mode, use the ADC_ContinuousModeCmd()
        function.
    (+) To activate the calibration mode, use the ADC_GetCalibrationFactor() functions.
    (+) To read the ADC converted values, use the ADC_GetConversionValue()
        function.

  *  @endverbatim
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
#include "pt32f0xx_adc.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC 
  * @brief ADC driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ADC CFGR mask */
#define INICFR_CLEAR_MASK           ((uint32_t)0xFFFFF741)
#define CALIBRATION_TIMEOUT         ((uint32_t)0x00000FFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ADC_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the ADCx peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC ( 
  *         HighSpeedSampMode,Data Alignment, continuous mode activation, External 
  *         trigger source and edge).   
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral.
	          @param   ADC_ContinuousConvMode
						         @arg  ENABLE
										 @arg  DISABLE
						@param   ADC_HighSpeedSampMode
						         @arg  ENABLE
										 @arg  DISABLE
						@param   ADC_ExternalTrigConv
						         @arg  ADC_ExternalTrigConv_Timer0
										 @arg  ADC_ExternalTrigConv_Timer1
										 @arg  ADC_ExternalTrigConv_Timer2
										 @arg  ADC_ExternalTrigConv_Timer3
										 @arg  ADC_ExternalTrigConv_Software
										 @arg  ADC_ExternalTrigConv_EXTRising
						@param   ADC_DataAlign
						         @arg  ADC_DataAlign_Right
										 @arg  ADC_DataAlign_Left
  * @retval None
  */
void ADC_Init(CMSDK_ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_ContinuousConvMode));
	assert_param(IS_FUNCTIONAL_STATE(ADC_InitStruct->ADC_HighSpeedSampMode));
  assert_param(IS_ADC_EXTERNAL_TRIG_CONV(ADC_InitStruct->ADC_ExternalTrigConv));
  assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_DataAlign));

  /* Get the ADCx CR value */
  tmpreg = ADCx->CR;

  /* Clear MODE, SOC_SEL[3:2], TMR_SEL[5:4],HSSM and ALIGN bits */
  tmpreg &= INICFR_CLEAR_MASK;

  /*---------------------------- ADCx CR Configuration ---------------------*/
  tmpreg  |= ((uint32_t)(ADC_InitStruct->ADC_ContinuousConvMode) << 0x01) | 
	           (( ADC_InitStruct->ADC_ExternalTrigConv )) |
						 ((uint32_t)( ADC_InitStruct->ADC_HighSpeedSampMode ) << 0x07) |
             ((ADC_InitStruct->ADC_DataAlign) << 11);

  /* Write to ADCx CR */
  ADCx->CR = tmpreg;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
            @param   ADC_ContinuousConvMode
						         @arg  ENABLE
										 @arg  DISABLE
						@param   ADC_HighSpeedSampMode
						         @arg  ENABLE
										 @arg  DISABLE
						@param   ADC_ExternalTrigConv
						         @arg  ADC_ExternalTrigConv_Timer0
										 @arg  ADC_ExternalTrigConv_Timer1
										 @arg  ADC_ExternalTrigConv_Timer2
										 @arg  ADC_ExternalTrigConv_Timer3
										 @arg  ADC_ExternalTrigConv_Software
										 @arg  ADC_ExternalTrigConv_EXTRising
						@param   ADC_DataAlign
						         @arg  ADC_DataAlign_Right
										 @arg  ADC_DataAlign_Left
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
  /* Reset ADC init structure parameters values */

   /* Initialize the ADC_ContinuousConvMode member */
  ADC_InitStruct->ADC_ContinuousConvMode = DISABLE;	

  /* Initialize the ADC_ExternalTrigConv member */
  ADC_InitStruct->ADC_ExternalTrigConv = ADC_ExternalTrigConv_Software;
	

   /* Initialize the ADC_HighSpeedSampMode member */
  ADC_InitStruct->ADC_HighSpeedSampMode = DISABLE;		

  /* Initialize the ADC_DataAlign member */
  ADC_InitStruct->ADC_DataAlign = ADC_DataAlign_Right;

}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @param  NewState: new state of the ADCx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
						@arg  ENABLE
						@arg  DISABLE
  * @retval None
  */
void ADC_Cmd(CMSDK_ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ADEN bit to Enable the ADC peripheral */
    ADCx->CR |= (uint32_t)ADC_CR_ADEN;
  }
  else
  {
    /* Reset the ADEN to Disable the ADC peripheral */
    ADCx->CR &= (uint32_t)~ADC_CR_ADEN;
  }
}

/**
  * @brief  Configure the ADC to be clocked by the synchronous clock derived from
  *         the PCLK clock of the ADC bus interface divided by 1,2,4 or 8.
  * @note   This function can be called only when ADC is disabled.
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @param  ADC_ClockMode: This parameter can be :
  *            @arg ADC_ClockMode_SynClkDiv: ADC clocked by PCLK
  *            @arg ADC_ClockMode_SynClkDiv2: ADC clocked by PCLK/2
  *            @arg ADC_ClockMode_SynClkDiv4: ADC clocked by PCLK/4  
  *            @arg ADC_ClockMode_SynClkDiv8: ADC clocked by PCLK/8  
  * @retval None
  */
void ADC_ClockModeConfig(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_ClockMode)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLOCKMODE(ADC_ClockMode));

  ADCx->CR &=(uint32_t)~ADC_CR_CLKDIV;
  /* Configure the ADC Clock mode according to ADC_ClockMode */
  ADCx->CR |= (uint32_t)ADC_ClockMode;

}



/**
  * @brief  Enables or disables the Wait conversion mode.
  * @note   When the CPU clock is not fast enough to manage the data rate, a 
  *         Hardware delay can be introduced between ADC conversions to reduce 
  *         this data rate. 
  * @note   The Hardware delay is inserted after each conversions and until the
  *         previous data is read from the ADC data register
  * @note   This is a way to automatically adapt the speed of the ADC to the speed 
  *         of the system which will read the data.
  * @note   Any hardware triggers wich occur while a conversion is on going or 
  *         while the automatic Delay is applied are ignored 
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @param  NewState: new state of the ADC Auto-Delay.
  *          This parameter can be: ENABLE or DISABLE.
						@arg  ENABLE
						@arg  DISABLE
  * @retval None
  */
void ADC_HighSampModeCmd(CMSDK_ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the ADC Automatic Delayed conversion */
    ADCx->CR |= ADC_CR_HSSMP;
  }
  else
  {
    /* Disable the ADC Automatic Delayed conversion */
    ADCx->CR &= (uint32_t)~ADC_CR_HSSMP;
  }
}

/**
  * @}
  */


/** @defgroup ADC_Group5 Channels Configuration functions
 *  @brief    Channels Configuration functions 
 *
@verbatim
 ===============================================================================
            ##### Channels Configuration functions #####
 ===============================================================================
    [..] This section provides functions allowing to manage the ADC channels,
         it is composed of 3 sub sections :
         (#) Configuration and management functions for ADC channels: This subsection 
             provides functions allowing to configure the ADC channels :    
             (++) Select the ADC channels
             (++) Activate the Continuous Mode.
             (++) Select the conversion Trigger and Edge for ADC channels
             -@@- Please Note that the following features for ADC channels are configurated
                  using the ADC_Init() function : 
                  (+@@) Activate the Continuous Mode
                  (+@@) Select the conversion Trigger and Edge for ADC channels
         (#) Control the ADC peripheral : This subsection permits to command the ADC:
             (++) Start the ADC conversion .
         (#) Get the conversion data: This subsection provides an important function in 
             the ADC peripheral since it returns the converted data of the current 
             ADC channel. When the Conversion value is read, the EOC Flag is 
             automatically cleared.

@endverbatim
  * @{
  */

/**
  * @brief  Configures for the selected ADC channel enable.
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @param  ADC_Channel: the ADC channel to configure. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected, not available for STM32F031 devices
  *            @arg ADC_Channel_11: ADC Channel11 selected, not available for STM32F031 devices
  * @retval None
  */
void ADC_ChannelConfig(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_Channel)
{

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CHANNEL(ADC_Channel));
  /* Clear the ADC Channel Selection bits */
  ADCx->CR &=(uint32_t)~ADC_CR_CHSEL;
  /* Configure the ADC Channel */
  ADCx->CR |= (uint32_t)ADC_Channel;

}

/**
  * @brief  Enable the Continuous mode for the selected ADCx channels.
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @param  NewState: new state of the Continuous mode.
  *         This parameter can be: ENABLE or DISABLE.
					  @arg  ENABLE
					  @arg  DISABLE
  * @note   It is not possible to have both discontinuous mode and continuous mode
  *         enabled. In this case (If DISCEN and CONT are Set), the ADC behaves 
  *         as if continuous mode was disabled.
  * @retval None
  */
void ADC_ContinuousModeCmd(CMSDK_ADC_TypeDef* ADCx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
  {
    /* Enable the Continuous mode*/
    ADCx->CR |= (uint32_t)ADC_CR_CONT;
  }
  else
  {
    /* Disable the Continuous mode */
    ADCx->CR &= (uint32_t)(~ADC_CR_CONT);
  }
}



/**
  * @brief  Active the Calibration operation for the selected ADC.
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @retval ADC Offset Calibration Value 
  */
uint32_t ADC_GetCalibrationFactor(CMSDK_ADC_TypeDef* ADCx)
{
  uint32_t tmpreg = 0, calibrationcounter = 0, calibrationstatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  /* Set the ADC calibartion */
  ADCx->CR |= (uint32_t)ADC_CR_ADCAL;
  /*Enables ADC conversion */	
  ADCx->CR |= (uint32_t)ADC_CR_ADEN;	
  
  /* Wait until ADC is readied */
  do
  {
    calibrationstatus = ADCx->CR & ADC_SR_ADRDY;
    calibrationcounter++;  
  } while((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus == 0x00));
    
  if((uint32_t)(ADCx->CR & ADC_CR_ADCAL) == SET)
  {
  ADCx->CR |=ADC_CR_ADSTART;		
  do
  {
    calibrationstatus = ADCx->CR & ADC_SR_EOC;
    calibrationcounter++;  
  } while((calibrationcounter != CALIBRATION_TIMEOUT) && (calibrationstatus == 0x00));		

    ADCx->CR |=	ADC_SR_EOC;
    /*Get the Offset Calibration Value from the ADC data register */
    tmpreg = ADCx->DR;
  }
  else
  {
    /* Error factor */
    tmpreg = 0x00000000;
  }
    /* Reset the ADEN to Disable the ADC peripheral */
    ADCx->CR &= (uint32_t)~ADC_CR_ADEN;	
  return tmpreg;
}

/**
  * @brief  Stop the on going conversions for the selected ADC.
  * @note   When ADSTP is set, any on going conversion is aborted, and the ADC 
  *         data register is not updated with current conversion. 
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @retval None
  */
void ADC_StopOfConversion(CMSDK_ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  ADCx->CR &= (uint32_t)~ADC_CR_ADSTART;
}

/**
  * @brief  Start Conversion for the selected ADC channels.
  * @note   In continuous mode, ADSTART is not cleared by hardware with the 
  *         assertion of EOSEQ because the sequence is automatic relaunched
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @retval None
  */
void ADC_StartOfConversion(CMSDK_ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  
  ADCx->CR |= (uint32_t)ADC_CR_ADSTART;
}

/**
  * @brief  Returns the last ADCx conversion result data for ADC channel.  
  * @param  ADCx: select the ADC peripheral.
	          @arg  ADC
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(CMSDK_ADC_TypeDef* ADCx)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));

  /* Return the selected ADC conversion value */
  return (uint16_t) ADCx->DR;
}

/**
  * @}
  */



/** @defgroup ADC_Group7 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions.
 *
@verbatim   
 ===============================================================================
            ##### Interrupts and flags management functions #####
 ===============================================================================
    [..] This section provides functions allowing to configure the ADC Interrupts 
         and get the status and clear flags and Interrupts pending bits.
  
    [..] The ADC provide 6 Interrupts sources and 11 Flags which can be divided into 
         3 groups:

  *** Flags for ADC status ***
  ======================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_ADRDY : This flag is set after the ADC has been enabled (bit ADEN=1)
               and when the ADC reaches a state where it is ready to accept conversion requests


  *** Flags and Interrupts for ADC channel conversion ***
  =====================================================
    [..]
        (+)Flags :
           (##) ADC_FLAG_EOC : This flag is set by hardware at the end of each conversion
                of a channel when a new data result is available in the data register

        (+)Interrupts :
           (##) ADC_IT_EOC : specifies the interrupt source for end of conversion .

    [..] The user should identify which mode will be used in his application to 
         manage the ADC controller events: Polling mode or Interrupt mode.
  
    [..] In the Polling Mode it is advised to use the following functions:
         (+) ADC_GetFlagStatus() : to check if flags events occur.
         (+) ADC_ClearFlag()     : to clear the flags events.
  
    [..] In the Interrupt Mode it is advised to use the following functions:
         (+) ADC_ITConfig()       : to enable or disable the interrupt source.
         (+) ADC_GetITStatus()    : to check if Interrupt occurs.
         (+) ADC_ClearITPendingBit() : to clear the Interrupt pending Bit 
             (corresponding Flag).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_ADC_CONFIG_IT(ADC_IT)); 

  if (NewState != DISABLE)
  {
    /* Enable the selected ADC interrupts */
    ADCx->CR |= ADC_IT;
  }
  else
  {
    /* Disable the selected ADC interrupts */
    ADCx->CR &= (~(uint32_t)ADC_IT);
  }
}

/**
  * @brief  Checks whether the specified ADC flag is set or not.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to check. 
  *          This parameter can be one of the following values:
  *            @arg ADC_FLAG_EOC: End of conversion flag
  *            @arg ADC_FLAG_ADRDY: ADC Ready flag
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetFlagStatus(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_FLAG(ADC_FLAG));
  /* Check the status of the specified ADC flag */
  if ((ADCx->SR & ADC_FLAG) != (uint32_t)RESET)
  {
    /* ADC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_FLAG is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_FLAG: specifies the flag to clear. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_FLAG_EOC: End of conversion flag
  * @retval None
  */
void ADC_ClearFlag(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_CLEAR_FLAG(ADC_FLAG));

  /* Clear the selected ADC flags */
  ADCx->SR = (uint32_t)ADC_FLAG;
}

/**
  * @brief  Checks whether the specified ADC interrupt has occurred or not.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral
  * @param  ADC_IT: specifies the ADC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_EOC: End of conversion interrupt 
  * @retval The new state of ADC_IT (SET or RESET).
  */
ITStatus ADC_GetITStatus(CMSDK_ADC_TypeDef* ADCx, uint32_t ADC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_ADC_ALL_PERIPH(ADCx));
  assert_param(IS_ADC_GET_IT(ADC_IT));

  /* Get the ADC_IT enable bit status */
  enablestatus = (uint32_t)(ADCx->CR & ADC_IT); 

  /* Check the status of the specified ADC interrupt */
  if (((uint32_t)(ADCx->SR & ADC_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* ADC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* ADC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the ADC_IT status */
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
