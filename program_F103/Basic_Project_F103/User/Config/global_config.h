#ifndef __GLOBAL_CONFIG__
#define __GLOBAL_CONFIG__

#define TRUE     1
#define FALSE    0
//#define NULL     0
#define USE_FULL_ASSERT


#ifndef __ICCARM__
#define  __ICCARM__        //IAR下使�?  
#endif

#define DEBUG_UART TRUE
#define SYS_TRACE TRUE


//Condif for The ST FWLIB   default use all
#define __INIT_ADC__        TRUE
#define __INIT_BKP__        TRUE
#define __INIT_CAN__        TRUE
#define __INIT_CEC__        TRUE
#define __INIT_CRC__        TRUE
#define __INIT_DAC__        TRUE
#define __INIT_DBGMCU__     TRUE
#define __INIT_DMA__        TRUE
#define __INIT_EXIT__       TRUE
#define __INIT_FLASH__      TRUE
#define __INIT_FSMC__       TRUE
#define __INIT_GPIO__       TRUE
#define __INIT_I2C__        TRUE
#define __INIT_IWDG__       TRUE
#define __INIT_PWR__        TRUE
#define __INIT_RCC__        TRUE
#define __INIT_RTC__        TRUE
#define __INIT_SDIO__       TRUE
#define __INIT_SPI__        TRUE
#define __INIT_TIM__        TRUE
#define __INIT_USART__      TRUE
#define __INIT_WWDG__       TRUE


//Config ThiredParty Tools For Now Project



//Config IIC Mode
#define SOFT_IIC TRUE
#define HARD_IIC FALSE

//Config OLED USE Mode
#define OLED_RAM FALSE
#define OLED_PICTURE FALSE
#define OLED_CHINESE FALSE
#define OLED_NORMAL TRUE

#define XSHELL_SUPPORT TRUE

//Config This Project Applied to The Board



//Config This Project Now Revsion 


 
#define a b

#define a b

#define a b


#endif