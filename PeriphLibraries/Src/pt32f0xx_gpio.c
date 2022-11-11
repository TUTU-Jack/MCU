/**
  ******************************************************************************
  * @file    pt32f0xx_gpio.c
  * @author  Application Team
  * @version V1.1.0
  * @date    15-September-2020
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the GPIO peripheral:
  *           + Initialization and Configuration functions
  *           + GPIO Read and Write functions
  *           + GPIO Alternate functions configuration functions
  *
  *  @verbatim
  *
  *
    ===========================================================================
                         ##### How to use this driver #####
    ===========================================================================
      [..]
      (#) Configure the GPIO pin(s) using GPIO_Init()
          Four possible configuration are available for each pin:
         (++) Input: Floating, Pull-up, Pull-down.
         (++) Output: Push-Pull (Pull-up, Pull-down or no Pull)
                      Open Drain (Pull-up, Pull-down or no Pull).
         (++) Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull)
                                  Open Drain (Pull-up, Pull-down or no Pull).
         (++) Analog: required mode when a pin is to be used as ADC channel,
              operational amplifier or comparator input.
      (#) Peripherals alternate function:
         (++) For ADC, operational amplifier and comparators, configure the desired pin in analog 
              mode using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN
         (++) For other peripherals (TIM, UART...):
              (+++) Connect the pin to the desired peripherals' Alternate 
                    Function (AF) using GPIO_PinAFConfig() function. 
              (+++) Select the type, pull-up/pull-down via GPIO_PuPd
              (+++) Call GPIO_Init() function
      (#) To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
      (#) To set/reset the level of a pin configured in output mode use
          GPIO_SetBits()/GPIO_ResetBits()
      (#) During and just after reset, the alternate functions are not active and 
          the GPIO pins are configured in input floating mode (except SWD pins).
      (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as general-purpose 
          PF0 and PF1, respectively, when the HSE oscillator is off. The HSE has 
          priority over the GPIO function.
    @endverbatim
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
#include "pt32f0xx_gpio.h"

/** @addtogroup PT32F0xx_StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup GPIO_Private_Functions 
  * @{
  */

/** @defgroup GPIO_Group1 Initialization and Configuration
 *  @brief   Initialization and Configuration
 *
@verbatim
 ===============================================================================
                    ##### Initialization and Configuration #####
 ===============================================================================

@endverbatim
  * @{
  */
	
/**
  * @brief  Initializes the CMSDK_Px peripheral according to the specified 
  *         parameters in the GPIO_InitStruct.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.  
	          @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
	          @param  GPIO_Pin: Select GPIO pin.
						      @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15
						@param   GPIO_Mode:Select GPIO Input and Output Mode.
						      @arg   GPIO_Mode_IN
									@arg   GPIO_OType_PP
									@arg   GPIO_OType_OD
									@arg   GPIO_Mode_AN
						@param   GPIO_PuPd:Select the drop-down and pull-down of GPIO.
						      @arg   GPIO_PuPd_NOPULL
                  @arg   GPIO_PuPd_UP	
                  @arg   GPIO_PuPd_DOWN									
  * @retval None
  */
