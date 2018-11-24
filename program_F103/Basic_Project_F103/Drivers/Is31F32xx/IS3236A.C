#include "reg922.h"
#include "intrins.h"

/*************************************************/
//宏编译开关
//可以根据需要加入不同硬件连接的宏定义
#define DEMO_MCU_CTRL_V10			0x01 //DEMO板V1.0

#define CTRL_CHOICE						0x01 //选择用DEMO板V1.0编译

/*************************************************/

#if (CTRL_CHOICE==DEMO_MCU_CTRL_V10)
//其他硬件连接定义
sbit VRGB=P0^1;	//RGB灯控制
sbit VWRI=P0^2;	//单色灯控制
sbit KEY=P1^4;	//按键端口
sbit EXT_CTRL=P1^1;//外部控制检测口

//IS3236 硬件连接定义
sbit IS_SDA_PIN=P1^7;
sbit IS_SCL_PIN=P0^0;
sbit IS_SDB_PIN=P1^0; 
sbit IS_ADR_PIN=P1^6;
#endif

/*************************************************/
//数据类型定义
#define   INT8  	signed char
#define   UINT8 	unsigned char
#define   UINT16 	unsigned int 
#define   UINT32 	unsigned long int

//IS3236 软件地址定义
#define IS3236_IIC_ADDRESS  0x78//AD 接 GND
//#define IS3226_IIC_ADDRESS  0x7E//AD 接 VCC
//#define IS3226_IIC_ADDRESS  0x7A//AD 接 SCL
//#define IS3226_IIC_ADDRESS  0x7C//AD 接 SDA

#define OPEN 	0x01			//工作模式软件开
#define CLOSE 	0x00			//工作模式软件关

#define RGB_LED 	0x02			//RGB LED
#define S_LED  		0x01			//单色灯

/****************以下是寄存器定义******************/
//各种平台通用
#define IS3236_REG_WORK			 	0x00 //关断寄存器

#define IS3236_REG_PWM_OUT1 	0x01 //输出PWM寄存器
#define IS3236_REG_PWM_OUT2 	0x02
#define IS3236_REG_PWM_OUT3 	0x03
#define IS3236_REG_PWM_OUT4 	0x04
#define IS3236_REG_PWM_OUT5 	0x05
#define IS3236_REG_PWM_OUT6 	0x06
#define IS3236_REG_PWM_OUT7 	0x07
#define IS3236_REG_PWM_OUT8 	0x08
#define IS3236_REG_PWM_OUT9 	0x09
#define IS3236_REG_PWM_OUT10 	0x0A
#define IS3236_REG_PWM_OUT11 	0x0B
#define IS3236_REG_PWM_OUT12 	0x0C
#define IS3236_REG_PWM_OUT13 	0x0D
#define IS3236_REG_PWM_OUT14 	0x0E
#define IS3236_REG_PWM_OUT15 	0x0F
#define IS3236_REG_PWM_OUT16 	0x10
#define IS3236_REG_PWM_OUT17 	0x11
#define IS3236_REG_PWM_OUT18 	0x12
#define IS3236_REG_PWM_OUT19 	0x13
#define IS3236_REG_PWM_OUT20 	0x14
#define IS3236_REG_PWM_OUT21 	0x15
#define IS3236_REG_PWM_OUT22 	0x16
#define IS3236_REG_PWM_OUT23 	0x17
#define IS3236_REG_PWM_OUT24 	0x18
#define IS3236_REG_PWM_OUT25 	0x19
#define IS3236_REG_PWM_OUT26 	0x1A
#define IS3236_REG_PWM_OUT27 	0x1B
#define IS3236_REG_PWM_OUT28 	0x1C
#define IS3236_REG_PWM_OUT29 	0x1D
#define IS3236_REG_PWM_OUT30 	0x1E
#define IS3236_REG_PWM_OUT31 	0x1F
#define IS3236_REG_PWM_OUT32 	0x20
#define IS3236_REG_PWM_OUT33 	0x21
#define IS3236_REG_PWM_OUT34 	0x22
#define IS3236_REG_PWM_OUT35 	0x23
#define IS3236_REG_PWM_OUT36 	0x24

#define	IS3236_REG_DATA_UPDATE	0x25 //PWM和LED控制更新寄存器

