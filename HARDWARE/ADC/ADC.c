#include "ADC.h"


/**************************************************************************************
* FunctionName :InitADC()
* Description : ADC Initialization
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void InitADC()
{
	/*配置PA0复用为ADC通道*/
	GPIO_AnalogFunctionConfig(M_Vcom_PORT,M_Vcom_PIN, ENABLE);
	
	/*ADC功能配置*/
	ADC_InitTypeDef  ADC_InitStruct;
	
	//单次转换
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	//数据右对齐
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	//软件触发转换
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Software;
	//高速采样模式
	ADC_InitStruct.ADC_HighSpeedSampMode = DISABLE;

	ADC_Init(ADC, &ADC_InitStruct);
	

	/*配置ADC的工作时钟为系统时钟的四分频*/
	ADC_ClockModeConfig(ADC, ADC_ClockMode_SynClkDiv8);
	
	/*配置ADC转换通道*/
	ADC_ChannelConfig(ADC, M_Vcom_Channel);
	
	
	/*启动ADC外设功能*/
	ADC_Cmd(ADC, ENABLE);
	/*等待ADC外设启动完成*/
	while(!ADC_GetFlagStatus(ADC,ADC_FLAG_ADRDY));	
}


/**************************************************************************************
* FunctionName :GetSampleValue(USHORT nSELECTID)
* Description : Sampling Fuction
* EntryParameter : nSELECTID
* ReturnValue : None
**************************************************************************************/
USHORT nSmpVal[5],nI,nMin,nMax,nMinIndex,nMaxIndex,nSampleSum,nValidCnt;
USHORT GetSampleValue(USHORT nSELECTID)
{
	//M_S0
	if(nSELECTID & 0x01)
		GPIO_SetBits(M_S0_PORT, M_S0_PIN);   
	else
		GPIO_ResetBits(M_S0_PORT, M_S0_PIN);
   
	//M_S1
 	if(nSELECTID & 0x02)		   
		GPIO_SetBits(M_S1_PORT, M_S1_PIN);     
 	else
		GPIO_ResetBits(M_S1_PORT, M_S1_PIN);  
   
	//M_S2
 	if(nSELECTID & 0x04)		
		GPIO_SetBits(M_S2_PORT, M_S2_PIN);  
  	else
		GPIO_ResetBits(M_S2_PORT, M_S2_PIN); 
	
	//M_S3
	if(nSELECTID & 0x08)		
		GPIO_SetBits(M_S3_PORT, M_S3_PIN);  
  	else
		GPIO_ResetBits(M_S3_PORT, M_S3_PIN); 
	
	//uSDelay(10);
	
	/*启动ADC外设功能*/
	ADC_Cmd(ADC, ENABLE);
	/*等待ADC外设启动完成*/
	while(!ADC_GetFlagStatus(ADC,ADC_FLAG_ADRDY));	
	/*启动ADC转换*/
	ADC_StartOfConversion(ADC);
	/*等待ADC一次转换结束*/
	while(!ADC_GetFlagStatus(ADC,ADC_FLAG_EOC));
	/*清除转换完成标识位*/	
	ADC_ClearFlag(ADC,ADC_FLAG_EOC);
	/*关闭ADC外设功能*/
	ADC_Cmd(ADC, DISABLE);
	
	//uSDelay(10);	
	nMin=(unsigned char)1024,nMax=0;
	for(nI = 0;nI < 5;nI++)
	{
		/*启动ADC外设功能*/
		ADC_Cmd(ADC, ENABLE);
		/*等待ADC外设启动完成*/
		while(!ADC_GetFlagStatus(ADC,ADC_FLAG_ADRDY));	
		/*启动ADC转换*/
		ADC_StartOfConversion(ADC);
		/*等待ADC一次转换结束*/
		while(!ADC_GetFlagStatus(ADC,ADC_FLAG_EOC));
		/*清除转换完成标识位*/	
		ADC_ClearFlag(ADC,ADC_FLAG_EOC);
		/*获取ADC转换结果*/
		nSmpVal[nI]=ADC_GetConversionValue(ADC);
		/*关闭ADC外设功能*/
		ADC_Cmd(ADC, DISABLE);
		
		//uSDelay(5);
		
		if(nSmpVal[nI] > nMax)
		{
			nMaxIndex = nI;
			nMax = nSmpVal[nI];
		}
		
		if(nSmpVal[nI] < nMin)
        {
            nMinIndex=nI;
            nMin=nSmpVal[nI];
        }
	}
	
    nSampleSum=0;nValidCnt=0;
    for(nI=0;nI<5;nI++)
    {
        if((nI!=nMinIndex)&&(nI!=nMaxIndex))
        {
            nSampleSum+=nSmpVal[nI];
            nValidCnt++;
        }
    } 
	if(nValidCnt>0)
    	return nSampleSum/nValidCnt;
    return 0;
}
