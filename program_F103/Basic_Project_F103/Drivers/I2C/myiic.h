#ifndef __MYIIC_H_
#define __MYIIC_H_
#include "sys.h"
#include "boards.h"

#ifndef SOFT_IIC
#define SOFT_IIC FALSE
#endif

#ifndef HARD_IIC
#define HARD_IIC TRUE
#endif

#define IIC_DECTION TRUE


#if (defined SOFT_IIC) && (SOFT_IIC == TRUE)

//IO��������
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO��������
//λ������Ӧ��IO��	 
#define IIC_SCL    PBout(I2C1_SCL_PIN) //SCL
#define IIC_SDA    PBout(I2C1_SDA_PIN) //SDA	 
#define READ_SDA   PBin(I2C1_SDA_PIN)  //����SDA 

//IIC���в�������
extern void IIC_Start(void);				//����IIC��ʼ�ź�
extern void IIC_Stop(void);

extern void IIC_Init(void);                //��ʼ��IIC��IO��
extern u16 test_i2c(u8* cmd_data);
extern u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
extern u8 IIC_Read_One_Byte(u8 daddr,u8 addr);
extern u8 IIC_Detection(u8 address);	  

#elif (defined HARD_IIC) && (HARD_IIC == TRUE)
#define TIME_OUT_US 1000

extern void IIC_Init(void);                //��ʼ��IIC��IO��	
extern u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
extern u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
extern u16 test_i2c(u8* cmd_data);
extern u8 IIC_Write_n_Byte(u8 daddr, u8 addr, u8 *data, u16 len);
extern u8 IIC_Read_n_Byte(u8 daddr, u8 addr, u8 *data, u16 len);
extern u8 IIC_Detection(u8 address);

#else

#warning "NOT Use I2C Drivers Successful... ";

#endif

#endif

















