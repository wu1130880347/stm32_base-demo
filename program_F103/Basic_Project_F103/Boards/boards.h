#ifndef __BOARDS_H__
#define __BOARDS_H__

//include Target source define 
#include "sys.h"

//GPIO_PIN
#define I2C1_SCL_PIN            6
#define I2C1_SDA_PIN            7
#define LED0_PIN                13


//IIC Source MASK
#define I2C1_RCC_SOURCE         RCC_APB2Periph_GPIOB
#define I2C1_SCL_SOURCE         GPIOB
#define I2C1_SCL_PIN_MASK       (1<<I2C1_SCL_PIN)              //I2C1_SCL    GPIOB->12
#define I2C1_SDA_SOURCE         GPIOB
#define I2C1_SDA_PIN_MASK       (1<<I2C1_SDA_PIN)                   //I2C1_SDA    GPIOB->13


//Boards LED Pin
#define LED_GPIOC
#define LED_RCC_SOURCE               RCC_APB2Periph_GPIOC
#define LED0_PIN_SOURCE              GPIOC 
#define LED0_PIN_MASK                (1<<LED0_PIN)             


#endif