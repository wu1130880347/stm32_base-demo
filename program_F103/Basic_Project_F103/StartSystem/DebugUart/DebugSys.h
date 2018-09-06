#ifndef __DEBUGSYS__
#define __DEBUGSYS__

#include "sys.h"

#if (defined DEBUG_UART) && (DEBUG_UART == TRUE)

extern u8 Dprintf(u8 enable_flag,const char *format, ...);

#endif



#endif