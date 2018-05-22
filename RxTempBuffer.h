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
*		这是一个消息队列，需要在RxTempChainInit中进行初始化，在函数中指定最大节点数量即可。
*		链表头
*		链表尾
*		链表繁忙
*		当前节点数量
*		最大节点数量
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



//初始化一个消息队列rxChain，以及此队列中节点的最大数量maxCountOfChainInList
//使用此函数之前，必须为rxChain 分配一个地址空间malloc()
unsigned	char	RxTempChainInit(struct	RXTEMPLIST *rxChain,unsigned	short	maxCountOfChainInList);

//查询一个消息队列中是否存在含有有效数据的节点
unsigned	short	RxTempChainEmptyOrNot(struct	RXTEMPLIST *rxChain);

//向一个消息队列中存入数据
//返回值信息包括：
//SUCCESS_USER：操作成功
//FAILURE_USER：操作失败
//BUSY_USER		：系统繁忙，繁忙时写入操作失败
//FULL_USER 	：链已满
unsigned	char	RxTempChainWrite(struct	RXTEMPLIST *rxChain,unsigned	char *rxData,unsigned	int len);

//从一个消息队列中读取数据
//返回值信息包括：
//SUCCESS_USER：操作成功
//BUSY_USER		：系统繁忙，繁忙时读取操作失败
//EMPTY_USER	：返回空数据
unsigned	char	RxTempChainRead(struct	RXTEMPLIST *rxChain,unsigned	char *outputData,unsigned int *len);

//清空一个消息队列，包括free(rxChain);
//返回值信息包括：
//SUCCESS_USER：操作成功
//BUSY_USER		：系统繁忙，繁忙时清空操作失败
unsigned	char	RxTempChainDel(struct	RXTEMPLIST *rxChain);



#endif


