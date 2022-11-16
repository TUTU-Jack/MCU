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
	
	/*GPIO复用为SPI模式*/
	GPIO_PinAFConfig(M_SPI_MOSI_PORT, M_SPI_MOSI_PIN, GPIO_AF_1);
	GPIO_PinAFConfig(M_SPI_MISO_PORT, M_SPI_MISO_PIN, GPIO_AF_1);
	GPIO_PinAFConfig(M_SPI_CLK_PORT, M_SPI_CLK_PIN, GPIO_AF_1);
	GPIO_PinAFConfig(M_SPI_SS_PORT, M_SPI_SS_PIN, GPIO_AF_1);
	
	/*SPI功能配置*/
	SPI_InitTypeDef  SPI_InitStructure;
	
	//SPI从机模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	//数据长度为16位
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
	//时钟空闲IDLE为高电平
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	//在时钟信号SCK的第一个跳变沿采样
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	//由硬件选择从机引脚
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	
	SPI_InitStructure.SPI_BaudRatePostPrescaler = 12;
	SPI_InitStructure.SPI_BaudRatePrescaler = 0;
	
	SPI_Init(SPI1,&SPI_InitStructure);
	
	/*SPI中断配置*/
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	//中断通道源
	NVIC_InitStruct.NVIC_IRQChannel = SPI1_IRQn;
	//中断优先级
	NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
	//中断使能
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStruct);
	
	//SPI中断使能
	//SPI 接收FIFO非空超时中断
	SPI_ITConfig(SPI1, SPI_IT_RFNEOT, ENABLE);
	//SPI 接收FIFO半满中断
	SPI_ITConfig(SPI1, SPI_IT_RFHF, ENABLE);
	
	//使能SPI
	SPI_Cmd(SPI1, ENABLE);
	
	while((SPI1->SR & SPI_FLAG_TFE) == RESET);
	SPI1->DR = 0x1212;
	
}





