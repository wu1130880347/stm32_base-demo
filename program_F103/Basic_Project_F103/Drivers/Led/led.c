#include "led.h"
#include "boards.h"
   
	    
//LED IO初始化
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
 	
    RCC_APB2PeriphClockCmd(LED_RCC_SOURCE, ENABLE);	 
	
     GPIO_InitStructure.GPIO_Pin = LED0_PIN_MASK;				 //端口配置
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
     GPIO_Init(LED0_PIN_SOURCE, &GPIO_InitStructure);		//根据设定参数初始化
     GPIO_SetBits(LED0_PIN_SOURCE,LED0_PIN_MASK);				// 输出高
}
 
