#include "ADC.h"


/**************************************************************************************
* FunctionName :InitADC()
* Description : ADC Initialization
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void InitADC()
{
	/*����PA0����ΪADCͨ��*/
	GPIO_AnalogFunctionConfig(M_Vcom_PORT,M_Vcom_PIN, ENABLE);
	
	/*ADC��������*/
	ADC_InitTypeDef  ADC_InitStruct;
	
	//����ת��
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	//�����Ҷ���
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	//�������ת��
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Software;
	//���ٲ���ģʽ
	ADC_InitStruct.ADC_HighSpeedSampMode = DISABLE;

	ADC_Init(ADC, &ADC_InitStruct);
	

	/*����ADC�Ĺ���ʱ��Ϊϵͳʱ�ӵ��ķ�Ƶ*/
	ADC_ClockModeConfig(ADC, ADC_ClockMode_SynClkDiv8);
	
	/*����ADCת��ͨ��*/
	ADC_ChannelConfig(ADC, M_Vcom_Channel);
	
	
	/*����ADC���蹦��*/
	ADC_Cmd(ADC, ENABLE);
	/*�ȴ�ADC�����������*/
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
	
	/*����ADC���蹦��*/
	ADC_Cmd(ADC, ENABLE);
	/*�ȴ�ADC�����������*/
	while(!ADC_GetFlagStatus(ADC,ADC_FLAG_ADRDY));	
	/*����ADCת��*/
	ADC_StartOfConversion(ADC);
	/*�ȴ�ADCһ��ת������*/
	while(!ADC_GetFlagStatus(ADC,ADC_FLAG_EOC));
	/*���ת����ɱ�ʶλ*/	
	ADC_ClearFlag(ADC,ADC_FLAG_EOC);
	/*�ر�ADC���蹦��*/
	ADC_Cmd(ADC, DISABLE);
	
	//uSDelay(10);	
	nMin=(unsigned char)1024,nMax=0;
	for(nI = 0;nI < 5;nI++)
	{
		/*����ADC���蹦��*/
		ADC_Cmd(ADC, ENABLE);
		/*�ȴ�ADC�����������*/
		while(!ADC_GetFlagStatus(ADC,ADC_FLAG_ADRDY));	
		/*����ADCת��*/
		ADC_StartOfConversion(ADC);
		/*�ȴ�ADCһ��ת������*/
		while(!ADC_GetFlagStatus(ADC,ADC_FLAG_EOC));
		/*���ת����ɱ�ʶλ*/	
		ADC_ClearFlag(ADC,ADC_FLAG_EOC);
		/*��ȡADCת�����*/
		nSmpVal[nI]=ADC_GetConversionValue(ADC);
		/*�ر�ADC���蹦��*/
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
