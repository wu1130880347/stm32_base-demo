#include "bsp_board_test.h"
#include "Led.h"
#include "buzzer.h"
#include "myiic.h"
#include "Is31f32xx.h"

void bsp_init(void);


void bsp_init(void)
{
    LED_Init();
    IIC_Init();
    delay_ms(50);
    Is31f32xx_Init();
   // buzzer_Init();
}
