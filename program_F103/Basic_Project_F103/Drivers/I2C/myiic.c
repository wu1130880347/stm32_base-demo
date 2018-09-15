
#include "myiic.h"
#include "delay.h"


void IIC_Init(void);                //初始化IIC的IO口	
u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	
void test_i2c(void);

#if (defined SOFT_IIC) && (SOFT_IIC == TRUE)


//IIC所有操作函数
			 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
u8 IIC_Detection(u8 address);


//初始化IIC
void IIC_Init(void)
{			
  static u8 static_flag = 1;
  if(static_flag)
  {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	IIC_SCL=1;
	IIC_SDA=1;
        static_flag = 0;

  }
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
//delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
//delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 //delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
//delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();       //SDA设置为输入  
	IIC_SDA=1;	   
	IIC_SCL=1;	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
//delay_us(2);
	IIC_SCL=1;
//delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
//delay_us(2);
	IIC_SCL=1;
//delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {            
        IIC_SDA = (txd & 0x80)>>7;
        txd<<=1; 	  
	//delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
	//delay_us(2); 
		IIC_SCL=0;	
	//delay_us(2);
    }	
	//IIC_SDA = 1; 
	//IIC_SCL = 1;
	//IIC_SCL = 0;
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        //delay_us(2);
	IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
	//delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

//IIC写函数   
//参数 从机地址  从机寄存器  数据
u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data)
{
	IIC_Start();
	IIC_Send_Byte(daddr);
	if(IIC_Wait_Ack()) return 1;
	IIC_Send_Byte(addr);
	if(IIC_Wait_Ack()) return 1;
	IIC_Send_Byte(data);
	if(IIC_Wait_Ack()) return 1;
	IIC_Stop();
	return 0;
}

//IIC 读函数  
//参数 从机地址  从机寄存器
u8 IIC_Read_One_Byte(u8 daddr,u8 addr)
{
	u8 temp = 0;
	IIC_Start();
	IIC_Send_Byte(daddr);
	if(IIC_Wait_Ack()) return 1;
	IIC_Send_Byte(addr);
	if(IIC_Wait_Ack()) return 1;

	IIC_Start();
	IIC_Send_Byte(daddr + 1);
	if(IIC_Wait_Ack()) return 1;
	temp = IIC_Read_Byte(1);
	IIC_Stop();
	
	return temp;
}
//IIC探测程序
u8 IIC_Detection(u8 address)
{
        u8 temp = 0;
        IIC_Start();
	IIC_Send_Byte(address);
	if(IIC_Wait_Ack()) temp = 1;
        IIC_Stop();
        return temp;
}

void test_i2c(void)
{
  u16 address = 0;
  IIC_Init();
  Dprintf(IIC_DECTION,"\r\n\r\n/*******************************/\r\n");
  Dprintf(IIC_DECTION,"/*******************************/\r\n");
  Dprintf(IIC_DECTION,"I2C find address Map : \r\n");
  for(address = 0;address <= 0xFF;address+=2)
  {
    if((address) % 16 == 0)Dprintf(IIC_DECTION,"\r\n");
    if(!IIC_Detection((u8)address))Dprintf(IIC_DECTION," 0x%x ",address);
    else Dprintf(IIC_DECTION,"  No  ");
  }
  Dprintf(IIC_DECTION,"\r\n/*******************************/\r\n");
  Dprintf(IIC_DECTION,"/*******************************/\r\n");
}

#elif (defined HARD_IIC) && (HARD_IIC == TRUE)


u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
	//delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
	//delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
	//delay_us(2); 
		IIC_SCL=0;	
	//delay_us(2);
    }	 
} 

void IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟

  //GPIOB8,B9初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	IIC_SCL=1;
	IIC_SDA=1;
}
#endif

























