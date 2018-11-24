
#include "myiic.h"
#include "delay.h"
#include "boards.h"

void IIC_Init(void); //��ʼ��IIC��IO��
u8 IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data);
u8 IIC_Read_One_Byte(u8 daddr, u8 addr);

u8 IIC_Write_n_Byte(u8 daddr, u8 addr, u8 *data, u16 len);
u8 IIC_Read_n_Byte(u8 daddr, u8 addr, u8 *data, u16 len);

void IIC_Send_Byte(u8 txd);			 //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack); //IIC��ȡһ���ֽ�

u16 test_i2c(u8 *cmd_data);

#if (defined SOFT_IIC) && (SOFT_IIC == TRUE)

//IIC���в�������

void IIC_Start(void);  //����IIC��ʼ�ź�
void IIC_Stop(void);   //����IICֹͣ�ź�
void IIC_Ack(void);	//IIC����ACK�ź�
void IIC_NAck(void);   //IIC������ACK�ź�
u8 IIC_Wait_Ack(void); //IIC�ȴ�ACK�ź�
u8 IIC_Detection(u8 address);

//��ʼ��IIC
void IIC_Init(void)
{
	static u8 static_flag = 1;
	if (static_flag)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(I2C1_RCC_SOURCE, ENABLE); //ʹ��GPIOBʱ��

		GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN_MASK;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(I2C1_SCL_SOURCE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = I2C1_SDA_PIN_MASK;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(I2C1_SDA_SOURCE, &GPIO_InitStructure);

		IIC_SCL = 1;
		IIC_SDA = 1;
		static_flag = 0;
	}
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT(); //sda�����
	IIC_SDA = 1;
	IIC_SCL = 1;
	//delay_us(4);
	IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
		//delay_us(4);
	IIC_SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT(); //sda�����
	IIC_SCL = 0;
	IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
	//delay_us(4);
	IIC_SCL = 1;
	IIC_SDA = 1; //����I2C���߽����ź�
				 //delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;
	SDA_IN(); //SDA����Ϊ����
	IIC_SDA = 1;
	IIC_SCL = 1;
	while (READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0; //ʱ�����0
	return 0;
}
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 0;
	//delay_us(2);
	IIC_SCL = 1;
	//delay_us(2);
	IIC_SCL = 0;
}
//������ACKӦ��
void IIC_NAck(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 1;
	//delay_us(2);
	IIC_SCL = 1;
	//delay_us(2);
	IIC_SCL = 0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT();
	IIC_SCL = 0; //����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		IIC_SDA = (txd & 0x80) >> 7;
		txd <<= 1;
		//delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL = 1;
		//delay_us(2);
		IIC_SCL = 0;
		//delay_us(2);
	}
	//IIC_SDA = 1;
	//IIC_SCL = 1;
	//IIC_SCL = 0;
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	SDA_IN(); //SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		//delay_us(2);
		IIC_SCL = 1;
		receive <<= 1;
		if (READ_SDA)
			receive++;
		//delay_us(1);
	}
	if (!ack)
		IIC_NAck(); //����nACK
	else
		IIC_Ack(); //����ACK
	return receive;
}

//IICд����
//���� �ӻ���ַ  �ӻ��Ĵ���  ����
u8 IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data)
{
	IIC_Start();
	IIC_Send_Byte(daddr);
	if (IIC_Wait_Ack())
		return 1;
	IIC_Send_Byte(addr);
	if (IIC_Wait_Ack())
		return 1;
	IIC_Send_Byte(data);
	if (IIC_Wait_Ack())
		return 1;
	IIC_Stop();
	return 0;
}

