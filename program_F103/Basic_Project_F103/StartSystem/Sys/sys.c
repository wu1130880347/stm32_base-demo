#include "sys.h"
void Init_System(void);


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//系统中断分组设置化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/10
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************  
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  


void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
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
    /*设置FLASH存储器延时时钟周期数*/
    FLASH_SetLatency(FLASH_Latency_2);    //FLASH_Latency_2  2延时周期 
    /*选择FLASH预取指缓存的模式*/ 
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);     // 预取指缓存使能
    /*设置PLL时钟源及倍频系数*/  
    /* Fcpu = (PLL_src * PLL_MUL) = (8 Mhz / 1) * (9) = 72Mhz   */ 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);            
    /* Enable PLL */
    RCC_PLLCmd(ENABLE); 
     /*检查指定的RCC标志位(PLL准备好标志)设置与否*/    
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

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);       //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,DISABLE);

   __disable_irq();    //关闭中断
}