#include "lcd_12864.h"

#if (defined OLED_NORMAL) && (OLED_NORMAL == TRUE)

#include "font.h"
#include "math.h"
#include "myiic.h"

extern void IIC_Init(void);					//IIC�ӿ�ʵ��
extern u8 IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);

#endif

/**********************************************
//IIC Start
**********************************************/

#if (defined OLED_PICTURE) && (OLED_PICTURE == TRUE)

#include "picture.h"



/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		Write_IIC_Command(0xb0+m);		//page0-page1
		Write_IIC_Command(0x00);		//low column start address
		Write_IIC_Command(0x10);		//high column start address
		for(n=0;n<132;n++)
			{
				Write_IIC_Data(fill_Data);
			}
	}
}
/******************************************
// picture������ʾһ��ͼƬ
******************************************/

void Picture()
{
  unsigned char x,y;
  unsigned int i=0;
  for(y=0;y<8;y++)
    {
      Write_IIC_Command(0xb0+y);
      Write_IIC_Command(0x0);
      Write_IIC_Command(0x10);
      for(x=0;x<132;x++)
        {
          Write_IIC_Data(show[i++]);
        }
    }
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP1)
{
 unsigned int j=0;
 unsigned char x,y;

  if(y1%8==0) y=y1/8;
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {
	    	OLED_WR_Byte(BMP_0[BMP1][j++],OLED_DATA);
	    }
	}
}
#endif







//����
//x:0~127
//y:0~63
//t:1 ��� 0,���
#if (defined OLED_RAM) && (OLED_RAM == TRUE)

void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 t);
void OLED_Refresh_Gram(void);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);

 //OLED���Դ�    1k Byte
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
u8 OLED_GRAM[128][8];

void OLED_DrawPoint(u8 x,u8 y,u8 t)
{

	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;

}

void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 t)
{
   u8 i = 0;
   if(!(y1-y2))
   for(i=x1;i<=x2;i+=t)
	 OLED_DrawPoint(i,y1,1);
   else for(i=y1;i<=y2;i+=t)OLED_DrawPoint(x1,i,1);

}


//�����Դ浽LCD
void OLED_Refresh_Gram(void)
{

	u8 i,n;
	for(i=0;i<8;i++)
	{

	OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
	OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�èD�е͵�ַ
	OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�èD�иߵ�ַ
	for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);

	}

}

//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63
//dot:0,���;1,���
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{

u8 x,y;
for(x=x1;x<=x2;x++)
{

for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);

}
OLED_Refresh_Gram();//������ʾ

}
#endif



#if (defined OLED_CHINESE) && (OLED_CHINESE == TRUE)
//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{
	u8 t,adder=0;
	OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }
		OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
			{
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }
}

#endif

//��ʼ��SSD1306

#if (defined OLED_NORMAL) && (OLED_NORMAL == TRUE)


void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);

void OLED_Init(void);
void OLED_Clear(void);

void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_Show0Num(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowFloat(u8 x,u8 y,float num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);

/**********************************************
// IIC Write byte
**********************************************/

void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
		IIC_Write_One_Byte(0x78,0x40,dat);
	else 
		IIC_Write_One_Byte(0x78,0x00,dat);
}



//��������

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
  OLED_WR_Byte(0xb0+y,OLED_CMD);
  OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
  OLED_WR_Byte((x&0x0f),OLED_CMD);
}
//����OLED��ʾ
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
	} //������ʾ
}
void OLED_On(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA);
	} //������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ
//size:ѡ������ 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
	unsigned char c=0,i=0;
		c=chr-' ';//�õ�ƫ�ƺ��ֵ
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);

			}
}

//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;
	return result;
}
u8 oled_len(u32 n)
{
  u8 num = 0;
  if(n==0)return 1;
  while(n)
  { 
    num++;
    n/=10;
  }
  return num;
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{
	u8 t,temp;
        len = oled_len(num);
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size)*t,y,' ',size);
				continue;
			}else enshow=1;

		}
	 	OLED_ShowChar(x+(size)*t,y,temp+'0',size);
	}
}
//��ʾ32λ��������
void OLED_Show0Num(u8 x,u8 y,u32 num,u8 len,u8 size)
{
	u8 t,temp;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
	 	OLED_ShowChar(x+(size)*t,y,temp+'0',size);
	}
}
//��ʾ32Float����
void OLED_ShowFloat(u8 x,u8 y,float num,u8 len,u8 size)
{
  u8 l_float;
  long f_num;
  f_num = (long)num;
  
  if(num>=0)
  {
    OLED_ShowChar(x,y,' ',8);
    OLED_ShowNum(x+8,y,(u32)num,0,8);
  }
  else 
  {
    OLED_ShowChar(x,y,'-',8);
    num = fabs(num);
    f_num = (long)num;
    OLED_ShowNum(x+8,y,(u32)num,0,8);
  }
  
  l_float = oled_len(f_num);
  if(len)OLED_ShowChar(x+(l_float+1)*8,y,'.',8);
  f_num = (u32)((num - (long)num)*oled_pow(10,len));
  OLED_Show0Num(x+(l_float+2)*8,y,(u32)f_num,len,8);
}

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}


void OLED_Init(void)
{
       //LCD_12864 Control
    IIC_Init();
        OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128
	//OLED_WR_Byte(0xA0,OLED_CMD);//set segment remap
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	//OLED_WR_Byte(0xA7,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	//OLED_WR_Byte(0xC0,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//

	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//

	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//

	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//

	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//

	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//

	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//

	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel

	OLED_Clear();          //cleaning
}
#endif

