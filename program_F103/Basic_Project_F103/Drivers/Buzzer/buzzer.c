#include "buzzer.h"
#include "boards.h"

void buzzer_Init(void);   
void TIM23_PWM_Init(u16 freq1,u8 duty1,u16 freq2,u8 duty2);
	    
//LED IO初始化
void buzzer_Init(void)
{
    TIM23_PWM_Init(0,0,0,0);
}

//TIM2 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM23_PWM_Init(u16 freq1,u8 duty1,u16 freq2,u8 duty2)
{
	static u8 flag_one = 1;
	u16 temp = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(flag_one)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
		
		//PIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
	
		//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6; //TIM_CH2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO

	
		//初始化TIM3
		TIM_TimeBaseStructure.TIM_Period = 1000; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
		TIM_TimeBaseStructure.TIM_Prescaler =36-1; //设置用来作为TIMx时钟频率除数的预分频值 
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

		//初始化TIM3
		TIM_TimeBaseStructure.TIM_Period = 4000; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
		TIM_TimeBaseStructure.TIM_Prescaler =36000-1; //设置用来作为TIMx时钟频率除数的预分频值 
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
		
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
		
		//初始化TIM3 Channel2 PWM模式	 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高

		TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
		TIM_SetCompare2(TIM2,1000/2);

		TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
		TIM_SetCompare1(TIM3,4000/2);
				
		TIM_Cmd(TIM2, DISABLE);  //使能TIM3
		TIM_Cmd(TIM3, DISABLE);
		flag_one = 0;
	}
else 
	{
		if(freq1 == 0 && freq2 == 0 && duty1 == 0 && duty1 == 0)
		{
			TIM_Cmd(TIM2, DISABLE);  //使能TIM3
			TIM_Cmd(TIM3, DISABLE);

			//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6; //TIM_CH2
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
			PAout(1) = 0;
			PAout(6) = 0;
			return ;
		}
		//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_6; //TIM_CH2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
		
		printf("\r\n %d  %d  %d  %d",freq1,freq2,duty1,duty2);
		TIM_Cmd(TIM2, DISABLE);  //使能TIM3
		TIM_Cmd(TIM3, DISABLE);

		temp = 2000000/freq1;
		printf("\r\nbuzzer freq = %dhz",freq1);
		TIM_SetAutoreload(TIM2,temp);
		TIM_PrescalerConfig(TIM2,36-1,TIM_PSCReloadMode_Immediate);
		TIM_SetCompare2(TIM2,temp * duty1 / 100);

		temp = 20000/freq2;
		printf("\r\npower freq = %d*mhz",freq2*100);
		TIM_SetAutoreload(TIM3,temp);
		TIM_PrescalerConfig(TIM3,36000-1,TIM_PSCReloadMode_Immediate);
		TIM_SetCompare1(TIM3,temp * duty2 / 100);
		

		TIM_Cmd(TIM2, ENABLE);  //使能TIM2
		TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	}
	return ;
}
 