void GPIO_Init(CMSDK_GPIO_TypeDef* CMSDK_Px, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentpin = 0x00;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /*-------------------------- Configure the port pins -----------------------*/
  /*-- GPIO Mode Configuration --*/

    /* Get the port pins position */
  currentpin = GPIO_InitStruct->GPIO_Pin;
  if (((GPIO_InitStruct->GPIO_Mode) == GPIO_OType_PP) || ((GPIO_InitStruct->GPIO_Mode) == GPIO_OType_OD))
	{
    /* Output mode configuration */
		CMSDK_Px->OUTENABLESET = currentpin;
		CMSDK_Px->ANACLR = currentpin;				
		if((GPIO_InitStruct->GPIO_Mode) == GPIO_OType_OD)
		{
     CMSDK_Px->ODRSET = currentpin;		
		}
		else
		{
     CMSDK_Px->ODRCLR = currentpin;			
		}
	}
  else if ((GPIO_InitStruct->GPIO_Mode) == GPIO_Mode_AN)
	{
		CMSDK_Px->OUTENABLECLR = currentpin;
		CMSDK_Px->ANASET = currentpin;		
	}
	else
	{
	  CMSDK_Px->OUTENABLECLR = currentpin;
	  CMSDK_Px->ANACLR = currentpin;					
    switch(((uint32_t)GPIO_InitStruct->GPIO_PuPd))
	  {
		 case GPIO_PuPd_NOPULL :
      CMSDK_Px->PULLDOWNCLR = currentpin;		
      CMSDK_Px->PULLUPCLR = currentpin;	
      break;				
		 case GPIO_PuPd_UP :
		  CMSDK_Px->PULLUPSET = currentpin;		
      CMSDK_Px->PULLDOWNCLR = currentpin;
      break;				
	   case GPIO_PuPd_DOWN :
		  CMSDK_Px->PULLDOWNSET = currentpin;		
      CMSDK_Px->PULLUPCLR = currentpin;		
		  break;	 	 
	  }	
	}
}
/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  CMSDK_Px:where x can be (A, B, or F) to select the GPIO peripheral.  
	*          @arg CMSDK_PA
  *          @arg CMSDK_PB
  *          @arg CMSDK_PF
  * @param  GPIO_Pin£ºspecifies the port bit to read.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15        
  *  @note   This parameter can be GPIO_Pin_x where x can be:
  *          For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF 
  *  @param  NewState: new state of the specified  analog.
  *         This parameter can be: ENABLE or DISABLE.
	          @arg  ENABLE
						@arg  DISABLE
  *  @retval None
  */
void GPIO_AnalogFunctionConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_Pin, FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_Pin)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    CMSDK_Px->ANASET = GPIO_Pin;
  }
  else
  {
    CMSDK_Px->ANACLR = GPIO_Pin;
  }
}
/**
  * @brief  When pins are configured for port input mode, each pin can control pull-up.
  *  @param  CMSDK_Px:where x can be (A, B, or F) to select the GPIO peripheral.  
	*          @arg CMSDK_PA
  *          @arg CMSDK_PB
  *          @arg CMSDK_PF
  *  @param  GPIO_Pin£ºspecifies the port bit to pull-up.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15     
  *  @note   This parameter can be GPIO_Pin_x where x can be:
  *          For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF 
  *  @param  NewState: new state of the  pull-up.
  *         This parameter can be: ENABLE or DISABLE.
	          @arg  ENABLE
						@arg  DISABLE
  * @retval None
  */
void GPIO_PullUpConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_Pin, FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_Pin)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    CMSDK_Px->PULLDOWNCLR = GPIO_Pin;		
		CMSDK_Px->PULLUPSET = GPIO_Pin;		
  }
  else
  {
    CMSDK_Px->PULLDOWNCLR = GPIO_Pin;		
    CMSDK_Px->PULLUPCLR = GPIO_Pin;	
  }
}

/**
  * @brief  When pins are configured for port input mode, each pin can control pull-down.
  *  @param  CMSDK_Px:where x can be (A, B, or F) to select the GPIO peripheral.  
	*          @arg CMSDK_PA
  *          @arg CMSDK_PB
  *          @arg CMSDK_PF
  * @param  GPIO_Pin£ºspecifies the port bit to pull-down.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15     
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *        For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF 
  *  @param  NewState: new state of the pull-down.
  *         This parameter can be: ENABLE or DISABLE.
		          @arg  ENABLE
						  @arg  DISABLE
  * @retval None
  */