#define IS3236_REG_CTRL_OUT1 	0x26 //LED控制寄存器
#define IS3236_REG_CTRL_OUT2 	0x27
#define IS3236_REG_CTRL_OUT3 	0x28
#define IS3236_REG_CTRL_OUT4 	0x29
#define IS3236_REG_CTRL_OUT5 	0x2A
#define IS3236_REG_CTRL_OUT6 	0x2B
#define IS3236_REG_CTRL_OUT7 	0x2C
#define IS3236_REG_CTRL_OUT8 	0x2D
#define IS3236_REG_CTRL_OUT9 	0x2E
#define IS3236_REG_CTRL_OUT10 	0x2F
#define IS3236_REG_CTRL_OUT11 	0x30
#define IS3236_REG_CTRL_OUT12 	0x31
#define IS3236_REG_CTRL_OUT13 	0x32
#define IS3236_REG_CTRL_OUT14 	0x33
#define IS3236_REG_CTRL_OUT15 	0x34
#define IS3236_REG_CTRL_OUT16 	0x35
#define IS3236_REG_CTRL_OUT17 	0x36
#define IS3236_REG_CTRL_OUT18 	0x37
#define IS3236_REG_CTRL_OUT19 	0x38
#define IS3236_REG_CTRL_OUT20 	0x39
#define IS3236_REG_CTRL_OUT21 	0x3A
#define IS3236_REG_CTRL_OUT22 	0x3B
#define IS3236_REG_CTRL_OUT23 	0x3C
#define IS3236_REG_CTRL_OUT24 	0x3D
#define IS3236_REG_CTRL_OUT25 	0x3E
#define IS3236_REG_CTRL_OUT26 	0x3F
#define IS3236_REG_CTRL_OUT27 	0x40
#define IS3236_REG_CTRL_OUT28 	0x41
#define IS3236_REG_CTRL_OUT29 	0x42
#define IS3236_REG_CTRL_OUT30 	0x43
#define IS3236_REG_CTRL_OUT31 	0x44
#define IS3236_REG_CTRL_OUT32 	0x45
#define IS3236_REG_CTRL_OUT33 	0x46
#define IS3236_REG_CTRL_OUT34 	0x47
#define IS3236_REG_CTRL_OUT35 	0x48
#define IS3236_REG_CTRL_OUT36 	0x49

#define IS3236_REG_LED_SYNC 	0x4A //输出同步寄存器

#define IS3236_REG_RST 	0x4F 			//复位寄存器

/********************************************************/

#if (CTRL_CHOICE==DEMO_MCU_CTRL_V10)

#define IS_SDA_PIN_High()	 IS_SDA_PIN=1  	//SDA=1
#define IS_SDA_PIN_Low()	 IS_SDA_PIN=0		//SDA=0

#define IS_SCL_PIN_High()	 IS_SCL_PIN=1  	//SCL=1
#define IS_SCL_PIN_Low()	 IS_SCL_PIN=0		//SCL=0

#define	IS_SDB_PIN_High()	 IS_SDB_PIN=1		//chip shut down线输出高.
#define	IS_SDB_PIN_Low()	 IS_SDB_PIN=0		//chip shut down线输出低.

#define	IS_ADR_PIN_High()	 IS_ADR_PIN=1		//硬件地址拉高
#define	IS_ADR_PIN_Low()	 IS_ADR_PIN=0		//硬件地址拉低

#endif


/*******************IIC 通讯底层***********************/
#define IS_IIC_DELAY_SW			OPEN  	//IIC通讯延时控制开关  OPEN 开   CLOSE 关
#define IS_IIC_DELAY_TIME	 	0X01 		//IIC通讯延时时间设置

void Delay_IIC(UINT16 time)					//IIC通讯延时函数
{
	while(time--);
}

void IS_IIC_Start(void)//启动总线
{
	IS_SDA_PIN_High();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif
	
	IS_SCL_PIN_High();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif
	
	IS_SDA_PIN_Low();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif
	
	IS_SCL_PIN_Low();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif
}

void IS_IIC_Stop(void)//停止总线
{
	IS_SCL_PIN_Low();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	IS_SDA_PIN_Low();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	IS_SCL_PIN_High();
	
	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	IS_SDA_PIN_High();

	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif
}
		 

UINT8 IS_IIC_TestAck(void)//测试应答信号
{
	UINT8 bit_ack;
	IS_SDA_PIN_High();

	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	IS_SCL_PIN_High();

	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	bit_ack=IS_SDA_PIN;

	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	IS_SCL_PIN_Low();

	#if IS_IIC_DELAY_SW
	Delay_IIC(IS_IIC_DELAY_TIME);
	#endif

	return(bit_ack);
}

void IS_IIC_Write_Byte(UINT8 inputdata)//写入8个二进制位
{
	UINT8 temp,bMask=0X80;
	for(temp=0;temp<8;temp++)
	{
		if(inputdata&bMask)
		{
			IS_SDA_PIN_High();
		}
		else
		{
			IS_SDA_PIN_Low();
		}
		#if IS_IIC_DELAY_SW
		Delay_IIC(IS_IIC_DELAY_TIME);
		#endif

		IS_SCL_PIN_High();

		#if IS_IIC_DELAY_SW
		Delay_IIC(IS_IIC_DELAY_TIME);
		#endif

		IS_SCL_PIN_Low();

		#if IS_IIC_DELAY_SW
		Delay_IIC(IS_IIC_DELAY_TIME);
		#endif

		bMask=bMask>>1;
	}
}

