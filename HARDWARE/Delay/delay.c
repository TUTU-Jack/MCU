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
		/* ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1*/	
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	/* �ر�SysTick��ʱ��*/	
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}