void GPIO_PullDownConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_Pin, FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_Pin)); 
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    CMSDK_Px->PULLUPCLR = GPIO_Pin;		
		CMSDK_Px->PULLDOWNSET = GPIO_Pin;		
  }
  else
  {
    CMSDK_Px->PULLDOWNCLR = GPIO_Pin;		
    CMSDK_Px->PULLUPCLR = GPIO_Pin;	
  }
}
/** @defgroup GPIO_Group2 GPIO Read and Write
 *  @brief   GPIO Read and Write
 *
@verbatim   
 ===============================================================================
                      ##### GPIO Read and Write #####
 ===============================================================================  

@endverbatim
  * @{
  */

/**
  * @brief  Reads the specified input port pin.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @param  GPIO_Pin: specifies the port bit to read.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15     
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF  
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((CMSDK_Px->DATA & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the input data port value.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.   
  * @retval input data port value.
  */
uint16_t GPIO_ReadInputData(CMSDK_GPIO_TypeDef* CMSDK_Px)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  
  return ((uint16_t)CMSDK_Px->DATA);
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.   
  * @param  GPIO_Pin: Specifies the port bit to read.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15  
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF           
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin)
{
  uint8_t bitstatus = 0x00;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin)); 
  
  if ((CMSDK_Px->DATAOUT & GPIO_Pin) != (uint32_t)Bit_RESET)
  {
    bitstatus = (uint8_t)Bit_SET;
  }
  else
  {
    bitstatus = (uint8_t)Bit_RESET;
  }
  return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.    
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(CMSDK_GPIO_TypeDef* CMSDK_Px)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
    
  return ((uint16_t)CMSDK_Px->DATAOUT);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.  
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15  
  * For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF  
  *         
  *         
  * @retval None
  */
