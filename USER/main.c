#include "main.h"


int main(void)
{
	LED_Init();
	Systick_Init();
	
	//Timer_Init();
	
	//Key_Init();
	//Capture_Init();
	
	//Pwm_Init();
	
	Uart_Init();
	
	
	while(1)
	{
		
		TaskProcess();
		
	}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************(C) COPYRIGHT PENGPAI Microelectronics*****END OF FILE****/
