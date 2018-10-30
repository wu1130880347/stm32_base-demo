#include "bsp_board_test.h"
#include "Led.h"
#include "buzzer.h"

void bsp_init(void);


void bsp_init(void)
{
    LED_Init();
    buzzer_Init();
}
