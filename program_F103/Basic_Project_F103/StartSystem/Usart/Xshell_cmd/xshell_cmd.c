#include "xshell_cmd.h"
#include "usart.h"
#include "string.h"
#include "myiic.h"
#include "app_task.h"
#include "buzzer.h"


////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包含下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

#if (defined XSHELL_SUPPORT) && (XSHELL_SUPPORT == TRUE)

/* Private define ------------------------------------------------------------*/

Cmd_list cmd_header ;

const char str_help[] = 
"\r\ncmd : iic_dection! or iic_dection    IIC探测工具\
\r\ncmd : help! or help                  使用帮助\
\r\ncmd : ls! or ls                 get help list\
\r\ncmd : reset! or reset           reset the system\
\r\ncmd : buzzer! or buzzer         play the buzzer\
";

 const u8 cmd_clear[] = {0x1b,0x5b,0x48,0x1b,0x5b,0x4a,0x00};
 const u8 cmd_del_byte[] = {0x08,0x00};
 const u8 cmd_con[] = "\r\nCmd Console : ";
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int analysis_cmd(u8 Res);
u8 xsehll_init(void);
u8 send_cmd_console(const u8 * send_cmd);
u8 do_cmd(u8 *str);
//char pre_cmd[128] = {0};
//u16 console_flag = 0;
u16 work_help(u8* cmd_data);
void console_task(void *pdata);
u16 reset_system(u8* cmd_data);
u16 buzzer(u8* cmd_data);

/* Private typedef -----------------------------------------------------------*/


const cmd_Hander cmd_task_arr[] = 
{
 	test_i2c,				//执行函数位置 1 函数
	work_help,				//执行函数位置 2 函数
	reset_system,			//执行函数位置 3 函数
	buzzer,
};





/********************************
//返回0则成功
********************************/
u8 xshell_init(void)
{
  	u16 cmd_num = 0;
	
	cmd_header.next = NULL;
	cmd_header.cmdStr = NULL;
	cmd_header.index_list = NULL;
	cmd_header.cmd_data = NULL;
	

	cmd_num = sizeof(cmd_task_arr)/4;
	printf("cmd_num = %d \r\n",cmd_num);
    return 0;
}

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
		
		OSTaskSuspend(CONSOLE_TASK_PRIO);	 //挂起任务，等下一次收到数据?
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
					if(Res == 0x7f)
					{
						USART_RX_STA--;
						if((USART_RX_STA&0X3FFF) == 0) USART_RX_BUF[USART_RX_STA&0X3FFF] = 0;
						else USART_RX_BUF[USART_RX_STA&0X3FFF]=Res;
						return 0;
					}
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接?
				}
						 
	return 0;
}

u16 work_help(u8* cmd_data)
{
      printf(str_help);
      return 0;
}

u16 reset_system(u8* cmd_data)
{
	My_SystemReset();
	return 0;
}

u16 buzzer(u8* cmd_data)
{
	//u16 freq1,freq2,duty1,duty2;
	u16 para[] = {0,0,0,0};
	u8 * data = (cmd_data);
	find_para(data,para);
	printf("\r\n %d  %d  %d  %d",para[0],para[1],para[2],para[3]);
	if(para[0] == 1 && para[1] == 1 && para[2] == 1 && para[3] == 1)
	{
		OSTaskResume(14);
		return 0;
	}
	if(para[0] == 1 && para[1] == 1 && para[2] == 1 && para[3] == 0)
	{
		OSTaskSuspend(14);
		return 0;
	}
	TIM23_PWM_Init(para[0],(u8)para[2],para[1],(u8)para[3]);
    return 0;
}

u8 do_cmd(u8 *str)
{
  if(strcmp((char *)str,"iic_dection") == 0)test_i2c("0");
  else if(strcmp((char *)str,"help") == 0)work_help("0");
  else if(strstr((char *)str,"ls") != 0)work_help("0");
  else if(strcmp((char *)str,"reset") == 0)reset_system("0");
  else if(strstr((char *)str,"buzzer") != 0)buzzer(str);
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