/****************************************************/
//写一个字节
void IS_IIC_Write_REG(UINT8 reg_address,UINT8 reg_data)
{
	EA=0;											//在写入时关总中断
	IS_IIC_Start();									//开始信号
	IS_IIC_Write_Byte(IS3236_IIC_ADDRESS);			//写IIC地址
	IS_IIC_TestAck();								//测试应答
	IS_IIC_Write_Byte(reg_address);					//写入寄存器地址
	IS_IIC_TestAck();								//测试应答
	IS_IIC_Write_Byte(reg_data);					//写入数据
	IS_IIC_TestAck();								//测试应答
	IS_IIC_Stop();									//结束信号
	EA=1;											//写入完成后开总中断
}

//连续写入N个同样数据
//reg_address起始地址		 reg_data数据			unit写入的寄存器个数
void IS_IIC_Write_REG_Series(UINT8 reg_address,UINT8 reg_data,UINT8 unit)
{
	EA=0;																	//在写入时关总中断
	IS_IIC_Start();												//开始信号
	IS_IIC_Write_Byte(IS3236_IIC_ADDRESS);//写IIC地址
	IS_IIC_TestAck();											//测试应答
	IS_IIC_Write_Byte(reg_address);				//写入寄存器地址
	IS_IIC_TestAck();											//测试应答
	for(;unit!=0;unit--)
	{
		IS_IIC_Write_Byte(reg_data);				//写入数据
		IS_IIC_TestAck();										//测试应答
	}
	IS_IIC_Stop();												//结束信号
	EA=1;																	//写入完成后开总中断
}

void IS_IIC_Write_REG_Table(UINT8 reg_address,UINT8 *table)
{
	UINT8 ctemp;
	EA=0;																	//在写入时关总中断
	IS_IIC_Start();												//开始信号
	IS_IIC_Write_Byte(IS3236_IIC_ADDRESS);//写IIC地址
	IS_IIC_TestAck();											//测试应答
	IS_IIC_Write_Byte(reg_address);				//写入寄存器地址
	IS_IIC_TestAck();											//测试应答
	for(ctemp=0;ctemp<7;ctemp++)
	{
		IS_IIC_Write_Byte(table[ctemp]);				//写入数据
		IS_IIC_TestAck();										//测试应答
	}
	IS_IIC_Stop();												//结束信号
	EA=1;																	//写入完成后开总中断
}

