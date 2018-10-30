#include "xshell_cmd.h"

u8 find_para(u8* data,u16* para);

u8 find_para(u8* data,u16* para)
{
    while(*(data++))
    {
        if(*data == ' ')
            {
                if(sizeof(data) < 19)
                  return -1;
                continue;
            }
        if(*data < '0' || *data > '9')
            return -1;
        else 
        {
            para[0] = (*data - '0')*10000 + (*(data+1) - '0')*1000 + (*(data+2) - '0')*100 + (*(data+3) - '0')*10 + (*(data+4) - '0');
            para[1] = (*(data+6) - '0')*10000 + (*(data+7) - '0')*1000 + (*(data+8) - '0')*100 + (*(data+9) - '0')*10 + (*(data+10) - '0');
            para[2] = (*(data+12) - '0')*100 + (*(data+13) - '0')*10 + (*(data+14) - '0');
            para[3] = (*(data+16) - '0')*100 + (*(data+17) - '0')*10 + (*(data+18) - '0');
            return 0;
        }
        
    }
    return -1;
}