void GPIO_SetBits(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  CMSDK_Px->DATAOUT |= GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.  
  * @param  GPIO_Pin: specifies the port bits to be written.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15  
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF  
  *         
  *         
  * @retval None
  */
void GPIO_ResetBits(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  CMSDK_Px->DATAOUT &= ~GPIO_Pin;
}	
/**
  * @brief  Reverse the selected data port bits.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.  
  * @param  GPIO_Pin: specifies the port bits to be written.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15  
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF  
  *         
  *         
  * @retval None
  */
void GPIO_ReverseBits(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  CMSDK_Px->DATAOUT ^= GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.  
  * @param  GPIO_Pin: specifies the port bit to be cleared.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15  
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF  
  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enumeration values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin

  *         
  * @retval None
  */
void GPIO_WriteBit(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin, BitAction BitVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_BIT_ACTION(BitVal)); 
  
  if (BitVal != Bit_RESET)
  {
    CMSDK_Px->DATAOUT |= GPIO_Pin;
  }
  else
  {
    CMSDK_Px->DATAOUT &= ~GPIO_Pin;
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.  
  * @param  PortVal: specifies the value to be written to the port output data register.

  * @retval None
  */
void GPIO_Write(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t PortVal)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  
  CMSDK_Px->DATAOUT = PortVal;
}


/**
  * @}
  */

/**
  * @brief  Writes Alternate function to the specified GPIO data port.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
	*         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031. 
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
	                @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
  * @note   This parameter can be GPIO_PinSourcex where x can be (0..15) for CMSDK_PA and (0..7) for CMSDK_PB and (0..1) for CMSDK_PF      
  * @param  GPIO_AF: selects specified Alternate function.
  *          This parameter can be one of the following value:
  *            @arg GPIO_AF_0:  OSC_IN£¬OSC_OUT£¬UART0_TX£¬UART0_RX£¬SPI0_CS£¬SPI0_SCK   
  *                             SPI0_MISO£¬SPI0_MOSI£¬IR_TXD£¬MCO£¬CMP0_OUT£¬CMP1_OUT    
  *                             I2C1_SCL£¬I2C1_SDA£¬SWDIO£¬SWCLK£¬TIM0_BKIN£¬TIM0_CH1    
  *                             TIM0_CH2£¬TIM0_CH3£¬TIM0_CH4£¬BEEP                        
  *            @arg GPIO_AF_1: I2C0_SDA£¬I2C0_SCL£¬TIM0_CH1N£¬TIM0_CH2N£¬TIM0_CH3
  *                            TIM0_CH4N£¬UART1_TX£¬UART1_RX£¬TIM1_BKIN£¬TIM1_CH1
  *                            TIM1_CH2N£¬TIM1_CH3N£¬TIM1_CH1£¬TIM1_CH2£¬TIM1_CH3
  *                            TIM1_CH4£¬TIM1_CH4N£¬IR_TXD£¬SPI1_CS£¬SPI1_SCK    
  *                            SPI1_MISO£¬SPI1_MOSI£¬I2C1_SCL£¬I2C1_SDA£¬MCO         
  *            @arg GPIO_AF_2: LED-DATA_A£¬LED-DATA_B£¬LED-DATA_C£¬LED-DATA_D               
  *                            LED-DATA_E£¬LED-DATA_F£¬LED_DATA_DP£¬LED-DATA_G              
  *                            ADC_ETR£¬LED-COM0£¬LED-COM2£¬LED-COM3£¬I2C0_SCL               
  *                            I2C0_SDA£¬UART1_TX£¬UART1_RX£¬UART1_TX£¬UART1_RX              
  *                            LED-COM1                                                  
  *            @arg GPIO_AF_3: UART1_TX£¬UART1_RX£¬UART0_TX£¬UART0_RX£¬UART1_TX    
  *                            UART1_RX£¬UART0_TX£¬UART0_RX£¬UART0_TX£¬UART0_RX      
  *            @arg GPIO_AF_4: I2C1_SCL,I2C1_SDA,I2C0_SCL,I2C0_SDA
  *            @arg GPIO_AF_5: MCO
  *            @arg GPIO_AF_6: RESEVR          
  * @note   The pin should already been configured in Alternate Function mode(AF)
  *         using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
  * @note   Refer to the Alternate function mapping table in the device datasheet 
  *         for the detailed mapping of the system and peripherals'alternate 
  *         function I/O pins.
  * @retval None
  */
void GPIO_PinAFConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  uint32_t temp = 0x00;
  uint32_t temp_2 = 0x00;
	uint32_t afr_tmp[2]={ 0x00, 0x00 };

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_param(IS_GPIO_AF(GPIO_AF));

  temp = ((uint32_t)(GPIO_AF) << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  afr_tmp[GPIO_PinSource >> 0x03] &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIO_PinSource & (uint32_t)0x07) * 4));
  temp_2 = afr_tmp[GPIO_PinSource >> 0x03] | temp;
  afr_tmp[GPIO_PinSource >> 0x03] = temp_2;
	CMSDK_Px->ALTFUNCSET = afr_tmp[0];
	CMSDK_Px->ALTFUNCSET1 = afr_tmp[1];		
}


/**
  * @brief  Clears the GPIO's Alternate function.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031.  
  * @param  GPIO_Pin: specifies the port bits to be written.
                  @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
                  @arg   GPIO_Pin_15  
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For PT32F031: (0..15) for CMSDK_PA, (0..7) for CMSDK_PB,(0..1) for CMSDK_PF  
  *         
  *         
  * @retval None
  */
void GPIO_ClearPinAF(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
     
  CMSDK_Px->ALTFUNCCLR = GPIO_Pin;
}

/**
  * @}
  */

