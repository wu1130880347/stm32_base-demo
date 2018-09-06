#include "xshell_cmd.h"
#include "usart.h"
#include "string.h"
#include "myiic.h"
#include "app_task.h"

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

#if (defined XSHELL_SUPPORT) && (XSHELL_SUPPORT == TRUE)


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

const char str_help[] = "\r\n cmd : iic_dection! or iic_dection    IIC探测工具  \
                         \r\n cmd : help! or help                  使用帮助     ";

 const u8 cmd_clear[] = {0x1b,0x5b,0x48,0x1b,0x5b,0x4a,0x00};
 const u8 cmd_del_byte[] = {0x08,0x00};
 const u8 cmd_con[] = "\r\nCmd Console : ";
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int analysis_cmd(u8 Res);
u8 send_cmd_console(const u8 * send_cmd);
u8 do_cmd(u8 *str);
//char pre_cmd[128] = {0};
//u16 console_flag = 0;

void work_help(void);
void console_task(void *pdata);

void console_task(void *pdata)
{
	while(1)
	{
		
		if(USART_RX_STA)
		{

			//strcpy(pre_cmd,(const char *)USART_RX_BUF);
			do_cmd(USART_RX_BUF);
			USART_RX_STA = 0;
			send_cmd_console(cmd_con);          //向显示台显示命令
		}
		/*
		else if(console_flag & 0x0001)
		{
			console_flag &= 0xfffe;
			USART_RX_STA = sizeof(pre_cmd) + 1;
            send_cmd_console((const u8 *)USART_RX_BUF);
		}
		*/
		else
		{
			send_cmd_console(cmd_con);          //向显示台显示命令
		} 
		
		OSTaskSuspend(CONSOLE_TASK_PRIO);	 //挂起任务，等下一次收到数据
	}
	
}


int analysis_cmd(u8 Res)
{
	usart1_send_char(Res);
    			if(Res == 0x0c)
				{
					send_cmd_console(cmd_clear);   //清屏指令
					send_cmd_console("Cmd Console :");
				}
				else if(Res == '!')
				{
                    USART_RX_BUF[USART_RX_STA] = '\0';
#if (defined XSHELL_SUPPORT) && (XSHELL_SUPPORT == TRUE)
                  	OSTaskResume(CONSOLE_TASK_PRIO);
#endif	
					return 0;
				}
				else if(Res == 0x0d)
				{
					USART_RX_BUF[USART_RX_STA] = '\0';
#if (defined XSHELL_SUPPORT) && (XSHELL_SUPPORT == TRUE)
                  	OSTaskResume(CONSOLE_TASK_PRIO);
#endif
					return 0;
				}
				/*
				else if(Res == 0x5b && USART_RX_BUF[USART_RX_STA&0x3fff - 1] == 0x1b)
				{
					
                    console_flag |= 0x0001;
					strcpy((char *)USART_RX_BUF,(const char *)pre_cmd);
					//printf("pre_cmd = %s\r\n",pre_cmd);
					USART_RX_STA = 0;
					OSTaskResume(CONSOLE_TASK_PRIO);
				}
				*/
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
				}
						 
	return 0;
}

void work_help(void)
{
      printf(str_help);
}

u8 do_cmd(u8 *str)
{
  if(strcmp((char *)str,"iic_dection") == 0)test_i2c();
  else if(strcmp((char *)str,"help") == 0)work_help();
  else printf("\r\nInput error ...  Please Input \"help!\" to get infomation...");
  return 0;
}

u8 send_cmd_console(const u8 * send_cmd)
{
	while(*(send_cmd))
		usart1_send_char(*(send_cmd++));
	if(*send_cmd == 0)
	return 1;
	return 0;
}

#endif