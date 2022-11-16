#ifndef _I2C_H_
#define _I2C_H_
/***********************************************Include*****************************************/
#include "pt32f0xx_conf.h"

/***********************************************Define******************************************/
#define uchar				unsigned char
#define	M_SDA_PORT			CMSDK_PA
#define	M_SDA_PIN			GPIO_PinSource10

#define	M_SCL_PORT			CMSDK_PA
#define	M_SCL_PIN			GPIO_PinSource9

/*等待超时时间*/
#define I2CT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT         ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))


/**********************************************Varible*******************************************/
static __IO uint32_t  I2CTimeout = I2CT_LONG_TIMEOUT;   
/***********************************************Fuction*****************************************/
void InitI2C(void);
char WriteTMP275(uchar Slaveaddr,uchar Pointeraddr,uchar *DataPtr);
char ReadTMP275(uchar Slaveaddr,uchar Pointeraddr,uchar *DataPtr,uchar Nbyte);

#endif
