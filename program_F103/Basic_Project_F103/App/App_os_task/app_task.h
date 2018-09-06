#ifndef __APP_TASK__
#define __APP_TASK__

#include "main.h"
#include "sys.h"

//usart Control Console 任务
//设置任务优先级
#define CONSOLE_TASK_PRIO      		1 //开始任务的优先级设置为最高
//设置任务堆栈大小
#define CONSOLE_STK_SIZE  				2048


extern void start_task(void *pdata);
extern void Init_Task(void);

#endif