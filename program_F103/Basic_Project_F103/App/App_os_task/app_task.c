#include "app_task.h"
#include "xshell_cmd.h"
#include <math.h>



extern u16 OSCPUUsage;
///////////////////////////UCOSII��������///////////////////////////////////

//START ����
//�����������ȼ�
#define START_TASK_PRIO      		15 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�����ջ	
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);

//usart Control Console ����


//�����ջ	
OS_STK CONSOLE_TASK_STK[CONSOLE_STK_SIZE];
//������
extern void console_task(void *pdata);
 			   
//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO       			7 
//���������ջ��С
#define LED0_STK_SIZE  		    		64
//�����ջ	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);


//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO       			6 
//���������ջ��С
#define LED1_STK_SIZE  					64
//�����ջ
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);


//�����������
#define FLOAT_TASK_PRIO			5
//���������ջ��С
#define FLOAT_STK_SIZE			128
//�����ջ
//���������ʹ��printf����ӡ�������ݵĻ�һ��Ҫ8�ֽڶ���
__attribute__((aligned(8))) OS_STK FLOAT_TASK_STK[FLOAT_STK_SIZE]; 
//������
void float_task(void *pdata);






void Init_Task(void)
{
  OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
}

//��ʼ����
void start_task(void *pdata)
{
        OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	OSStatInit();
  	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);	 				   
	OSTaskCreate(float_task,(void*)0,(OS_STK*)&FLOAT_TASK_STK[FLOAT_STK_SIZE-1],FLOAT_TASK_PRIO);
	OSTaskCreate(console_task,(void*)0,(OS_STK*)&CONSOLE_TASK_STK[CONSOLE_STK_SIZE-1],CONSOLE_TASK_PRIO);
        
    Dprintf(SYS_TRACE,"start_task is successful...\r\n");
                
  	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.  
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)


}



unsigned char flag_use = 1; 


//LED0����
void led0_task(void *pdata)
{	 	
  int tt = 10;
	while(1)
	{
          if(flag_use == 1)
          {
            for(tt = 10;tt>0;tt--)
            {
                LED0=0;
		        delay_ms(10);
		        LED0=1;
		        delay_ms(90);
            }
            flag_use = 2;
          }
          delay_ms(2);
	};
}

//LED1����
void led1_task(void *pdata)
{	
    int tt = 5;  
	while(1)
	{
          if(flag_use == 2)
          {
            for(tt = 5;tt>0;tt--)
            {
                    LED0=0;
		            delay_ms(200);
		            LED0=1;
		            delay_ms(200);
						
            }
            flag_use = 1;
          }
          delay_ms(4);
	};
}

//�����������
void float_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	static float float_num=0.01;
	//static u8 i = 0, j = 0;
	while(1)
	{
		float_num+=0.01f;
		OS_ENTER_CRITICAL();	//�����ٽ���(�ر��ж�)
		//printf("float_num ��ֵΪ: %f\r\n",float_num); //���ڴ�ӡ���
	//	printf("receive : %s  \r\n",USART_RX_BUF);
		//if((USART_RX_STA & 0x8000) != 0)
		//{
			//i = (USART_RX_STA & 0x00ff);
			//printf("receive :"); 
			//for(j = 0;j<i;j++)
			//printf("%c",USART_RX_BUF[j]);
		//	printf("\r\n");
		//	USART_RX_STA = 0;
		//}
		//printf("Cpu usage : %% %.1f \r\n",(float)OSCPUUsage/10);
		OLED_ShowString(0,7,"CPU_usage:      ",8);
		OSCPUUsage = ((short)OSCPUUsage>=0)?OSCPUUsage:(0xffff - OSCPUUsage);
		OLED_ShowNum(80,7,OSCPUUsage,0,8);
		OS_EXIT_CRITICAL();		//�˳��ٽ���(���ж�)
		delay_ms(500);
	}
}





