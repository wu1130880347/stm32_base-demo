#ifndef __MYIIC_H_
#define __MYIIC_H_
#include "sys.h"
#include "boards.h"

#ifndef SOFT_IIC
#define SOFT_IIC TRUE
#endif

#ifndef HARD_IIC
#define HARD_IIC FALSE
#endif

#define IIC_DECTION TRUE


#if (defined SOFT_IIC) && (SOFT_IIC == TRUE)

//IO方向设置
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数
//位操作对应的IO口	 
#define IIC_SCL    PBout(I2C1_SCL_PIN) //SCL
#define IIC_SDA    PBout(I2C1_SDA_PIN) //SDA	 
#define READ_SDA   PBin(I2C1_SDA_PIN)  //输入SDA 

//IIC所有操作函数
extern void IIC_Start(void);				//发送IIC开始信号
extern void IIC_Stop(void);

extern void IIC_Init(void);                //初始化IIC的IO口
extern void test_i2c(void);
extern u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
extern u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

#elif (defined HARD_IIC) && (HARD_IIC == TRUE)

extern void IIC_Init(void);                //初始化IIC的IO口	
extern void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
extern u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

#else

#warning "NOT Use I2C Drivers Successful... ";

#endif

#endif

