/** @defgroup GPIO_Group12 Interrupts and flags management functions
 *  @brief   Interrupts and flags management functions 
 *
@verbatim   
 ===============================================================================                                                                                         
            ##### Interrupts and flags management functions #####                                                           
 ===============================================================================                                            
    [..] This subsection provides a set of functions allowing to configure the                                              
         UART Interrupts sources, Requests and check or clear the flags or pending bits status.                                                                                     
                                                                                       
 *** Interrupt Mode ***                                                                                                     
 ======================                                                                                                     
    [..] the GPIO can be managed by 15 interrupt                                            
         sources           
         (+) Pending Bits:
             (##) GPIO_FLAG_PR0    to indicate the status of CMSDK_Px0 interrupt
             (##) GPIO_FLAG_PR1    to indicate the status of CMSDK_Px1 interrupt
             (##) GPIO_FLAG_PR2    to indicate the status of CMSDK_Px2 interrupt
             (##) GPIO_FLAG_PR3    to indicate the status of CMSDK_Px3 interrupt
             (##) GPIO_FLAG_PR4    to indicate the status of CMSDK_Px4 interrupt
             (##) GPIO_FLAG_PR5    to indicate the status of CMSDK_Px5 interrupt
             (##) GPIO_FLAG_PR6    to indicate the status of CMSDK_Px6 interrupt
             (##) GPIO_FLAG_PR7    to indicate the status of CMSDK_Px7 interrupt
             (##) GPIO_FLAG_PR8    to indicate the status of CMSDK_Px8 interrupt
             (##) GPIO_FLAG_PR9    to indicate the status of CMSDK_Px9 interrupt
             (##) GPIO_FLAG_PR10   to indicate the status of CMSDK_Px10 interrupt
             (##) GPIO_FLAG_PR11   to indicate the status of CMSDK_Px11 interrupt
             (##) GPIO_FLAG_PR12   to indicate the status of CMSDK_Px12 interrupt
             (##) GPIO_FLAG_PR13   to indicate the status of CMSDK_Px13 interrupt
             (##) GPIO_FLAG_PR14   to indicate the status of CMSDK_Px14 interrupt
             (##) GPIO_FLAG_PR15   to indicate the status of CMSDK_Px15 interrupt
             	                                    	          	                                                                                                                   
         (+) Interrupt Source:                                                                                              
             (##) GPIO_IT_ITE0   specifies the interrupt source for CMSDK_Px0 interrupt   
             (##) GPIO_IT_ITE1   specifies the interrupt source for CMSDK_Px1 interrupt  
             (##) GPIO_IT_ITE2   specifies the interrupt source for CMSDK_Px2 interrupt  
             (##) GPIO_IT_ITE3   specifies the interrupt source for CMSDK_Px3 interrupt  
             (##) GPIO_IT_ITE4   specifies the interrupt source for CMSDK_Px4 interrupt  
             (##) GPIO_IT_ITE5   specifies the interrupt source for CMSDK_Px5 interrupt  
             (##) GPIO_IT_ITE6   specifies the interrupt source for CMSDK_Px6.interrupt  
             (##) GPIO_IT_ITE7   specifies the interrupt source for CMSDK_Px7 interrupt  
             (##) GPIO_IT_ITE8   specifies the interrupt source for CMSDK_Px8 interrupt  
             (##) GPIO_IT_ITE9   specifies the interrupt source for CMSDK_Px9 interrupt  
             (##) GPIO_IT_ITE10  specifies the interrupt source for CMSDK_Px10 interrupt 
             (##) GPIO_IT_ITE11  specifies the interrupt source for CMSDK_Px11 interrupt 
             (##) GPIO_IT_ITE12 specifies the interrupt source for CMSDK_Px12 interrupt 
             (##) GPIO_IT_ITE13 specifies the interrupt source for CMSDK_Px13 interrupt 
             (##) GPIO_IT_ITE14 specifies the interrupt source for CMSDK_Px14 interrupt 
             (##) GPIO_IT_ITE15 specifies the interrupt source for CMSDK_Px15 interrupt                                                                               
    [..] In this Mode it is advised to use the following functions:                                                         
         (+) GPIO_ITConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_IT, FunctionalState NewState)                           
         (+) FlagStatus GPIO_GetFlagStatus(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_FLAG).                                  
         (+) void UART_ClearFlag(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_FLAG).

@endverbatim
  * @{
  */

