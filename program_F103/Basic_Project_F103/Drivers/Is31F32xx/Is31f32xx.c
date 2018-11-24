#include "Is31f32xx.h"
#include "myiic.h"
#include <string.h>

u8 is31f_args[79] = {0};
Is31f32xx st3236;

u8 Is31f32xx_Init(void);
u8 Is31f32xx_SetMode(void *arg);
u8 Is31f32xx_Enable(void *arg);
u8 Is31f32xx_Normal(void *arg);

u8 Is31f32xx_Init(void)
{
    u8 i = 0;
    if (!(IIC_Detection(IS31F3236_SLAVE_ADDR)))
    {
        memset(is31f_args, 0x00, sizeof(is31f_args));
        is31f_args[0] = 1;
        for(i = 1;i <= 0x24;i++)is31f_args[i] = 0xff;
        is31f_args[0x25] = 0;
        for(i = 0x26;i <= 0x49;i++)is31f_args[i] = 0x03;
        is31f_args[0x4a] = 0;
        is31f_args[0x4b] = 1;
        st3236.regs = is31f_args;
        IIC_Write_n_Byte(IS31F3236_SLAVE_ADDR, 0x00, st3236.regs, sizeof(is31f_args)-3);
        Dprintf(IS31F32XX_SUPPORT, "is31f32xx init successful\r\n");
    }
    else
    {
        Dprintf(IS31F32XX_SUPPORT, "is31f32xx is not exist\r\n");
        return FALSE;
    }
    return TRUE;
}
