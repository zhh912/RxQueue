#include "RS232.h" 






/*
**************************************************************************************************
DESCRIPATION:
              initialize the UARTx  with bound per second 'bps'

INPUT	  DATA:
              bound per second 'bps'

OUTPUT	DATA:
              NONE

RETURN	DATA:
              NONE
              
NOTES		    :


**************************************************************************************************
*/
void  RS232_2_Init(unsigned int bps)
{
   //GPIO???迆谷豕??
	GPIO_InitTypeDef 	  GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	  NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//那1?邦USARTx那㊣?車	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 
	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); 
	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6; //
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//?∩車?1|?邦
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//?迄?豕100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //赤?赤足?∩車?那?3?
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //谷?角-
	GPIO_Init(GPIOD,&GPIO_InitStructure); //

  
	USART_InitStructure.USART_BaudRate            = bps;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(USART2, &USART_InitStructure); 
	
	USART_Cmd(USART2, ENABLE);   
	

	
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//?a???角1??D??

	//Usartx NVIC ????
	NVIC_InitStructure.NVIC_IRQChannel                    = USART2_IRQn;//∩??迆x?D??赤“米角
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;//?角??車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;		//℅車車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;			//IRQ赤“米角那1?邦
	NVIC_Init(&NVIC_InitStructure);	//?迄?Y???“米?2?那y3?那??‘VIC??∩??¯?⊿

	USART_ClearFlag(USART2, USART_FLAG_TC);	

}
//


/*
**************************************************************************************************
DESCRIPATION:
              initialize the UARTx  with bound per second 'bps'

INPUT	  DATA:
              bound per second 'bps'

OUTPUT	DATA:
              NONE

RETURN	DATA:
              NONE
              
NOTES		    :


**************************************************************************************************
*/
void  RS232_5_Init(unsigned int bps)
{
	GPIO_InitTypeDef 	  GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	  NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC	|	RCC_AHB1Periph_GPIOD,ENABLE); 
	

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5); 
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5); 
	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; 
	GPIO_Init(GPIOC,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; 
	GPIO_Init(GPIOD,&GPIO_InitStructure); 

	USART_InitStructure.USART_BaudRate            = bps;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	
	USART_Init(UART5, &USART_InitStructure); 
	
	USART_Cmd(UART5, ENABLE);   
	

	
	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);

	
	NVIC_InitStructure.NVIC_IRQChannel                    = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	USART_ClearFlag(UART5, USART_FLAG_TC);	
		  
}
//


/*
**************************************************************************************************
DESCRIPATION:
              initialize the UARTx  with bound per second 'bps'

INPUT	  DATA:
              bound per second 'bps'

OUTPUT	DATA:
              NONE

RETURN	DATA:
              NONE
              
NOTES		    :


**************************************************************************************************
*/
void  RS232_7_Init(unsigned int bps)
{
   //GPIO???迆谷豕??
	GPIO_InitTypeDef 	  GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	  NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,ENABLE);//那1?邦USARTx那㊣?車	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF ,ENABLE); 
	
	//**∩??迆x??車|辰y???∩車?車3谷?**
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource6,GPIO_AF_UART7); 
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7,GPIO_AF_UART7); 
	
	//USARTx???迆????
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7; //
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//?∩車?1|?邦
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//?迄?豕100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //赤?赤足?∩車?那?3?
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //谷?角-
	GPIO_Init(GPIOF,&GPIO_InitStructure); 

   //USARTx 3?那??‘谷豕??
	USART_InitStructure.USART_BaudRate            = bps;//2“足??那谷豕??
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;//℅?3∟?a8??那y?Y??那?
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;//辰???赤㏒?1??
	USART_InitStructure.USART_Parity              = USART_Parity_No;//?T????D㏒?谷??
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//?T車2?t那y?Y芍¯????
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//那?﹞⊿?㏒那?
	USART_Init(UART7, &USART_InitStructure); //3?那??‘∩??迆x
	
	USART_Cmd(UART7, ENABLE);  //那1?邦∩??迆x 
	
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);//?a???角1??D??

	//Usartx NVIC ????
	NVIC_InitStructure.NVIC_IRQChannel                    = UART7_IRQn;//∩??迆x?D??赤“米角
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 3;//?角??車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 3;		//℅車車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;			//IRQ赤“米角那1?邦
	NVIC_Init(&NVIC_InitStructure);	//?迄?Y???“米?2?那y3?那??‘VIC??∩??¯?⊿

	USART_ClearFlag(UART7, USART_FLAG_TC);	
		  
}
//



