#include "xshell_cmd.h"

u16 strToint(u8 * str);
u8 find_para(u8* data,u16* para);

u8 find_para(u8* data,u16* para)
{
    u8 fg_num = 0;
    u8 i = 0, j = 0, k = 0;
    u8 temp[32-1] = {0};
    while(*data)
    {
        if(*data == ' ')
        {
            fg_num = 0;
            k = 0;
            temp[j] = 0;
            j = 0;
            if(*temp)
            {
                if(i >= 1)
                {
                	*(para + i - 1) = strToint(temp);
				}
				i++;
                if(i > 4) return 0; 
            }   
        }
        else
        {
            if(fg_num == 0 || k == 1)
            {
                temp[j++] = *data;
                k = 1;
            }
            fg_num = 1;
        }
        data++;
        if(*data == 0)
       	{
       		 temp[j] = 0;
       		 *(para + i - 1) = strToint(temp);
		}
        
    }
    if(i < 4)
    {
        for(;i<4;i++)
            *(para + i) = 0;
        return 0;
    }

    return -1;
}


u16 strToint(u8 * str)
{
    u16 temp = 0;
    while(*str)
    {
    	if(*str >='0' && *str <= '9')
        temp = temp * 10 + *str - '0';
        str++;
    }
    return temp;
}