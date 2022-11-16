#include "delay.h"

/**************************************************************************************
* FunctionName :uSDelay( __IO uint32_t us)
* Description : Us Delay Function
* EntryParameter : us
* ReturnValue : None
**************************************************************************************/
void uSDelay( __IO uint32_t us)
{
	uint32_t i;
	SysTick->LOAD  = (uint32_t)(SystemCoreClock/1000000 - 1UL);
	SysTick->VAL   = 0UL;
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
	
	for(i=0;i<us;i++)
	{
		/* 当计数器的值减小到0的时候，CRTL寄存器的位16会置1*/	
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	/* 关闭SysTick定时器*/	
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}