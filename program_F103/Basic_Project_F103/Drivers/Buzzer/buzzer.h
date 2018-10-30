#ifndef __BUZZER_H
#define __BUZZER_H	 
#include "sys.h"
#include "boards.h"



extern void buzzer_Init(void);

extern void TIM23_PWM_Init(u16 freq1,u8 duty1,u16 freq2,u8 duty2);

		 				    
#endif
