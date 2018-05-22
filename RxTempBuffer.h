/**
  ******************************************************************************
  * @file    RxTempBuffer.h
  * @author  Alex-BNS	ZhaoHui
  * @version V1.0.0
  * @date    23-July-2017
  * @brief   
  * #include "RxTempBuffer.h"
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
	* @attention
	* 
	*	PLEASE SET ENOUGH HEAP SIZE TO SATISFY PROGRAM.
	*	OR ELSE PROGRAM WILL OCCOUR ERROR.
	*
  * <h2><center>&copy; COPYRIGHT 2017 Alex-BNS	</center></h2>
  ******************************************************************************
  */


/*

//some compiler will occur a error called '__use_no_semihosting was requested, but _ttywrch was '
//__use_no_semihosting was requested, but _ttywrch was 
int _ttywrch(int ch) 
{ 
ch = ch; 
	return 0;
} 

*/








#ifndef	__RxTempBuffer_H__
#define	__RxTempBuffer_H__

#include	<stdio.h>
#include	"string.h"
#include  	"stdlib.h"

#define		ENABLE_DEBUG_RXTEMPBUFFER		0
/*
********************************************************************************************
*		mei ju xing bian liang ,yong yu biao shi han shu fan hui xin xi . 
*
*		There are some parameters what are ENUM type.They can indicate some result information that 
*functions return
*
*		
*
********************************************************************************************
*/
enum
{
	SUCCESS_USER	=	0,
	FAILURE_USER	=	1,

	EMPTY_USER		=	0,
	NOTEMPTY_USER	=	3,
	FULL_USER			=	4,

	BUSY_USER			=	5,
	LEISURE_USER	=	6
};
/**/


extern	struct	RXTEMPLIST *	uart2RxChain;
/*
********************************************************************************************
*		construct a struct type to express	a node of chain .
*		this is a bidirection chain.
*		
*		
*
********************************************************************************************
*/
struct	RXTEMPCHAINNODE
{
	struct	RXTEMPCHAINNODE	*previous;
	struct	RXTEMPCHAINNODE	*next;
	unsigned	int	lengthOfData;
	unsigned	char	*data;
};
/**/




/*
********************************************************************************************
*		construct a struct type to express	a chain .
*		����һ����Ϣ���У���Ҫ��RxTempChainInit�н��г�ʼ�����ں�����ָ�����ڵ��������ɡ�
*		����ͷ
*		����β
*		����æ
*		��ǰ�ڵ�����
*		���ڵ�����
********************************************************************************************
*/
struct	RXTEMPLIST
{
	struct	RXTEMPCHAINNODE	*head;
	struct	RXTEMPCHAINNODE	*tail;
	unsigned	char	busy;
	unsigned	short	countOfNode;
	unsigned	short	maxCountOfNode;
};
//



//��ʼ��һ����Ϣ����rxChain���Լ��˶����нڵ���������maxCountOfChainInList
//ʹ�ô˺���֮ǰ������ΪrxChain ����һ����ַ�ռ�malloc()
unsigned	char	RxTempChainInit(struct	RXTEMPLIST *rxChain,unsigned	short	maxCountOfChainInList);

//��ѯһ����Ϣ�������Ƿ���ں�����Ч���ݵĽڵ�
unsigned	short	RxTempChainEmptyOrNot(struct	RXTEMPLIST *rxChain);

//��һ����Ϣ�����д�������
//����ֵ��Ϣ������
//SUCCESS_USER�������ɹ�
//FAILURE_USER������ʧ��
//BUSY_USER		��ϵͳ��æ����æʱд�����ʧ��
//FULL_USER 	��������
unsigned	char	RxTempChainWrite(struct	RXTEMPLIST *rxChain,unsigned	char *rxData,unsigned	int len);

//��һ����Ϣ�����ж�ȡ����
//����ֵ��Ϣ������
//SUCCESS_USER�������ɹ�
//BUSY_USER		��ϵͳ��æ����æʱ��ȡ����ʧ��
//EMPTY_USER	�����ؿ�����
unsigned	char	RxTempChainRead(struct	RXTEMPLIST *rxChain,unsigned	char *outputData,unsigned int *len);

//���һ����Ϣ���У�����free(rxChain);
//����ֵ��Ϣ������
//SUCCESS_USER�������ɹ�
//BUSY_USER		��ϵͳ��æ����æʱ��ղ���ʧ��
unsigned	char	RxTempChainDel(struct	RXTEMPLIST *rxChain);



#endif