/**
  * @brief  Enables or disables the specified GPIO interrupts.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
	* @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031. 
  * @param  GPIO_IT: specifies the USART interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
	*            @arg GPIO_IT_ITE0 
  *            @arg GPIO_IT_ITE1 
  *            @arg GPIO_IT_ITE2 
  *            @arg GPIO_IT_ITE3 
  *            @arg GPIO_IT_ITE4 
  *            @arg GPIO_IT_ITE5 
  *            @arg GPIO_IT_ITE6 
  *            @arg GPIO_IT_ITE7 
  *            @arg GPIO_IT_ITE8
  *            @arg GPIO_IT_ITE9 
  *            @arg GPIO_IT_ITE10 
  *            @arg GPIO_IT_ITE11
  *            @arg GPIO_IT_ITE12
  *            @arg GPIO_IT_ITE13 
  *            @arg GPIO_IT_ITE14
  *            @arg GPIO_IT_ITE15     
  * @param  NewState: new state of the specified GPIO interrupts.
  *          This parameter can be: ENABLE or DISABLE.
	             @arg ENABLE
							 @arg DISABLE
  * @retval None 
  */
void GPIO_ITConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_IT, FunctionalState NewState)
{

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_CONFIG_IT(GPIO_IT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    CMSDK_Px->INTENSET = GPIO_IT;
  }
  else
  {
    CMSDK_Px->INTENCLR = GPIO_IT;
  }
}


/**
  * @brief  Specifies the type of interrupt trigger for the pin
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
	* @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031. 
  * @param  GPIO_Pin: specifies the port bit to trigger the interrupt.
	                @arg   GPIO_Pin_0
                  @arg   GPIO_Pin_1
                  @arg   GPIO_Pin_2
                  @arg   GPIO_Pin_3
                  @arg   GPIO_Pin_4
                  @arg   GPIO_Pin_5
                  @arg   GPIO_Pin_6
                  @arg   GPIO_Pin_7
                  @arg   GPIO_Pin_8
                  @arg   GPIO_Pin_9
                  @arg   GPIO_Pin_10
                  @arg   GPIO_Pin_11
                  @arg   GPIO_Pin_12
                  @arg   GPIO_Pin_13
                  @arg   GPIO_Pin_14
  * @note   This parameter can be GPIO_Pin_x where x can be:
  * @param  Trigger_Type: Specifies the type of trigge.
  *         @arg GPIOTI_Trigger_Rising
  *         @arg GPIOTI_Trigger_Falling
  *         @arg GPIOTI_Trigger_Rising_Falling 
  *         @arg GPIOTI_Trigger_High_Level
  *         @arg GPIOTI_Trigger_Low_Level
  *
  * @retval None
  */
void GPIO_TriTypeConfig(CMSDK_GPIO_TypeDef* CMSDK_Px, uint16_t GPIO_Pin, uint32_t Trigger_Type)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIOTI_TRIGGER(Trigger_Type)); 
  
	switch( Trigger_Type )
	{
		case GPIOTI_Trigger_Rising :
      CMSDK_Px->INTTYPESET = GPIO_Pin;
      CMSDK_Px->INTPOLSET =  GPIO_Pin;
		  CMSDK_Px->INTTYPECLR1 = GPIO_Pin;
      break;				
		case GPIOTI_Trigger_Falling :
      CMSDK_Px->INTTYPESET = GPIO_Pin;
      CMSDK_Px->INTPOLCLR =  GPIO_Pin;
		  CMSDK_Px->INTTYPECLR1 = GPIO_Pin;		
      break;				
		case GPIOTI_Trigger_Rising_Falling :
			CMSDK_Px->INTTYPESET1 = GPIO_Pin;
			break;	
		case GPIOTI_Trigger_High_Level :
      CMSDK_Px->INTTYPECLR = GPIO_Pin;
      CMSDK_Px->INTPOLSET =  GPIO_Pin;
			CMSDK_Px->INTTYPECLR1 = GPIO_Pin;
			break;		
		case GPIOTI_Trigger_Low_Level :
      CMSDK_Px->INTTYPECLR = GPIO_Pin;
      CMSDK_Px->INTPOLCLR =  GPIO_Pin;
		  CMSDK_Px->INTTYPECLR1 = GPIO_Pin;		
			break;				
	}
}

