#include "led.h"
#include "boards.h"
   
	    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
 	
    RCC_APB2PeriphClockCmd(LED_RCC_SOURCE, ENABLE);	 
	
     GPIO_InitStructure.GPIO_Pin = LED0_PIN_MASK;				 //�˿�����
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
     GPIO_Init(LED0_PIN_SOURCE, &GPIO_InitStructure);		//�����趨������ʼ��
     GPIO_SetBits(LED0_PIN_SOURCE,LED0_PIN_MASK);				// �����
}
 
