#include "DebugSys.h"
#include "usart.h"
#include <stdio.h>
#include <stdarg.h>

u8 Dprintf(u8 enable_flag,const char *format, ...);


u8 Dprintf(u8 enable_flag,const char *format, ...)
{
  
#if (defined DEBUG_UART) && (DEBUG_UART == TRUE)
    if(enable_flag)
    {
     va_list args;
     va_start(args, format);
     vprintf(format, args);
     va_end(args);
    }
   else return 1;
#endif
    return 1;
}