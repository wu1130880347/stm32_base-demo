
#include "myiic.h"
#include "delay.h"


void IIC_Init(void);                //��ʼ��IIC��IO��	
u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	
void test_i2c(void);

#if (defined SOFT_IIC) && (SOFT_IIC == TRUE)


//IIC���в�������
			 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
u8 IIC_Detection(u8 address);


//��ʼ��IIC
void IIC_Init(void)
{			
  static u8 static_flag = 1;
  if(static_flag)
  {
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	IIC_SCL=1;
	IIC_SDA=1;
        static_flag = 0;

  }
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
//delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
//delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 //delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
//delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();       //SDA����Ϊ����  
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {            
        IIC_SDA = (txd & 0x80)>>7;
        txd<<=1; 	  
	//delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
	//delay_us(2); 
		IIC_SCL=0;	
	//delay_us(2);
    }	
	//IIC_SDA = 1; 
	//IIC_SCL = 1;
	//IIC_SCL = 0;
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

//IICд����   
//���� �ӻ���ַ  �ӻ��Ĵ���  ����
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

//IIC ������  
//���� �ӻ���ַ  �ӻ��Ĵ���
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
//IIC̽�����
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
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
	//delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
	//delay_us(2); 
		IIC_SCL=0;	
	//delay_us(2);
    }	 
} 

void IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	IIC_SCL=1;
	IIC_SDA=1;
}
#endif

