/*
**************************************************************************************************
DESCRIPATION:
              initialize the UARTx  with bound per second 'bps'

INPUT	  DATA:
              bound per second 'bps'

OUTPUT	DATA:
              NONE

RETURN	DATA:
              NONE
              
NOTES		    :


**************************************************************************************************
*/
void  RS232_8_Init(unsigned int bps)
{
   //GPIO???迆谷豕??
	GPIO_InitTypeDef 	  GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	NVIC_InitTypeDef 	  NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,ENABLE);//那1?邦USARTx那㊣?車	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE ,ENABLE); 
	
	//**∩??迆x??車|辰y???∩車?車3谷?**
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_UART8); 
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_UART8); 
	
	//USARTx???迆????
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1; //
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;//?∩車?1|?邦
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//?迄?豕100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //赤?赤足?∩車?那?3?
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //谷?角-
	GPIO_Init(GPIOE,&GPIO_InitStructure); 

   //USARTx 3?那??‘谷豕??
	USART_InitStructure.USART_BaudRate            = bps;//2“足??那谷豕??
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;//℅?3∟?a8??那y?Y??那?
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;//辰???赤㏒?1??
	USART_InitStructure.USART_Parity              = USART_Parity_No;//?T????D㏒?谷??
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//?T車2?t那y?Y芍¯????
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;	//那?﹞⊿?㏒那?
	USART_Init(UART8, &USART_InitStructure); //3?那??‘∩??迆x
	
	USART_Cmd(UART8, ENABLE);  //那1?邦∩??迆x 
	
	USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);//?a???角1??D??

	//Usartx NVIC ????
	NVIC_InitStructure.NVIC_IRQChannel                    = UART8_IRQn;//∩??迆x?D??赤“米角
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 3;//?角??車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 3;		//℅車車??豕??3
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;			//IRQ赤“米角那1?邦
	NVIC_Init(&NVIC_InitStructure);	//?迄?Y???“米?2?那y3?那??‘VIC??∩??¯?⊿

	USART_ClearFlag(UART8, USART_FLAG_TC);	
		  
}
//


void  RS232_2_Send(unsigned char  *buf,unsigned  short len)
{

	unsigned short i;
	
	USART_ClearFlag(USART2, USART_FLAG_LBD);	
	USART_ClearFlag(USART2, USART_FLAG_RXNE);
	USART_GetFlagStatus(USART2, USART_FLAG_TC);
	USART_ClearFlag(USART2, USART_FLAG_TC);

	
	for(i=0;i<len;i++)		//
	{
		USART_SendData(USART2,buf[i]);	   
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	  
	}	 
	
}
//

void  RS232_5_Send(unsigned char  *buf,unsigned  short len)
{

	unsigned short i;
	
	USART_ClearFlag(UART5, USART_FLAG_LBD);	
	USART_ClearFlag(UART5, USART_FLAG_RXNE);
	USART_GetFlagStatus(UART5, USART_FLAG_TC);
	USART_ClearFlag(UART5, USART_FLAG_TC);

	
	for(i=0;i<len;i++)		//
	{
		USART_SendData(UART5,buf[i]);	   
		while(USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);	  
	}	 
	
}
//

void  RS232_7_Send(unsigned char  *buf,unsigned  short len)
{

	unsigned short i;
	
	USART_ClearFlag(UART7, USART_FLAG_LBD);	
	USART_ClearFlag(UART7, USART_FLAG_RXNE);
	USART_GetFlagStatus(UART7, USART_FLAG_TC);
	USART_ClearFlag(UART7, USART_FLAG_TC);

	
	for(i=0;i<len;i++)		//
	{
		USART_SendData(UART7,buf[i]);	   
		while(USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET);	  
	}	 
	
}
//



void  RS232_8_Send(unsigned char  *buf,unsigned  short len)
{

	unsigned short i;
	
	USART_ClearFlag(UART8, USART_FLAG_LBD);	
	USART_ClearFlag(UART8, USART_FLAG_RXNE);
	USART_GetFlagStatus(UART8, USART_FLAG_TC);
	USART_ClearFlag(UART8, USART_FLAG_TC);

	
	for(i=0;i<len;i++)		//
	{
		USART_SendData(UART8,buf[i]);	   
		while(USART_GetFlagStatus(UART8, USART_FLAG_TC) == RESET);	  
	}	 
	
}
//