//IIC ������
//���� �ӻ���ַ  �ӻ��Ĵ���
u8 IIC_Read_One_Byte(u8 daddr, u8 addr)
{
	u8 temp = 0;
	IIC_Start();
	IIC_Send_Byte(daddr);
	if (IIC_Wait_Ack())
		return 1;
	IIC_Send_Byte(addr);
	if (IIC_Wait_Ack())
		return 1;

	IIC_Start();
	IIC_Send_Byte(daddr + 1);
	if (IIC_Wait_Ack())
		return 1;
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
	if (IIC_Wait_Ack())
		temp = 1;
	IIC_Stop();
	return temp;
}

u16 test_i2c(u8 *cmd_data)
{
	u16 address = 0;
	IIC_Init();
	Dprintf(IIC_DECTION, "\r\n\r\n/*******************************/\r\n");
	Dprintf(IIC_DECTION, "/*******************************/\r\n");
	Dprintf(IIC_DECTION, "I2C find address Map : \r\n");
	for (address = 0; address <= 0xFF; address += 2)
	{
		if ((address) % 16 == 0)
			Dprintf(IIC_DECTION, "\r\n");
		if (!IIC_Detection((u8)address))
			Dprintf(IIC_DECTION, " 0x%x ", address >> 1);
		else
			Dprintf(IIC_DECTION, "  No  ");
	}
	Dprintf(IIC_DECTION, "\r\n/*******************************/\r\n");
	Dprintf(IIC_DECTION, "/*******************************/\r\n");
	return 0;
}

#elif (defined HARD_IIC) && (HARD_IIC == TRUE)

volatile u16 timeout = 0;

u8 IIC_Write_One_Byte(u8 daddr, u8 addr, u8 data)
{
	timeout = TIME_OUT_US;
	I2C_GenerateSTART(I2C1, ENABLE);							//������ʼ�ź�
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) //���	EV5�¼�
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "i2c start Fail\n");
	}
	timeout = TIME_OUT_US;

	I2C_Send7bitAddress(I2C1, daddr, I2C_Direction_Transmitter);			  //����7λEEPROM��Ӳ����ַ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) //���EV6�¼�
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "call slave address Fail\n");
	}
	timeout = TIME_OUT_US;

	I2C_SendData(I2C1, addr);										 //���Ͳ������ڴ��ַ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) //���EV8�¼�
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "send start write data address Fail\n");
	}
	timeout = TIME_OUT_US;

	I2C_SendData(I2C1, data);										 //Ҫд������ݣ�һ���ֽڣ�
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) //���EV8�¼�
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "send one data Fail\n");
	}

	I2C_GenerateSTOP(I2C1, ENABLE); //���ͽ����ź�
	return 0;
}
u8 IIC_Read_One_Byte(u8 daddr, u8 addr)
{
	u8 readtemp;
	timeout = TIME_OUT_US;

	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) //5
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "i2c start Fail\n");
	}
	timeout = TIME_OUT_US;

	I2C_Send7bitAddress(I2C1, daddr, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) //6
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "call slave address Fail");
	}
	timeout = TIME_OUT_US;

	I2C_SendData(I2C1, addr);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "send start read data address Fail");
	}
	timeout = TIME_OUT_US;

	I2C_GenerateSTART(I2C1, ENABLE);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "i2c read start Fail");
	}
	timeout = TIME_OUT_US;

	I2C_Send7bitAddress(I2C1, daddr, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "recall slave address Fail");
	}
	timeout = TIME_OUT_US;

	I2C_AcknowledgeConfig(I2C1, ENABLE);

	/* ��� EV7 �¼� */
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
	{
		if ((timeout--) == 0)
			Dprintf(IIC_DECTION, "read byte Fail");
	}
	timeout = TIME_OUT_US;

	/* ��ȡ�������� */
	readtemp = I2C_ReceiveData(I2C1);

	/* ֹͣ�ź� */
	I2C_GenerateSTOP(I2C1, ENABLE);

	return readtemp;
}