/**
  * @brief  Checks whether the specified GPIO interrupt flag is set or not.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *         @arg CMSDK_PA
            @arg CMSDK_PB
            @arg CMSDK_PF
  * @note   CMSDK_PA,CMSDK_PB,CMSDK_PF is available only for PT32F031. 
  * @param  GPIO_IT_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg GPIO_FLAG_PR0    Port interrupt pending bit set, bit 0 
  *            @arg GPIO_FLAG_PR1    Port interrupt pending bit set, bit 1 
  *            @arg GPIO_FLAG_PR2    Port interrupt pending bit set, bit 2 
  *            @arg GPIO_FLAG_PR3    Port interrupt pending bit set, bit 3 
  *            @arg GPIO_FLAG_PR4    Port interrupt pending bit set, bit 4 
  *            @arg GPIO_FLAG_PR5    Port interrupt pending bit set, bit 5 
  *            @arg GPIO_FLAG_PR6    Port interrupt pending bit set, bit 6 
  *            @arg GPIO_FLAG_PR7    Port interrupt pending bit set, bit 7 
  *            @arg GPIO_FLAG_PR8    Port interrupt pending bit set, bit 8 
  *            @arg GPIO_FLAG_PR9    Port interrupt pending bit set, bit 9 
  *            @arg GPIO_FLAG_PR10   Port interrupt pending bit set, bit 10
  *            @arg GPIO_FLAG_PR11   Port interrupt pending bit set, bit 11
  *            @arg GPIO_FLAG_PR12   Port interrupt pending bit set, bit 12
  *            @arg GPIO_FLAG_PR13   Port interrupt pending bit set, bit 13
  *            @arg GPIO_FLAG_PR14   Port interrupt pending bit set, bit 14
  *            @arg GPIO_FLAG_PR15   Port interrupt pending bit set, bit 15	
  * @retval The new state of GPIO_IT_FLAG (SET or RESET).
  */
FlagStatus GPIO_GetFlagStatus(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_IT_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_GET_FLAG(GPIO_IT_FLAG));
  
  if ((CMSDK_Px->INTSTATUS & GPIO_IT_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the GPIO's pending flags.
  * @param  CMSDK_Px: where x can be (A, B,or F) to select the GPIO peripheral.
  *             @arg CMSDK_PA
  *             @arg CMSDK_PB
  *             @arg CMSDK_PF
  * @param  GPIO_IT_FLAG: specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg GPIO_FLAG_PR0    Port interrupt pending bit set, bit 0 
  *            @arg GPIO_FLAG_PR1    Port interrupt pending bit set, bit 1 
  *            @arg GPIO_FLAG_PR2    Port interrupt pending bit set, bit 2 
  *            @arg GPIO_FLAG_PR3    Port interrupt pending bit set, bit 3 
  *            @arg GPIO_FLAG_PR4    Port interrupt pending bit set, bit 4 
  *            @arg GPIO_FLAG_PR5    Port interrupt pending bit set, bit 5 
  *            @arg GPIO_FLAG_PR6    Port interrupt pending bit set, bit 6 
  *            @arg GPIO_FLAG_PR7    Port interrupt pending bit set, bit 7 
  *            @arg GPIO_FLAG_PR8    Port interrupt pending bit set, bit 8 
  *            @arg GPIO_FLAG_PR9    Port interrupt pending bit set, bit 9 
  *            @arg GPIO_FLAG_PR10   Port interrupt pending bit set, bit 10
  *            @arg GPIO_FLAG_PR11   Port interrupt pending bit set, bit 11
  *            @arg GPIO_FLAG_PR12   Port interrupt pending bit set, bit 12
  *            @arg GPIO_FLAG_PR13   Port interrupt pending bit set, bit 13
  *            @arg GPIO_FLAG_PR14   Port interrupt pending bit set, bit 14
  *            @arg GPIO_FLAG_PR15   Port interrupt pending bit set, bit 15	
  * @retval None 	
  */
void GPIO_ClearFlag(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_IT_FLAG)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_CLEAR_FLAG(GPIO_IT_FLAG));
     
  CMSDK_Px->INTCLEAR = GPIO_IT_FLAG;
}

