#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

/*
Drive	LED	ON	defination
*/
#define M_LED1_ON			PFout(11)=0
#define M_LED2_ON			PFout(12)=0
#define M_LED3_ON			PFout(13)=0
#define M_LED4_ON			PFout(14)=0
#define M_LED5_ON			PFout(15)=0
#define M_LED6_ON			PGout(0) =0
#define M_LED7_ON			PGout(1) =0
#define M_LED8_ON			PEout(7) =0
#define	M_LED_ALL_ON	M_LED1_ON;M_LED2_ON;M_LED3_ON;M_LED4_ON;M_LED5_ON;M_LED6_ON;M_LED7_ON;M_LED8_ON

/*
Drive	LED	OFF	defination
*/
#define M_LED1_OFF		PFout(11)=1
#define M_LED2_OFF		PFout(12)=1
#define M_LED3_OFF		PFout(13)=1
#define M_LED4_OFF		PFout(14)=1
#define M_LED5_OFF		PFout(15)=1
#define M_LED6_OFF		PGout(0) =1
#define M_LED7_OFF		PGout(1) =1
#define M_LED8_OFF		PEout(7) =1
#define	M_LED_ALL_OFF	M_LED1_OFF;M_LED2_OFF;M_LED3_OFF;M_LED4_OFF;M_LED5_OFF;M_LED6_OFF;M_LED7_OFF;M_LED8_OFF

/*
Initialize LED Port
*/
void LED_Init(void);//≥ı ºªØ		 				    
#endif

/**/