//IS3236 软件开关控制
void IS3236_Soft_SW(UINT8 workmode)
{
	IS_IIC_Write_REG(IS3236_REG_WORK,workmode);
}
//IS3236 硬件开关控制
void IS3236_Hard_SW(UINT8 workmode)
{
	if(workmode==0x00)
	{IS_SDB_PIN_Low();}
	else
	{IS_SDB_PIN_High();}
}
//IS3236 PWM更新
void IS3236_DataUpdate(void)
{
	IS_IIC_Write_REG(IS3236_REG_DATA_UPDATE,0xff);
}
//IS3236 输出控制 4个字节分别对应32个OUT
void IS3236_OUT_SW(UINT8 out1_8,UINT8 out9_16,UINT8 out17_24,UINT8 out25_32,UINT8 out33_36)
{	
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT1,out1_8&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT2,(out1_8&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT3,(out1_8&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT4,(out1_8&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT5,(out1_8&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT6,(out1_8&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT7,(out1_8&0x40)>>6);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT8,(out1_8&0x80)>>7);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT9,out9_16&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT10,(out9_16&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT11,(out9_16&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT12,(out9_16&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT13,(out9_16&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT14,(out9_16&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT15,(out9_16&0x40)>>6);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT16,(out9_16&0x80)>>7);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT17,out17_24&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT18,(out17_24&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT19,(out17_24&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT20,(out17_24&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT21,(out17_24&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT22,(out17_24&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT23,(out17_24&0x40)>>6);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT24,(out17_24&0x80)>>7);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT25,out25_32&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT26,(out25_32&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT27,(out25_32&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT28,(out25_32&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT29,(out25_32&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT30,(out25_32&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT31,(out25_32&0x40)>>6);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT32,(out25_32&0x80)>>7);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT33,out33_36&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT34,(out33_36&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT35,(out33_36&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT36,(out33_36&0x08)>>3);

	IS3236_DataUpdate();
}
//IS3236 硬件初始化   输入参数为写入所有PWM寄存器的值
void IS3236_Init(UINT8 pwmdata)
{
	IS3236_Hard_SW(OPEN);//开硬件开关
	IS3236_Soft_SW(OPEN);//开软件开关
	IS_IIC_Write_REG_Series(IS3236_REG_PWM_OUT1,pwmdata,36);
 	IS_IIC_Write_REG_Series(IS3236_REG_CTRL_OUT1,0x01,36);
	IS3236_DataUpdate();//更新PWM
}
void IS3236_DEMO_LED_SW(UINT8 led)
{
	if(led==1)
	{
		VRGB=1;
		VWRI=0;
	}
	if(led==2)
	{
		VRGB=0;
		VWRI=1;
	}
}

void IS3236_DEMO_DISPALY_NUM(UINT8 num1,UINT8 num2,UINT8 num3,UINT8 num4)
{
	UINT8 table_num[7];
	switch(num1)
	{
		case 0:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 1:
		table_num[0]=0x00;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 2:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0x00;break;
		case 3:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 4:
		table_num[0]=0x00;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 5:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 6:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 7:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 8:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 9:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
	}	
	IS_IIC_Write_REG_Table(IS3236_REG_PWM_OUT1,table_num);
	switch(num2)
	{
		case 0:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 1:
		table_num[0]=0x00;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 2:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0x00;break;
		case 3:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 4:
		table_num[0]=0x00;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 5:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 6:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 7:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 8:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 9:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
	}	
	IS_IIC_Write_REG_Table(IS3236_REG_PWM_OUT11,table_num);
	switch(num3)
	{
		case 0:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 1:
		table_num[0]=0x00;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 2:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0x00;break;
		case 3:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 4:
		table_num[0]=0x00;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 5:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 6:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 7:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 8:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 9:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
	}	
	IS_IIC_Write_REG_Table(IS3236_REG_PWM_OUT20,table_num);
	switch(num4)
	{
		case 0:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 1:
		table_num[0]=0x00;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 2:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0x00;break;
		case 3:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 4:
		table_num[0]=0x00;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 5:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 6:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0x00;table_num[6]=0xff;break;
		case 7:
		table_num[0]=0xff;table_num[1]=0x00;table_num[2]=0x00;table_num[3]=0x00;table_num[4]=0x00;table_num[5]=0xff;table_num[6]=0xff;break;
		case 8:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0xff;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
		case 9:
		table_num[0]=0xff;table_num[1]=0xff;table_num[2]=0x00;table_num[3]=0xff;table_num[4]=0xff;table_num[5]=0xff;table_num[6]=0xff;break;
	}	
	IS_IIC_Write_REG_Table(IS3236_REG_PWM_OUT30,table_num);
	IS3236_DataUpdate();//更新PWM
}

code UINT8 NUM_TABLE[10]=	
{
	0x6f,0x60,0x3d,0x79,0x72,0x5b,0x5f,0x51,0x7f,0x7b
};

void IS3236_DEMO_DISPALY_NUM_CTRL(UINT8 num1,UINT8 num2,UINT8 num3,UINT8 num4)
{
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT1,NUM_TABLE[num1]&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT2,(NUM_TABLE[num1]&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT3,(NUM_TABLE[num1]&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT4,(NUM_TABLE[num1]&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT5,(NUM_TABLE[num1]&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT6,(NUM_TABLE[num1]&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT7,(NUM_TABLE[num1]&0x40)>>6);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT8,0x00);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT9,0x00);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT10,0x00);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT11,NUM_TABLE[num2]&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT12,(NUM_TABLE[num2]&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT13,(NUM_TABLE[num2]&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT14,(NUM_TABLE[num2]&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT15,(NUM_TABLE[num2]&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT16,(NUM_TABLE[num2]&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT17,(NUM_TABLE[num2]&0x40)>>6);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT18,0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT19,0x00);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT20,NUM_TABLE[num3]&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT21,(NUM_TABLE[num3]&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT22,(NUM_TABLE[num3]&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT23,(NUM_TABLE[num3]&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT24,(NUM_TABLE[num3]&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT25,(NUM_TABLE[num3]&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT26,(NUM_TABLE[num3]&0x40)>>6);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT27,0x00);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT28,0x00);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT29,0x00);

	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT30,NUM_TABLE[num4]&0x01);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT31,(NUM_TABLE[num4]&0x02)>>1);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT32,(NUM_TABLE[num4]&0x04)>>2);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT33,(NUM_TABLE[num4]&0x08)>>3);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT34,(NUM_TABLE[num4]&0x10)>>4);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT35,(NUM_TABLE[num4]&0x20)>>5);
	IS_IIC_Write_REG(IS3236_REG_CTRL_OUT36,(NUM_TABLE[num4]&0x40)>>6);

	IS3236_DataUpdate();	
}
UINT8 mode=7,mode_temp;
UINT8 shi=12,fen=0,miao=0;
UINT8 count[5];
code UINT8 Gamma_T32[32]=	
													{
														0X00,0X01,0X02,0X04,0X06,0X0A,0X0D,0X12,
														0X16,0X1C,0X21,0X27,0X2E,0X35,0X3D,0X45,
														0X4E,0X56,0X60,0X6A,0X74,0X7E,0X8A,0X95,
														0XA1,0XAD,0XBA,0XC7,0XD4,0XE2,0XF0,0XFF
													};
code UINT8 Gamma_T64[64]=
													{
														0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
														0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
														0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
														0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
														0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
														0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
														0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
														0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff
													};
code UINT8 PWM1[32]=
													{
														//0xff,0x7d,0x55,0x34,0x1a,0x08,0x00,0x00,
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
														0xff,0x7d,0x55,0x34,0x1a,0x08,0x00,0x00,
														0xff,0x7d,0x55,0x34,0x1a,0x08,0x00,0x00,
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
													//	0xff,0x7d,0x55,0x34,0x1a,0x08,0x00,0x00
													};
code UINT8 PWM2[40]=
													{
														0xff,0x7d,0x55,0x34,0x1a,0x08,0x00,0x00,
														0X00,0X00,0X08,0X1A,0X34,0X55,0X7D,0XFF,
														0xff,0x7d,0x55,0x34,0x1a,0x08,0x00,0x00,
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
														0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF
													};
code UINT8 PWM3[64]=
													{
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
														0x00,0X08,0X1A,0X34,0X55,0X7D,0XAC,0Xff,
														0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
														0Xff,0XAC,0X7D,0X55,0X34,0X1A,0X08,0X00,
														0x00,0X08,0X1A,0X34,0X55,0X7D,0XAC,0Xff,
														0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,														
														0Xff,0XAC,0X7D,0X55,0X34,0X1A,0X08,0X00,
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00
													};
code UINT8 PWM4[80]=
													{
/*													0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
														0x00,0X08,0X1A,0X34,0X55,0X7D,0XAC,0Xff,
														0Xff,0XAC,0X7D,0X55,0X34,0X1A,0X08,0X00,
														0x00,0X08,0X1A,0X34,0X55,0X7D,0XAC,0Xff,														
														0Xff,0XAC,0X7D,0X55,0X34,0X1A,0X08,0X00,
														0x00,0X08,0X1A,0X34,0X55,0X7D,0XAC,0Xff,														
														0Xff,0XAC,0X7D,0X55,0X34,0X1A,0X08,0X00,
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00, */

														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
														0X00,0X01,0X02,0X04,0X06,0X0A,0X0D,0X12,
														0X16,0X1C,0X21,0X27,0X2E,0X35,0X3D,0X45,
														0X4E,0X56,0X60,0X6A,0X74,0X7E,0X8A,0X95,
														0XA1,0XAD,0XBA,0XC7,0XD4,0XE2,0XF0,0XFF,

														0XFF,0XF0,0XE2,0XD4,0XC7,0XBA,0XAD,0XA1,
														0X95,0X8A,0X7E,0X74,0X6A,0X60,0X56,0X4E,
														0X45,0X3D,0X35,0X2E,0X27,0X21,0X1C,0X16,
														0X12,0X0D,0X0A,0X06,0X04,0X02,0X01,0X00,
														0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00														
													};
code UINT8 PWM5[288]=
													{
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,

														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,

														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,

														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
														0X45,0X56,0X6A,0X7E,0X95,0XAD,0XC7,0XE2,0XFF,
														0XFF,0XE2,0XC7,0XAD,0X95,0X7E,0X6A,0X56,0X45,
													};

const unsigned char code PWM_RGB[512]=
{
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
	0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
	0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
	0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
	0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
	0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
	0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
	0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff,

	0xff,0xfe,0xfa,0xf6,0xf1,0xed,0xe9,0xe1,
	0xd6,0xcf,0xcb,0xc6,0xbf,0xb9,0xb0,0xac,
	0xa7,0xa0,0x9a,0x94,0x8d,0x88,0x80,0x7d,
	0x77,0x72,0x6d,0x69,0x64,0x5f,0x5a,0x55,
	0x4f,0x4b,0x48,0x44,0x40,0x3c,0x38,0x34,
	0x2e,0x28,0x25,0x22,0x1f,0x1d,0x1c,0x1a,
	0x16,0x13,0x11,0x0f,0x0d,0x0b,0x09,0x08,
	0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,
	
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,

	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
	0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
	0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
	0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
	0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
	0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
	0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
	0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff,

	0xff,0xfe,0xfa,0xf6,0xf1,0xed,0xe9,0xe1,
	0xd6,0xcf,0xcb,0xc6,0xbf,0xb9,0xb0,0xac,
	0xa7,0xa0,0x9a,0x94,0x8d,0x88,0x80,0x7d,
	0x77,0x72,0x6d,0x69,0x64,0x5f,0x5a,0x55,
	0x4f,0x4b,0x48,0x44,0x40,0x3c,0x38,0x34,
	0x2e,0x28,0x25,0x22,0x1f,0x1d,0x1c,0x1a,
	0x16,0x13,0x11,0x0f,0x0d,0x0b,0x09,0x08,
	0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,
	
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,

	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
	0x08,0x09,0x0b,0x0d,0x0f,0x11,0x13,0x16,
	0x1a,0x1c,0x1d,0x1f,0x22,0x25,0x28,0x2e,
	0x34,0x38,0x3c,0x40,0x44,0x48,0x4b,0x4f,
	0x55,0x5a,0x5f,0x64,0x69,0x6d,0x72,0x77,
	0x7d,0x80,0x88,0x8d,0x94,0x9a,0xa0,0xa7,
	0xac,0xb0,0xb9,0xbf,0xc6,0xcb,0xcf,0xd6,
	0xe1,0xe9,0xed,0xf1,0xf6,0xfa,0xfe,0xff,

	0xff,0xfe,0xfa,0xf6,0xf1,0xed,0xe9,0xe1,
	0xd6,0xcf,0xcb,0xc6,0xbf,0xb9,0xb0,0xac,
	0xa7,0xa0,0x9a,0x94,0x8d,0x88,0x80,0x7d,
	0x77,0x72,0x6d,0x69,0x64,0x5f,0x5a,0x55,
	0x4f,0x4b,0x48,0x44,0x40,0x3c,0x38,0x34,
	0x2e,0x28,0x25,0x22,0x1f,0x1d,0x1c,0x1a,
	0x16,0x13,0x11,0x0f,0x0d,0x0b,0x09,0x08,
	0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00
};
void Delay_Key(UINT8 time)
{
	UINT8 tt;
	for(;time>0;time--)
		for(tt=200;tt>0;tt--);
}

void Delay_ms(UINT8 time)
{
	UINT8 tt,ttt;
	for(;time>0;time--)
		for(tt=200;tt>0;tt--)
			for(ttt=200;ttt>0;ttt--);
}
/*
void	Timer1_isr()	interrupt 3
 {
		TH1=0xff;				//重装T0值,1ms ,800us
		TL1=0x00;
 }
*/

void INT1_Serv()  interrupt  2 //中断
{
	EA=0;
	if(!KEY)
	{
		Delay_Key(150);
		if(!KEY)
		{
			mode++;
			if(mode==8)
			{mode=1;}
			while(!KEY);
		}
	} 
	EA=1;
}

void TIMER0_ISR()  interrupt  1 //定时器0
{
	TH0=0x00;				//装载初值
	TL0=0x00;

	count[0]++;
	if(count[0]>=64)
	{
		 miao=miao+1;
		 count[0]=0;
		 if(miao>=60)
		 {
		 		fen=fen+1;
				miao=0;
				if(fen>=60)
				{
					shi=shi+1;
					fen=0;
					if(shi>=24)
					{
						shi=0;
					}
				}
		 }
		 count[1]=fen/10;
		 count[2]=fen%10;
		 count[3]=shi/10;
		 count[4]=shi%10;
		 IS3236_DEMO_DISPALY_NUM_CTRL(count[3],count[4],count[1],count[2]);

	}
	else
	{
		if(count[0]<=31)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT18,Gamma_T32[count[0]]);
			IS3236_DataUpdate();
		}
		if(count[0]>31)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT18,Gamma_T32[63-count[0]]);
			IS3236_DataUpdate();
		}
	}

}
void GPIO_Init(void)
{
	P0M1=0XFF;	
	P0M2=0XFF; 
	P1M1=0XFC;	
	P1M2=0XFD;
/*
		PxM1	PxM2
		0			0				标准双向端口
		0			1				推挽输出
		1			0				仅输入，高阻
		1			1				开漏
*/ 
	P0=0XFF;
	P1=0XFF;
}
void INT1_Init(void)
{
	IT1=1;          //外部中断1下降沿触发
	EX1=1;          //开外部中断1
	EA=1;		     		//开总中断
}
void TIMER_Init(void)
{
	TMOD=0x11;			//T0模式选择：模式1
	
	TH0=0x00;				//装载初值
	TL0=0x00;
	
	TR0=1;					//打开定时器T0	
	ET0=0;					//T0中断使能

	TH1=0x00;				//装载初值
	TL1=0x00;
	
	TR1=1;					//打开定时器T0	
	ET1=1;					//T0中断使能
}

void Funtion_Mode_1(void);
void Funtion_Mode_2(void);
void Funtion_Mode_3(void);
void Funtion_Mode_4(void);
void Funtion_Mode_5(void);
void Funtion_Mode_6(void);
void Funtion_Mode_7(void);

void key_delay_int(void)//按键消抖延时  10MS   在中断中使用
{
	UINT8 t,tt;
	for(t=100;t>0;t--)
	for(tt=180;tt>0;tt--);
}

void	Timer1_isr()	interrupt 3   //定时器1中断函数
{
	TH1=0X00;				//重装T0值,20ms
	TL1=0X00;	
	if(EXT_CTRL==1)
	{
		key_delay_int();
		if(EXT_CTRL==1)
		{
			if(mode!=8)
			{
				IS3236_DEMO_LED_SW(S_LED);
				IS3236_Init(0x00);				
				IS_IIC_Write_REG(IS3236_REG_RST,0xff);
				P0M1=0XFF;	
				P0M2=0XFF; 
				P1M1=0XFD;	
				P1M2=0XFD;	
				EX1=0;				//关按键中断
				mode=8;
				IS_SDA_PIN_High();IS_SCL_PIN_High();IS_SDB_PIN_High();
			}
		}	
	}
	else
	{
		P0M1=0XFF;	
		P0M2=0XFF; 
		P1M1=0XFC;	
		P1M2=0XFD;
		EX1=1;		//开按键中断
		if(mode>=8)
		{
			mode=1;
		}
	}
}
void main(void)
{		
	GPIO_Init();
	INT1_Init();
	TIMER_Init();

	mode=9;
	IS_ADR_PIN=0;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0x00);
//	IS3236_DEMO_DISPALY_NUM(8,9,6,7);
	while(1)
	{			 		 
		switch(mode)
		{
			case 1:
			mode_temp=mode;	Funtion_Mode_1();break;
			case 2:
			mode_temp=mode;	Funtion_Mode_2();break;
			case 3:
			mode_temp=mode;	Funtion_Mode_3();break;
			case 4:
			mode_temp=mode;	Funtion_Mode_4();break;
			case 5:
			mode_temp=mode;	Funtion_Mode_5();break;
			case 6:
			mode=7; break;
			case 7:
			mode_temp=mode;	Funtion_Mode_7();break;
			case 8:
			break;
		}		
	}
}
void Funtion_Mode_1(void)
{
	UINT8 com1,com2;
	ET0=0;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0x00);
	IS3236_OUT_SW(0x66,0x98,0x31,0xc3,0x0c);
	while(mode_temp==mode)
	{
	/*
		for(com1=0;com1<64;com1++)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,Gamma_T64[com1]);
			IS3236_DataUpdate();//更新PWM
		}	*/
		for(com2=2;com2>0;com2--)
		{
			for(com1=0;com1<24;com1++)
			{
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM1[com1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM1[com1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM1[com1+1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM1[com1+1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM1[com1+2]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM1[com1+2]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM1[com1+3]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM1[com1+3]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM1[com1+4]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM1[com1+4]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM1[com1+5]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM1[com1+5]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM1[com1+6]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM1[com1+6]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM1[com1+7]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM1[com1+7]);
				IS3236_DataUpdate();//更新PWM
				if(mode_temp!=mode)break;
				Delay_ms(4);
			}
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
		}
	}
}
void Funtion_Mode_2(void)
{
	UINT8 com1,com2;
	ET0=0;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0x00);
	IS3236_OUT_SW(0x66,0x98,0x31,0xc3,0x0c);
	while(mode_temp==mode)
	{
	/*
		for(com1=0;com1<64;com1++)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,Gamma_T64[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,Gamma_T64[com1]);
			IS3236_DataUpdate();//更新PWM
		}	*/
		for(com2=2;com2>0;com2--)
		{
			for(com1=0;com1<24;com1++)
			{
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM1[com1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM1[com1+7]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM1[com1+1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM1[com1+6]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM1[com1+2]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM1[com1+5]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM1[com1+3]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM1[com1+4]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM1[com1+4]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM1[com1+3]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM1[com1+5]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM1[com1+2]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM1[com1+6]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM1[com1+1]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM1[com1+7]);
				IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM1[com1]);
				IS3236_DataUpdate();//更新PWM
				if(mode_temp!=mode)break;
				Delay_ms(4);
			}
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
			Delay_ms(10);
			if(mode_temp!=mode)break;
		}
	}	
}

void Funtion_Mode_3(void)
{
	UINT8 com1;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0xFF);
	IS3236_DEMO_DISPALY_NUM_CTRL(0,0,0,0);
	ET0=1;					     //T0中断使能
	while(mode_temp==mode)
	{
		for(com1=0;com1<255;com1++)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT1,PWM5[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM5[com1]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM5[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT5,PWM5[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM5[com1+4]);
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT8,PWM5[com1+4]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT4,PWM5[com1+8]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM5[com1+8]);
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT9,PWM5[com1+8]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM5[com1+8]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT11,PWM5[com1+8]);
	
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT10,PWM5[com1+12]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM5[com1+12]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT15,PWM5[com1+12]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM5[com1+12]);
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT19,PWM5[com1+12]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT14,PWM5[com1+16]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM5[com1+16]);
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT19,PWM5[com1+16]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM5[com1+16]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT20,PWM5[com1+16]);
	
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT19,PWM5[com1+20]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM5[com1+20]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT24,PWM5[com1+20]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM5[com1+20]);
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT27,PWM5[com1+20]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT23,PWM5[com1+24]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM5[com1+24]);
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT28,PWM5[com1+24]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT30,PWM5[com1+24]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM5[com1+24]);
	
	//		IS_IIC_Write_REG(IS3236_REG_PWM_OUT29,PWM5[com1+28]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM5[com1+28]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT34,PWM5[com1+28]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM5[com1+28]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT33,PWM5[com1+32]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM5[com1+32]);
			IS3236_DataUpdate();//更新PWM
			Delay_ms(2);
			if(mode_temp!=mode)break;
		}
	}	
}
void Funtion_Mode_4(void)
{
	UINT8 com1;
	ET0=0;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0x00);
	IS3236_OUT_SW(0x66,0x98,0x31,0xc3,0x0c);
	while(mode_temp==mode)
	{
	
		for(com1=0;com1<36;com1++)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM2[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM2[com1+3]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM2[com1+3]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM2[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM2[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM2[com1+1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM2[com1+1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM2[com1]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM2[com1+1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM2[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM2[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM2[com1+1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM2[com1+3]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM2[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM2[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM2[com1+3]);
			IS3236_DataUpdate();//更新PWM
			Delay_ms(4);
			if(mode_temp!=mode)break;
		}	
	}
}
void Funtion_Mode_5(void)
{
	UINT8 com1;
	ET0=0;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0x00);
	while(mode_temp==mode)
	{	
		for(com1=0;com1<58;com1++)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT1,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM3[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT4,PWM3[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT5,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM3[com1+4]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT11,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM3[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT14,PWM3[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT15,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM3[com1+6]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT20,PWM3[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM3[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT23,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT24,PWM3[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM3[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM3[com1+2]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT30,PWM3[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM3[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT33,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT34,PWM3[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM3[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM3[com1]);
			IS3236_DataUpdate();//更新PWM
			Delay_ms(4);
			if(mode_temp!=mode)break;
		}	
	}
}
/*
void Funtion_Mode_6(void)
{
	UINT8 com1;
	ET0=0;
	IS3236_DEMO_LED_SW(S_LED);
	IS3236_Init(0x00);
	while(mode_temp==mode)
	{	
		for(com1=0;com1<74;com1++)
		{
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT1,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM4[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT4,PWM4[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT5,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM4[com1+4]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT11,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM4[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT14,PWM4[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT15,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM4[com1+6]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT20,PWM4[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM4[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT23,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT24,PWM4[com1+2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM4[com1+4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM4[com1+2]);

			IS_IIC_Write_REG(IS3236_REG_PWM_OUT30,PWM4[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM4[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT33,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT34,PWM4[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM4[com1+6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM4[com1]);
			IS3236_DataUpdate();//更新PWM
			if(mode_temp!=mode)break;
		//	Delay_ms(2);
		}	
	}
}*/
void Funtion_Mode_7(void)
{
	UINT8 com1;
	UINT8 x=128;
	UINT8 y=64;
	UINT8 z=8;
	ET0=0;
	IS3236_DEMO_LED_SW(RGB_LED);
	IS3236_Init(0x00);
	while(mode_temp==mode)
	{
		for(com1=0;com1<196;com1++)
		{	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT1,PWM_RGB[com1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT2,PWM_RGB[com1+x]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT3,PWM_RGB[com1+y]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT4,PWM_RGB[com1+z*1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT5,PWM_RGB[com1+x+z*1]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT6,PWM_RGB[com1+y+z*1]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT7,PWM_RGB[com1+z*2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT8,PWM_RGB[com1+x+z*2]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT9,PWM_RGB[com1+y+z*2]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT10,PWM_RGB[com1+z*3]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT11,PWM_RGB[com1+x+z*3]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT12,PWM_RGB[com1+y+z*3]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT13,PWM_RGB[com1+z*4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT14,PWM_RGB[com1+x+z*4]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT15,PWM_RGB[com1+y+z*4]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT16,PWM_RGB[com1+z*5]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT17,PWM_RGB[com1+x+z*5]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT18,PWM_RGB[com1+y+z*5]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT19,PWM_RGB[com1+z*6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT20,PWM_RGB[com1+x+z*6]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT21,PWM_RGB[com1+y+z*6]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT22,PWM_RGB[com1+z*7]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT23,PWM_RGB[com1+x+z*7]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT24,PWM_RGB[com1+y+z*7]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT25,PWM_RGB[com1+z*8]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT26,PWM_RGB[com1+x+z*8]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT27,PWM_RGB[com1+y+z*8]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT28,PWM_RGB[com1+z*9]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT29,PWM_RGB[com1+x+z*9]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT30,PWM_RGB[com1+y+z*9]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT31,PWM_RGB[com1+z*10]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT32,PWM_RGB[com1+x+z*10]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT33,PWM_RGB[com1+y+z*10]);
	
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT34,PWM_RGB[com1+z*11]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT35,PWM_RGB[com1+x+z*11]);
			IS_IIC_Write_REG(IS3236_REG_PWM_OUT36,PWM_RGB[com1+y+z*11]);
	
			IS3236_DataUpdate();//更新PWM	
			if(mode_temp!=mode)break;
		}	
	}
}