u8 IIC_Write_n_Byte(u8 daddr, u8 addr, u8 *data, u16 len)
{
	volatile u16 temp = 0;
	timeout = TIME_OUT_US;

	I2C_GenerateSTART(I2C1, ENABLE);							//������ʼ�ź�
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) //���	EV5�¼�
	{
		if ((timeout--) == 0)
		{
			Dprintf(IIC_DECTION, "i2c start Fail\n");
			return 1;
		}
	}
	timeout = TIME_OUT_US;

	I2C_Send7bitAddress(I2C1, daddr, I2C_Direction_Transmitter);			  //����7λEEPROM��Ӳ����ַ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) //���EV6�¼�
	{
		if ((timeout--) == 0)
		{
			Dprintf(IIC_DECTION, "call slave address Fail\n");
			return 1;
		}
	}
	timeout = TIME_OUT_US;

	I2C_SendData(I2C1, addr);										 //���Ͳ������ڴ��ַ
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) //���EV8�¼�
	{
		if ((timeout--) == 0)
		{
			Dprintf(IIC_DECTION, "send start write data address Fail\n");
			return 1;
		}
	}
	printf("len = %d\r\n",len);
	for (temp = 0; temp < len; temp++)
	{
		timeout = TIME_OUT_US;
		I2C_SendData(I2C1, *(data + temp)); //Ҫд������ݣ�һ���ֽڣ�

		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) //���EV8�¼�
		{
			if ((timeout--) == 0)
			{
				Dprintf(IIC_DECTION, "send %d data Fail\n", temp);
				return 1;
			}
		}
		printf("addr = 0x%2x data = 0x%2x\r\n",addr++,*(data + temp));
	}
	printf("iic write OK\r\n");
	I2C_GenerateSTOP(I2C1, ENABLE); //���ͽ����ź�
	return 0;
}
u8 IIC_Read_n_Byte(u8 daddr, u8 addr, u8 *data, u16 len)
{
	return 0;
}

u8 IIC_Detection(u8 address)
{
	u8 temp = 0;
	I2C_GenerateSTART(I2C1, ENABLE);
	timeout = 100;
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
	{
		if ((timeout--) == 0)
		{
			temp = 0;
			break;
		}
	}
	timeout = 100;
	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) //6
	{
		if ((timeout--) == 0)
		{
			temp = 1;
			break;
		}
	}
	I2C_GenerateSTOP(I2C1, ENABLE);
	return temp;
}

u16 test_i2c(u8 *cmd_data)
{
	u16 address = 0;
	IIC_Init();
	Dprintf(IIC_DECTION, "\r\n\r\n/*******************************/\r\n");
	Dprintf(IIC_DECTION, "/*******************************/\r\n");
	Dprintf(IIC_DECTION, "I2C find address Map : \r\n");
	for (address = 0; address <= 0xFF; address += 2)
	{
		if ((address) % 16 == 0)
			Dprintf(IIC_DECTION, "\r\n");
		if (!IIC_Detection((u8)address))
			Dprintf(IIC_DECTION, " 0x%x ", address >> 1);
		else
			Dprintf(IIC_DECTION, "  No  ");
	}
	Dprintf(IIC_DECTION, "\r\n/*******************************/\r\n");
	Dprintf(IIC_DECTION, "/*******************************/\r\n");
	return 0;
}

u8 IIC_Read_Byte(unsigned char ack)
{
	return 0;
}

void IIC_Send_Byte(u8 txd)
{
}

void IIC_Init(void)
{
	static u8 static_flag = 1;
	if (static_flag)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		I2C_InitTypeDef I2C_InitStruct;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE); //ʹ��I2C1ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = I2C1_SCL_PIN_MASK;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(I2C1_SCL_SOURCE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = I2C1_SDA_PIN_MASK;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(I2C1_SDA_SOURCE, &GPIO_InitStructure);

		I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
		I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
		I2C_InitStruct.I2C_ClockSpeed = 100000;
		I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
		I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
		I2C_InitStruct.I2C_OwnAddress1 = 0x55;
		I2C_Init(I2C1, &I2C_InitStruct);

		I2C_Cmd(I2C1, ENABLE);
	}
}
#endif
