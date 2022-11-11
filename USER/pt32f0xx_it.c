
/* Includes ------------------------------------------------------------------*/
#include "pt32f0xx_it.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TaskRemarks();
}

/******************************************************************************/
/*                 PT32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_pt32f0xx.s).                                            */
/******************************************************************************/
/**
  * @brief  This function handles WWDG interrupt.
  * @param  None
  * @retval None
  */
void SWDG_Handler(void)
{
}

/**
  * @brief  This function handles CLK_FAIL interrupt.
  * @param  None
  * @retval None
  */
void CLK_FAIL_Handler(void)
{
}

/**
  * @brief  This function handles FLASH interrupt.
  * @param  None
  * @retval None
  */
void FLASH_Handler(void)
{
}

/**
  * @brief  This function handles PA interrupt.
  * @param  None
  * @retval None
  */
void PA_Handler(void)
{
	FlagStatus status = GPIO_GetFlagStatus(CMSDK_PA, GPIO_FLAG_PR11);
	if(status)
	{
		GPIO_ClearFlag(CMSDK_PA, GPIO_FLAG_PR11);
		//定时器使能
		PWM_Cmd(PWM1,ENABLE);
		TaskDisplayLED_R();
	}
}

/**
  * @brief  This function handles PB interrupt.
  * @param  None
  * @retval None
  */
void PB_Handler(void)
{
}

/**
  * @brief  This function handles PF interrupt.
  * @param  None
  * @retval None
  */
void PF_Handler(void)
{
}

/**
  * @brief  This function handles Comparator0 interrupt.
  * @param  None
  * @retval None
  */
void Comparator0_Handler(void)
{
}

/**
  * @brief  This function handles Comparator1 interrupt.
  * @param  None
  * @retval None
  */
void Comparator1_Handler(void)
{
}

/**
  * @brief  This function handles ADC interrupt.
  * @param  None
  * @retval None
  */
void ADC_Handler(void)
{
}


/**
  * @brief  This function handles SPI0 interrupt.
  * @param  None
  * @retval None
  */
void SPI0_Handler(void)
{
}

/**
  * @brief  This function handles SPI1 interrupt.
  * @param  None
  * @retval None
  */
void SPI1_Handler(void)
{
}

/**
  * @brief  This function handles UART0 interrupt.
  * @param  None
  * @retval None
  */
void UART0_Handler(void)
{
	
}

/**
  * @brief  This function handles UART1 interrupt.
  * @param  None
  * @retval None
  */
void UART1_Handler(void)
{
}

/**
  * @brief  This function handles I2C0 interrupt.
  * @param  None
  * @retval None
  */
void I2C0_Handler(void)
{
}

/**
  * @brief  This function handles I2C1 interrupt.
  * @param  None
  * @retval None
  */
void I2C1_Handler(void)
{
}

/**
  * @brief  This function handles LED interrupt.
  * @param  None
  * @retval None
  */
void LED_Handler(void)
{
}

/**
  * @brief  This function handles TIMER0 interrupt.
  * @param  None
  * @retval None
  */
void TIMER0_Handler(void)
{
}

/**
  * @brief  This function handles TIMER1 interrupt.
  * @param  None
  * @retval None
  */
uint32_t IntOverflowCount = 0;
void TIMER1_Handler(void)
{
	//计数值溢出触发中断
	if(PWM_GetFlagStatus(PWM1,PWM_FLAG_MR0))
	{
		PWM_ClearFlag(PWM1,PWM_FLAG_MR0);
		IntOverflowCount++;
	}
	//捕获上升沿触发中断
	if(PWM_GetFlagStatus(PWM1,PWM_FLAG_CAP4_RE))
	{
		//清除中断标志位（很重要，不然会一直产生中断）
		PWM_ClearFlag(PWM1, PWM_FLAG_CAP4_RE);
		uint16_t capture_counter = PWM_GetCaptureCounter(PWM1,PWM_CH_4);
		//捕获成功，关闭中断
		PWM_Cmd(PWM1, DISABLE);
		
		uint16_t KeyPresstime = (IntOverflowCount*0.1 + (capture_counter+1)*0.000001);
		IntOverflowCount = 0;
		
		UART_SendData(UART0,KeyPresstime);
	}
	
}

/**
  * @brief  This function handles TIMER2 interrupt.
  * @param  None
  * @retval None
  */
void TIMER2_Handler(void)
{
}

/**
  * @brief  This function handles TIMER3 interrupt.
  * @param  None
  * @retval None
  */
void TIMER3_Handler(void)
{
	uint32_t status = TIM_GetFlagStatus(TIM3,TIM_FLAG_MR0);
	uint8_t string[] = "timer";
	
	if(status)
	{
		TIM_ClearFlag(TIM3,TIM_FLAG_MR0);
		
		count++;
		if(count > 999)
		{
			count = 0;
			TaskDisplayLED_R();
			UART_StringSend(UART0,string);
		}
	}
}

/**
  * @brief  This function handles TIMER4 interrupt.
  * @param  None
  * @retval None
  */
void TIMER4_Handler(void)
{
}
/**
  * @brief  This function handles PVD interrupt.
  * @param  None
  * @retval None
  */
void PVD_Handler(void)
{
}
/**
  * @brief  This function handles LVD interrupt.
  * @param  None
  * @retval None
  */
void LVD_Handler(void)
{
}
/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
