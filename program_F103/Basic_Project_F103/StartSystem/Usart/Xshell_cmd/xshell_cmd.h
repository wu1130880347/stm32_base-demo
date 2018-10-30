#ifndef __XSHELL_CMD__
#define __XSHELL_CMD__

#include "sys.h"
#include "global_config.h"


extern u8 play_buzzer;    //����������

//clear xshell
extern int analysis_cmd(u8 Res);
extern u8 do_cmd(u8 *str);
extern void console_task(void *pdata);
extern u8 xshell_init(void);

extern u8 find_para(u8* data,u16* para);

/* Exported define -----------------------------------------------------------*/
//�����б���
typedef struct 
{
	u8 cmdStr;				//��������
	u8 cmd_data;				//�������
	int index_list;			//ִ�к���λ��
	 int next;			//�����б�ָ��

}Cmd_list;

//ִ�к���ָ��
typedef unsigned short (*cmd_Hander)( u8* cmdStr);
extern const cmd_Hander cmd_task_arr[];



 /* USE_STM324x9I_EVAL */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
	 
#endif