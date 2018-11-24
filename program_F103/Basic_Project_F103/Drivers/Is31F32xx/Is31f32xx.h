#ifndef __IS31F32XX_H__
#define __IS31F32XX_H__
#include "sys.h"
typedef struct 
{
    u8 addr;
    u8 *regs;
    u8 work_flag;
}Is31f32xx;
//regs resource
#define IS31F3236_SLAVE_ADDR 0x78

#define IS31F3236_SHUTDOWN 0x00
#define IS31F3236_PWM1 0x01
//...
#define IS31F3236_PWM36 0x24

#define IS31F3236_UP_PWM 0x25

#define IS31F3236_SET_I1 0x26
//...
#define IS31F3236_SET_I36 0x49

#define IS31F3236_ALL_ON 0x4a
#define IS31F3236_SET_PWM 0x4b
#define IS31F3236_RESET 0x4f



//operation funtions
u8 Is31f32xx_Init(void);
u8 Is31f32xx_SetMode(void *arg);
u8 Is31f32xx_Enable(void *arg);
u8 Is31f32xx_Normal(void *arg);




#endif