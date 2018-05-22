#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include	"RS232.h"
#include "led.h" 
#include "RxTempBuffer.h"


void TIM7_INIT(unsigned short arr,unsigned short psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);  ///ʹ��TIM7ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);//��ʼ��TIM7
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); //����ʱ��x�����ж�
  
	TIM_Cmd(TIM7,DISABLE); //ʹ�ܶ�ʱ��x
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM7_IRQn; //��ʱ��x�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x02; //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
//


struct	RXTEMPLIST *	uart2RxChain;

int main(void)
{
	u32 t=0;
	
	unsigned	char	uart2RxTemp[512]={0};
	unsigned	int	lengthOfUart2Rx;
  
  
	unsigned	char	tx1[]={"���ڳ�ʼ���ɹ���\r\n"};
	uart2RxChain	=	(struct	RXTEMPLIST *)malloc(sizeof(struct	RXTEMPLIST ));
	RxTempChainInit(uart2RxChain,10);	
	
	delay_init(186);
	RS232_2_Init(115200);
	RS232_2_Send(tx1,sizeof(tx1));
	TIM7_INIT(2000,840-1);//20ms��ʱ��
	LED_Init();
	M_LED_ALL_OFF;
	

	
  while(1)
	{
		
		
		
		
		RxTempChainRead(uart2RxChain,uart2RxTemp,&lengthOfUart2Rx);

		RS232_2_Send(uart2RxTemp,lengthOfUart2Rx);
		
		memset(uart2RxTemp,0,sizeof(uart2RxTemp));
		lengthOfUart2Rx	=	0;
		
		
		delay_ms(1000);
		
		{
			static	unsigned char	tomes	=0;
			if(tomes)
			{
				tomes	=	0;
				M_LED1_ON;
			}
			else
			{
				tomes	=	1;
				M_LED1_OFF;
				M_LED2_OFF;
			}
			//
		}
		//
		
		
	}
}
/*End main*/


