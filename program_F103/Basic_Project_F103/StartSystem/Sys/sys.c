#include "sys.h"
void Init_System(void);


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//ϵͳ�жϷ������û�		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/10
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************  
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  


void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
 void MSR_MSP(u32 addr) 
{
    __ASM volatile("MSR MSP, r0");			//set Main Stack value
    __ASM volatile("BX r14");
}

void My_SystemReset(void)
{
    __ASM volatile("msr faultmask, r0");
    __ASM volatile("MOV R0, #1");
    __ASM volatile("MSR FAULTMASK, R0");
    __ASM volatile("LDR R0, =0xE000ED0C");
    __ASM volatile("LDR R1, =0x05FA0004");
    __ASM volatile("STR R1, [R0]");

    while(1);
}


void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
} 

/*RCC config*/
void Init_System(void)
{
    RCC_DeInit();  
    RCC_HSEConfig(RCC_HSE_ON);
    while(SUCCESS != RCC_WaitForHSEStartUp()){} 
    /*����FLASH�洢����ʱʱ��������*/
    FLASH_SetLatency(FLASH_Latency_2);    //FLASH_Latency_2  2��ʱ���� 
    /*ѡ��FLASHԤȡָ�����ģʽ*/ 
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);     // Ԥȡָ����ʹ��
    /*����PLLʱ��Դ����Ƶϵ��*/  
    /* Fcpu = (PLL_src * PLL_MUL) = (8 Mhz / 1) * (9) = 72Mhz   */ 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);            
    /* Enable PLL */
    RCC_PLLCmd(ENABLE); 
     /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/    
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
    /* Set system clock dividers */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);   
    /* Embedded Flash Configuration */
    FLASH_SetLatency(FLASH_Latency_2);                           
    FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    /*SYSCLK configuration*/
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);       //�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE);

   __disable_irq();    //�ر��ж�
}