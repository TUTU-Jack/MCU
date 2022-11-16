#include "SPI.h"

#include "spi.h"


/**************************************************************************************
* FunctionName :InitSPI()
* Description : SPI Initialization
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void InitSPI()
{
	
	/*GPIO����ΪSPIģʽ*/
	GPIO_PinAFConfig(M_SPI_MOSI_PORT, M_SPI_MOSI_PIN, GPIO_AF_1);
	GPIO_PinAFConfig(M_SPI_MISO_PORT, M_SPI_MISO_PIN, GPIO_AF_1);
	GPIO_PinAFConfig(M_SPI_CLK_PORT, M_SPI_CLK_PIN, GPIO_AF_1);
	GPIO_PinAFConfig(M_SPI_SS_PORT, M_SPI_SS_PIN, GPIO_AF_1);
	
	/*SPI��������*/
	SPI_InitTypeDef  SPI_InitStructure;
	
	//SPI�ӻ�ģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	//���ݳ���Ϊ16λ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	//ʱ�ӿ���IDLEΪ�ߵ�ƽ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	//��ʱ���ź�SCK�ĵ�һ�������ز���
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	//��Ӳ��ѡ��ӻ�����
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	
	SPI_InitStructure.SPI_BaudRatePostPrescaler = 12;
	SPI_InitStructure.SPI_BaudRatePrescaler = 0;
	
	SPI_Init(SPI1,&SPI_InitStructure);
	
	/*SPI�ж�����*/
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	//�ж�ͨ��Դ
	NVIC_InitStruct.NVIC_IRQChannel = SPI1_IRQn;
	//�ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	//�ж�ʹ��
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//SPI�ж�ʹ��
	//SPI ����FIFO�ǿճ�ʱ�ж�
	SPI_ITConfig(SPI1, SPI_IT_RFNEOT, ENABLE);
	//SPI ����FIFO�����ж�
	SPI_ITConfig(SPI1, SPI_IT_RFHF, ENABLE);
	
	//ʹ��SPI
	SPI_Cmd(SPI1, ENABLE);
	
	while((SPI1->SR & SPI_FLAG_TFE) == RESET);
	SPI1->DR = 0x1212;
	
}





