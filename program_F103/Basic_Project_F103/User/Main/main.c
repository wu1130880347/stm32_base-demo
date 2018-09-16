#include "main.h"
#include "myiic.h"



int main(void)
{
  Init_System();        //配置时钟，初始化硬件
  usart_init(115200);      //配置波特率为115200
  delay_init(72);         //配置tick


  Dprintf(SYS_TRACE,"\r\n/**************************/ \r\n");
  Dprintf(SYS_TRACE,"my system ready to start... \r\n");
  Dprintf(SYS_TRACE,"Welcome to use this system... \r\n");
  Dprintf(SYS_TRACE,"This system version is V1.0 \r\n");
  Dprintf(SYS_TRACE,"Next to run uCosII... \r\n");
  Dprintf(SYS_TRACE,"/**************************/ \r\n");
  bsp_init();
  Dprintf(SYS_TRACE,"bsp_init is successful \r\n");
  
  OLED_Init();
  Dprintf(SYS_TRACE,"OLED_Init is successful\r\n");
 #if (defined XSHELL_SUPPORT) && (XSHELL_SUPPORT == TRUE)
  xshell_init();
 #endif
   
  OSInit(); 
  Dprintf(SYS_TRACE,"OSInit is successful\r\n");  
  Init_Task();
  OSStart();

  while (1);
}

