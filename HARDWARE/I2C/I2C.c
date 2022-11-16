#include "I2C.h"

/**************************************************************************************
* FunctionName :InitI2C()
* Description : I2C Initialization
* EntryParameter : None
* ReturnValue : None
**************************************************************************************/
void InitI2C()
{
	 /*GPIO复用I2C*/
	GPIO_PinAFConfig(M_SDA_PORT, M_SDA_PIN, GPIO_AF_4);
	GPIO_PinAFConfig(M_SCL_PORT, M_SCL_PIN, GPIO_AF_4);
	GPIO_PullUpConfig(M_SDA_PORT, M_SDA_PIN, ENABLE);
	GPIO_PullUpConfig(M_SCL_PORT, M_SCL_PIN, ENABLE);
	
	/*I2C功能配置*/
	I2C_InitTypeDef	I2C_InitStructure; 

	
	I2C_InitStructure.I2C_OwnAddress =0; 
	I2C_InitStructure.I2C_Ack = ENABLE ;
	I2C_InitStructure.I2C_BroadCast = DISABLE;
	I2C_InitStructure.I2C_SCLK_DIV = I2C_SCLK_DIVX60;  
	
	I2C_Init(I2C1, &I2C_InitStructure);
  
	/* 使能 I2C */
	I2C_Cmd(I2C1, ENABLE);   
}

/**************************************************************************************
* FunctionName :WriteTMP275(uchar Slaveaddr,uchar Pointeraddr,uchar *DataPtr)
* Description : Write TMP275 Register
* EntryParameter : SlaveAddr、PointerAddr、DataPtr
* ReturnValue : Error Information
**************************************************************************************/
char WriteTMP275(uchar SlaveAddr,uchar PointerAddr,uchar *DataPtr) 
{
	/* Send STRAT condition */
	I2C_GenerateSTART(I2C1, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主机发送起始位完成*/
	while(I2C_GetStatus(I2C1) !=0x8)  
	{
		if((I2CTimeout--) == 0) return 1;
	} 
	
	/* Send EEPROM address for write */
	SlaveAddr = 0x90 | (SlaveAddr & 0x0e);
	I2C_SendData(I2C1,SlaveAddr);  
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主机发送起始位完成*/
	while(I2C_GetStatus(I2C1) !=0x18)  
	{
		if((I2CTimeout--) == 0) return 2;
	} 
	
	/* Send the EEPROM's internal address to write to */
	I2C_SendData(I2C1,PointerAddr);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*主模式发送数据字节完成并受到ACK相应 */
	while(I2C_GetStatus(I2C1)!=0x28)
	{
		if((I2CTimeout--) == 0) return 3;
	} 
	
	/* Send the byte to be written */
	I2C_SendData(I2C1,*DataPtr); 
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主模式发送数据字节完成并受到ACK相应 */
	while(I2C_GetStatus(I2C1)!=0x28)
	{
		if((I2CTimeout--) == 0) return 4;
	} 
  
	/* Send STOP condition */
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return 0;
}


/**************************************************************************************
* FunctionName :ReadTMP275(uchar Slaveaddr,uchar Pointeraddr,uchar *DataPtr,uchar Nbyte)
* Description : Read TMP275 Register
* EntryParameter : SlaveAddr、PointerAddr、DataPtr、Nbyte
* ReturnValue : Error Information
**************************************************************************************/
char ReadTMP275(uchar SlaveAddr,uchar PointerAddr,uchar *DataPtr,uchar Nbyte)
{
	
	/* Send STRAT condition */
	I2C_GenerateSTART(I2C1, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主机发送起始位完成*/
	while(I2C_GetStatus(I2C1) !=0x8)  
	{
		if((I2CTimeout--) == 0) return 5;
	} 
	
	/* Send EEPROM address for write */
	SlaveAddr = 0x90 | (SlaveAddr & 0x0e);
	I2C_SendData(I2C1,SlaveAddr);  
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主机发送起始位完成*/
	while(I2C_GetStatus(I2C1) !=0x18)  
	{
		if((I2CTimeout--) == 0) return 6;
	} 
	
	/* Send the EEPROM's internal address to write to */
	I2C_SendData(I2C1,PointerAddr);
  
	I2CTimeout = I2CT_FLAG_TIMEOUT;
	/*主模式发送数据字节完成并受到ACK相应 */
	while(I2C_GetStatus(I2C1)!=0x28)
	{
		if((I2CTimeout--) == 0) return 7;
	} 
	
	
	/* Send STOP condition */
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	//uSDelay(50);
	
	/* Send STRAT condition */
	I2C_GenerateSTART(I2C1, ENABLE);
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主机发送起始位完成*/
	while(I2C_GetStatus(I2C1) !=0x8)  
	{
		if((I2CTimeout--) == 0) return 8;
	} 
	
	/* Send EEPROM address for write */
	SlaveAddr = 0x90 | (SlaveAddr & 0x0f);
	I2C_SendData(I2C1,SlaveAddr);  
	
	I2CTimeout = I2CT_FLAG_TIMEOUT;  
	/*主机发送起始位完成*/
	while(I2C_GetStatus(I2C1) !=0x40)  
	{
		if((I2CTimeout--) == 0) return 9;
	} 
	
	/* While there is data to be read */
	while(Nbyte)  
	{
		if(Nbyte == 1)
		{
			/* Disable Acknowledgement */
			I2C_AcknowledgeConfig(I2C1, DISABLE);
		}
		else
		{
			/* Enable Acknowledgement */
			I2C_AcknowledgeConfig(I2C1, ENABLE);
		}
		
		I2CTimeout = I2CT_LONG_TIMEOUT;
		/*数据字节接收完成*/    
		while((I2C_GetStatus(I2C1)!=0x50)&&(I2C_GetStatus(I2C1)!=0x58))  
		{
			if((I2CTimeout--) == 0) return 10;
		} 
     
		/* Read a byte from the EEPROM */
		*DataPtr = I2C_ReceiveData(I2C1);

		/* Point to the next location where the byte read will be saved */
		DataPtr++; 
      
		/* Decrement the read bytes counter */
		Nbyte--;    
		

	}
      
	/* Send STOP Condition */
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	
	return 0;
}

