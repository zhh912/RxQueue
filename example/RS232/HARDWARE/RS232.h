#ifndef __RS232_H
#define __RS232_H
#include "sys.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"


/*
Initialize RS232 Port
*/
void RS232_2_Init(unsigned	int	bps);
void RS232_5_Init(unsigned	int	bps);
void RS232_7_Init(unsigned	int	bps);
void RS232_8_Init(unsigned	int	bps);

void  RS232_2_Send(unsigned char  *temp,unsigned  short len);
void  RS232_5_Send(unsigned char  *temp,unsigned  short len);
void  RS232_7_Send(unsigned char  *temp,unsigned  short len);
void  RS232_8_Send(unsigned char  *temp,unsigned  short len);


#endif

/**/

