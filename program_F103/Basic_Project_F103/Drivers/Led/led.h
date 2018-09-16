#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "boards.h"

#if defined LED_GPIOA
#define LED0 PAout(LED0_PIN)
#endif

#if defined LED_GPIOB
#define LED0 PBout(LED0_PIN)
#endif

#if defined LED_GPIOC
#define LED0 PCout(LED0_PIN)
#endif


void LED_Init(void);//≥ı ºªØ

		 				    
#endif