/**
  * @brief  Checks whether the specified interrupt has occurred or not.
  * @param  CMSDK_Px: where x can be (A, B,or F) to select the GPIO peripheral.
               @arg CMSDK_PA
               @arg CMSDK_PB
               @arg CMSDK_PF
  *  @param GPIO_IT_FLAG: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg GPIO_IT_ITE0 
  *            @arg GPIO_IT_ITE1 
  *            @arg GPIO_IT_ITE2 
  *            @arg GPIO_IT_ITE3 
  *            @arg GPIO_IT_ITE4 
  *            @arg GPIO_IT_ITE5 
  *            @arg GPIO_IT_ITE6 
  *            @arg GPIO_IT_ITE7 
  *            @arg GPIO_IT_ITE8
  *            @arg GPIO_IT_ITE9 
  *            @arg GPIO_IT_ITE10 
  *            @arg GPIO_IT_ITE11
  *            @arg GPIO_IT_ITE12
  *            @arg GPIO_IT_ITE13 
  *            @arg GPIO_IT_ITE14
  *            @arg GPIO_IT_ITE15 	
  * @retval The new state of GPIO_IT (SET or RESET).
  */
ITStatus GPIO_GetITStatus(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_GET_IT(GPIO_IT));

  /* Get the GPIO_IT enable bit status */
  enablestatus = (uint32_t)(CMSDK_Px->INTENSET & GPIO_IT); 

  /* Check the status of the specified GPIO interrupt */
  if (((uint32_t)(CMSDK_Px->INTSTATUS & GPIO_IT) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    /* GPIO_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* GPIO_IT is reset */
    bitstatus = RESET;
  }
  /* Return the GPIO_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the GPIO interrupt pending bits.
  * @param  CMSDK_Px: where x can be (A, B or F) to select the GPIO peripheral.
  *             @arg CMSDK_PA
  *             @arg CMSDK_PB
  *             @arg CMSDK_PF
  * @param  GPIO_IT: specifies the interrupt pending bit to clear.
  *            @arg GPIO_IT_ITE0 
  *            @arg GPIO_IT_ITE1 
  *            @arg GPIO_IT_ITE2 
  *            @arg GPIO_IT_ITE3 
  *            @arg GPIO_IT_ITE4 
  *            @arg GPIO_IT_ITE5 
  *            @arg GPIO_IT_ITE6 
  *            @arg GPIO_IT_ITE7 
  *            @arg GPIO_IT_ITE8
  *            @arg GPIO_IT_ITE9 
  *            @arg GPIO_IT_ITE10 
  *            @arg GPIO_IT_ITE11
  *            @arg GPIO_IT_ITE12
  *            @arg GPIO_IT_ITE13 
  *            @arg GPIO_IT_ITE14
  *            @arg GPIO_IT_ITE15 	
  * @retval None
  */
void GPIO_ClearITPendingBit(CMSDK_GPIO_TypeDef* CMSDK_Px, uint32_t GPIO_IT)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(CMSDK_Px));
  assert_param(IS_GPIO_CLEAR_IT(GPIO_IT));

  /* Clear the selected GPIO interrupt pending bits */
  CMSDK_Px->INTCLEAR = (uint32_t)GPIO_IT; 
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
